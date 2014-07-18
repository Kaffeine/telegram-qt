/*
    Copyright (C) 2014 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "CTelegramDispatcher.hpp"

#include "CTelegramConnection.hpp"
#include "CTelegramStream.hpp"

#include <QDebug>

const quint32 secretFormatVersion = 0;

CTelegramDispatcher::CTelegramDispatcher(QObject *parent) :
    QObject(parent),
    m_appInformation(0),
    m_activeDc(0),
    m_wantedActiveDc(0)
{
}

void CTelegramDispatcher::setAppInformation(const CAppInformation *newAppInfo)
{
    m_appInformation = newAppInfo;
}

void CTelegramDispatcher::addContacts(const QStringList &phoneNumbers, bool replace)
{
    activeConnection()->addContacts(phoneNumbers, replace);
}

QByteArray CTelegramDispatcher::connectionSecretInfo() const
{
    if (!activeConnection()) {
        return QByteArray();
    }

    QByteArray output;
    CTelegramStream outputStream(&output, /* write */ true);

    outputStream << secretFormatVersion;
    outputStream << activeConnection()->deltaTime();
    outputStream << activeConnection()->dcInfo();
    outputStream << m_selfPhone;
    outputStream << activeConnection()->authKey();
    outputStream << activeConnection()->authId();
    outputStream << activeConnection()->serverSalt();

    return output;
}

void CTelegramDispatcher::initConnection(const QString &address, quint32 port)
{
    TLDcOption dcInfo;
    dcInfo.ipAddress = address;
    dcInfo.port = port;

    CTelegramConnection *connection = createConnection(dcInfo);

    m_connections.insert(0, connection);
    connection->connectToDc();

    setActiveDc(0);
}

bool CTelegramDispatcher::restoreConnection(const QByteArray &secret)
{
    CTelegramStream inputStream(secret);

    quint32 format;
    qint32 deltaTime;
    TLDcOption dcInfo;
    QByteArray authKey;
    quint64 authId;
    quint64 serverSalt;

    inputStream >> format;

    if (format != secretFormatVersion) {
        qDebug() << "Unknown format version";
        return false;
    }

    inputStream >> deltaTime;
    inputStream >> dcInfo;
    inputStream >> m_selfPhone;
    inputStream >> authKey;
    inputStream >> authId;
    inputStream >> serverSalt;

    CTelegramConnection *connection = createConnection(dcInfo);

    connection->setDeltaTime(deltaTime);
    connection->setAuthKey(authKey);
    connection->setServerSalt(serverSalt);

    if (connection->authId() != authId) {
        qDebug() << "Invalid auth data.";
        delete connection;
        return false;
    }

    m_connections.insert(dcInfo.id, connection);

    setActiveDc(dcInfo.id);

    connection->connectToDc();

    return true;
}

void CTelegramDispatcher::requestPhoneStatus(const QString &phoneNumber)
{
    activeConnection()->requestPhoneStatus(phoneNumber);
}

void CTelegramDispatcher::signIn(const QString &phoneNumber, const QString &authCode)
{
    activeConnection()->signIn(phoneNumber, authCode);
}

void CTelegramDispatcher::signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName)
{
    activeConnection()->signUp(phoneNumber, authCode, firstName, lastName);
}

void CTelegramDispatcher::requestPhoneCode(const QString &phoneNumber)
{
    if (!activeConnection()) {
        qDebug() << "Can't request phone code: there is no active connection.";
        return;
    }

    if (m_dcConfiguration.isEmpty()) {
        qDebug() << "Can't request phone code: DC Configuration is unknown.";
        return;
    }

    activeConnection()->requestPhoneCode(phoneNumber);
}

void CTelegramDispatcher::requestContactList()
{
    activeConnection()->requestContacts();
}

void CTelegramDispatcher::requestContactAvatar(const QString &contact)
{
    qDebug() << Q_FUNC_INFO << contact;

    int contactIndex = m_contactList.indexOf(contact);

    if (contactIndex < 0) {
        qDebug() << Q_FUNC_INFO << "Unknown contact" << contact;
        return;
    }

    if (m_users.at(contactIndex).photo.tlType == UserProfilePhotoEmpty) {
        qDebug() << Q_FUNC_INFO << "Contact" << contact << "have no avatar";
        return;
    }

    TLFileLocation avatarLocation = m_users.at(contactIndex).photo.photoSmall;

    if (avatarLocation.tlType == FileLocationUnavailable) {
        qDebug() << Q_FUNC_INFO << "Contact" << contact << "avatar is not available";
        return;
    }

    TLInputFileLocation inputFile;
    inputFile.volumeId = avatarLocation.volumeId;
    inputFile.localId  = avatarLocation.localId;
    inputFile.secret   = avatarLocation.secret;

    requestFile(inputFile, avatarLocation.dcId, contactIndex);
    qDebug() << Q_FUNC_INFO << "Requested avatar for contact " << contactIndex << contact;
}

void CTelegramDispatcher::sendMessageToContact(const QString &phone, const QString &message)
{
    TLInputPeer peer = phoneNumberToInputPeer(phone);

    if (peer.tlType == InputPeerEmpty) {
        qDebug() << Q_FUNC_INFO << "Can not resolve contact" << phone;
        return;
    }

    activeConnection()->sendMessage(peer, message);
}

void CTelegramDispatcher::whenSelfPhoneReceived(const QString &phone)
{
    m_selfPhone = phone;
}

void CTelegramDispatcher::setUsers(const QVector<TLUser> &users)
{
    m_users = users;

    QStringList contactIds;
    contactIds.reserve(m_users.count());

    foreach (const TLUser &user, m_users) {
        contactIds.append(user.phone);
    }

    if (m_contactList != contactIds) {
        m_contactList = contactIds;
        emit contactListChanged();
    }
}

void CTelegramDispatcher::addUsers(const QVector<TLUser> &users)
{
    m_users += users;

    m_contactList.reserve(m_users.count());

    foreach (const TLUser &user, users) {
        m_contactList.append(user.phone);
    }

    emit contactListChanged();
}

void CTelegramDispatcher::requestFile(const TLInputFileLocation &location, quint32 dc, quint32 fileId)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (!connection) {
        qDebug() << "No connection";
    }

    if (connection && (connection->authState() == CTelegramConnection::AuthStateSignedIn)) {
        connection->getFile(location, fileId);
    } else {
        qDebug() << Q_FUNC_INFO << "There is no connection to dest dc. Not implemented." << dc;
        // TODO
    }
}

void CTelegramDispatcher::processUpdate(const TLUpdate &update)
{
    qDebug() << "Type:" << QString::number(update.tlType, 16);
    switch (update.tlType) {
//    case UpdateNewMessage:
//        update.message;
//        update.pts;
//        break;
//    case UpdateMessageID:
//        update.id;
//        update.randomId;
//        break;
//    case UpdateReadMessages:
//        update.messages;
//        update.pts;
//        break;
//    case UpdateDeleteMessages:
//        update.messages;
//        update.pts;
//        break;
//    case UpdateRestoreMessages:
//        update.messages;
//        update.pts;
//        break;
//    case UpdateUserTyping:
//        update.userId;
//        break;
//    case UpdateChatUserTyping:
//        update.chatId;
//        update.userId;
//        break;
//    case UpdateChatParticipants:
//        update.participants;
//        break;
//    case UpdateUserStatus:
//        update.userId;
//        update.status;
//        break;
//    case UpdateUserName:
//        update.userId;
//        update.firstName;
//        update.lastName;
//        break;
//    case UpdateUserPhoto:
//        update.userId;
//        update.date;
//        update.photo;
//        update.previous;
//        break;
//    case UpdateContactRegistered:
//        update.userId;
//        update.date;
//        break;
//    case UpdateContactLink:
//        update.userId;
//        update.myLink;
//        update.foreignLink;
//        break;
//    case UpdateActivation:
//        update.userId;
//        break;
//    case UpdateNewAuthorization:
//        update.authKeyId;
//        update.date;
//        update.device;
//        update.location;
//        break;
//    case UpdateNewGeoChatMessage:
//        update.message;
//        break;
//    case UpdateNewEncryptedMessage:
//        update.message;
//        update.qts;
//        break;
//    case UpdateEncryptedChatTyping:
//        update.chatId;
//        break;
//    case UpdateEncryption:
//        update.chat;
//        update.date;
//        break;
//    case UpdateEncryptedMessagesRead:
//        update.chatId;
//        update.maxDate;
//        update.date;
//        break;
//    case UpdateChatParticipantAdd:
//        update.chatId;
//        update.userId;
//        update.inviterId;
//        update.version;
//        break;
//    case UpdateChatParticipantDelete:
//        update.chatId;
//        update.userId;
//        update.version;
//        break;
//    case UpdateDcOptions:
//        update.dcOptions;
//        break;
//    case UpdateUserBlocked:
//        update.userId;
//        update.blocked;
//        break;
//    case UpdateNotifySettings:
//        update.peer;
//        update.notifySettings;
//        break;
    default:
        break;
    }
}

TLInputPeer CTelegramDispatcher::phoneNumberToInputPeer(const QString &phoneNumber) const
{
    TLInputPeer inputPeer;

    if (phoneNumber == m_selfPhone) {
        inputPeer.tlType = InputPeerSelf;
    } else {
        const int indexOfContact = m_contactList.indexOf(phoneNumber);
        if (indexOfContact >= 0) {
            inputPeer.tlType = InputPeerContact;
            inputPeer.userId = m_users.at(indexOfContact).id;
        }
    }

    return inputPeer;
}

QString CTelegramDispatcher::userIdToPhoneNumber(const quint32 id)
{
    foreach (const TLUser &user, m_users) {
        if (user.id == id) {
            return user.phone;
        }
    }

    return QString(QLatin1String("unknown%1")).arg(id);
}

void CTelegramDispatcher::whenConnectionAuthChanged(int dc, int newState)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (!connection) {
        return;
    }

    if (newState >= CTelegramConnection::AuthStateSuccess) {
        if (m_dcConfiguration.isEmpty()) {
            connection->getConfiguration();
        }

        if (m_wantedActiveDc == dc) {
            setActiveDc(dc);
        }

        foreach (const QByteArray &data, m_delayedPackages.values(dc)) {
            connection->processRedirectedPackage(data);
        }

        m_delayedPackages.remove(dc);
    }

    if (newState == CTelegramConnection::AuthStateSignedIn) {
        connect(connection, SIGNAL(usersReceived(QVector<TLUser>)), SLOT(setUsers(QVector<TLUser>)));
        connect(connection, SIGNAL(usersAdded(QVector<TLUser>))   , SLOT(addUsers(QVector<TLUser>)));
        connect(connection, SIGNAL(updatesReceived(TLUpdates)), SLOT(whenUpdatesReceived(TLUpdates)));

        emit authenticated();
    }
}

void CTelegramDispatcher::whenConnectionConfigurationUpdated(int dc)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (!connection) {
        return;
    }

    m_dcConfiguration = connection->dcConfiguration();

    qDebug() << "Core: DC Configuration:";
    for (int i = 0; i < m_dcConfiguration.count(); ++i) {
        qDebug() << m_dcConfiguration.at(i).id << ": " << m_dcConfiguration.at(i).ipAddress << ":"<< m_dcConfiguration.at(i).port;
    }

    emit dcConfigurationObtained();
}

void CTelegramDispatcher::whenConnectionDcIdUpdated(int connectionId, int newDcId)
{
    CTelegramConnection *connection = m_connections.value(connectionId);

    if (!connection) {
        return;
    }

    if (m_connections.value(newDcId)) {
        qDebug() << "Connection with wanted id already exists";
    } else {
        m_connections.remove(connectionId);
        m_connections.insert(newDcId, connection);

        TLDcOption info = connection->dcInfo();
        info.id = newDcId;
        connection->setDcInfo(info);

        if (m_activeDc == connectionId) {

            if (m_wantedActiveDc == m_activeDc) {
                m_wantedActiveDc = newDcId;
            }

            setActiveDc(newDcId);
        }

        qDebug() << "Connection DC Id changed from" << connectionId << "to" << newDcId;
    }
}

void CTelegramDispatcher::whenPackageRedirected(const QByteArray &data, int dc)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (connection && connection->authState() >= CTelegramConnection::AuthStateSuccess) {
        connection->processRedirectedPackage(data);
    } else {
        m_delayedPackages.insertMulti(dc, data);
        establishConnectionToDc(dc);
    }
}

void CTelegramDispatcher::whenWantedActiveDcChanged(int dc)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (connection && connection->authState() >= CTelegramConnection::AuthStateSuccess) {
        setActiveDc(dc);
    } else {
        m_wantedActiveDc = dc;
        establishConnectionToDc(dc);
    }
}

void CTelegramDispatcher::whenFileReceived(const TLUploadFile &file, quint32 fileId)
{
    // Proto version.

    QString mimeType = mimeTypeByStorageFileType(file.type.tlType);

    if (m_contactList.count() < fileId) {
        qDebug() << Q_FUNC_INFO << "Unexpected fileId" << fileId << "contact-list:" << m_contactList;
        return;
    }

    QString contact = m_contactList.at(fileId);

    emit avatarReceived(contact, file.bytes, mimeType);
}

void CTelegramDispatcher::whenUpdatesReceived(const TLUpdates &updates)
{
    switch (updates.tlType) {
    case UpdatesTooLong:
        qDebug() << Q_FUNC_INFO << "UpdatesTooLong processing is not implemented yet.";
        break;
    case UpdateShortMessage:
        emit messageReceived(userIdToPhoneNumber(updates.fromId), updates.message);
        break;
    case UpdateShortChatMessage:
        qDebug() << Q_FUNC_INFO << "UpdateShortChatMessage processing is not implemented yet.";
        break;
    case UpdateShort:
        processUpdate(updates.update);
        break;
    case UpdatesCombined:
        qDebug() << Q_FUNC_INFO << "UpdatesCombined processing is not implemented yet.";
        break;
    case Updates:
        qDebug() << Q_FUNC_INFO << "Updates processing is not implemented yet.";
    default:
        break;
    }
}

void CTelegramDispatcher::setActiveDc(int dc, bool syncWantedDc)
{
    m_activeDc = dc;

    if (syncWantedDc) {
        m_wantedActiveDc = dc;
    }

    qDebug() << "New active dc:" << dc;
}

CTelegramConnection *CTelegramDispatcher::createConnection(const TLDcOption &dc)
{
    CTelegramConnection *connection = new CTelegramConnection(m_appInformation, this);

    connect(connection, SIGNAL(selfPhoneReceived(QString)), SLOT(whenSelfPhoneReceived(QString)));
    connect(connection, SIGNAL(authStateChanged(int,int)), SLOT(whenConnectionAuthChanged(int,int)));
    connect(connection, SIGNAL(dcConfigurationReceived(int)), SLOT(whenConnectionConfigurationUpdated(int)));
    connect(connection, SIGNAL(actualDcIdReceived(int,int)), SLOT(whenConnectionDcIdUpdated(int,int)));
    connect(connection, SIGNAL(newRedirectedPackage(QByteArray,int)), SLOT(whenPackageRedirected(QByteArray,int)));
    connect(connection, SIGNAL(wantedActiveDcChanged(int)), SLOT(whenWantedActiveDcChanged(int)));

    connect(connection, SIGNAL(phoneStatusReceived(QString,bool,bool)), SIGNAL(phoneStatusReceived(QString,bool,bool)));
    connect(connection, SIGNAL(phoneCodeRequired()), SIGNAL(phoneCodeRequired()));
    connect(connection, SIGNAL(phoneCodeIsInvalid()), SIGNAL(phoneCodeIsInvalid()));

    connect(connection, SIGNAL(fileReceived(TLUploadFile,quint32)), SLOT(whenFileReceived(TLUploadFile,quint32)));

    connection->setDcInfo(dc);

    return connection;
}

CTelegramConnection *CTelegramDispatcher::establishConnectionToDc(int dc)
{
    CTelegramConnection *connection = m_connections.value(dc);

    if (!connection) {
        const TLDcOption info = dcInfoById(dc);

        if (info.ipAddress.isEmpty()) {
            qDebug() << "Error: Attempt to connect to unknown DC" << dc;
            return 0;
        }

        connection = createConnection(info);
        m_connections.insert(dc, connection);
    }

    if (!connection->isConnected()) {
        connection->connectToDc();
    }

    return connection;
}

TLDcOption CTelegramDispatcher::dcInfoById(quint32 dc)
{
    foreach (const TLDcOption option, m_dcConfiguration) {
        if (option.id == dc) {
            return option;
        }
    }

    return TLDcOption();
}

QString CTelegramDispatcher::mimeTypeByStorageFileType(TLValue type)
{
    switch (type) {
    case StorageFileJpeg:
        return QLatin1String("image/jpeg");
    case StorageFileGif:
        return QLatin1String("image/gif");
    case StorageFilePng:
        return QLatin1String("image/png");
    case StorageFilePdf:
        return QLatin1String("application/pdf");
    case StorageFileMp3:
        return QLatin1String("audio/mpeg");
    case StorageFileMov:
        return QLatin1String("video/quicktime");
    case StorageFileMp4:
        return QLatin1String("audio/mp4");
    case StorageFileWebp:
        return QLatin1String("image/webp");
    default:
        return QString();
    }
}
