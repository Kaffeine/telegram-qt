#include "TelegramServerUser.hpp"

#include "ApiUtils.hpp"
#include "RandomGenerator.hpp"
#include "ServerUtils.hpp"
#include "Session.hpp"
#include "Utils.hpp"

#include <QCryptographicHash>
#include <QLoggingCategory>

namespace Telegram {

namespace Server {

quint32 PostBox::addMessage(quint64 globalId)
{
    ++m_lastMessageId;
    ++m_pts;

    m_messages.insert(m_lastMessageId, globalId);
    return m_lastMessageId;
}

quint64 PostBox::getMessageGlobalId(quint32 messageId) const
{
    return m_messages.value(messageId);
}

QHash<quint32, quint64> PostBox::getAllMessageKeys() const
{
    return m_messages;
}

TLPeer MessageRecipient::toTLPeer() const
{
    const Peer p = toPeer();
    if (Q_UNLIKELY(!p.isValid())) {
        qCritical() << Q_FUNC_INFO << "Invalid peer" << this;
        return TLPeer();
    }
    TLPeer result;
    switch (p.type()) {
    case Peer::User:
        result.tlType = TLValue::PeerUser;
        result.userId = p;
        break;
    case Peer::Chat:
        result.tlType = TLValue::PeerChat;
        result.chatId = p;
        break;
    case Peer::Channel:
        result.tlType = TLValue::PeerChannel;
        result.channelId = p;
        break;
    }
    return result;
}

UserContact AbstractUser::toContact() const
{
    UserContact contact;
    contact.id = userId();
    contact.phone = phoneNumber();
    contact.firstName = firstName();
    contact.lastName = lastName();
    return contact;
}

LocalUser::LocalUser(UserId userId, const QString &phoneNumber)
{
    m_phoneNumber = phoneNumber;
    setUserId(userId);
}

LocalUser::~LocalUser()
{
    qDeleteAll(m_dialogs);
}

void LocalUser::setPhoneNumber(const QString &phoneNumber)
{
    m_phoneNumber = phoneNumber;
    if (!m_id.isValid()) {
        setUserId(UserId(qHash(m_phoneNumber)));
    }
}

void LocalUser::setUserName(const QString &userName)
{
    m_userName = userName;
}

void LocalUser::setFirstName(const QString &firstName)
{
    m_firstName = firstName;
}

void LocalUser::setLastName(const QString &lastName)
{
    m_lastName = lastName;
}

void LocalUser::setAbout(const QString &about)
{
    m_about = about;
}

void LocalUser::setOnlineTimestamp(quint32 onlineTimestampSec)
{
    m_onlineTimestamp = onlineTimestampSec;
}

bool LocalUser::isOnline() const
{
    return m_onlineTimestamp >= Telegram::Utils::getCurrentTime();
}

void AuthorizedUser::setDcId(quint32 id)
{
    m_dcId = id;
}

Session *AuthorizedUser::getSession(quint64 sessionId) const
{
    for (Session *s : m_sessions) {
        if (s->id() == sessionId) {
            return s;
        }
    }
    return nullptr;
}

void AuthorizedUser::addAuthKey(quint64 authId)
{
    if (m_authKeyIds.contains(authId)) {
        return;
    }
    m_authKeyIds.append(authId);
}

QVector<Session *> AuthorizedUser::activeSessions() const
{
    QVector<Session *> result;
    for (Session *s : m_sessions) {
        if (s->isActive()) {
            result.append(s);
        }
    }
    return result;
}

bool AuthorizedUser::hasActiveSession() const
{
    for (Session *s : m_sessions) {
        if (s->isActive()) {
            return true;
        }
    }
    return false;
}

void AuthorizedUser::addSession(Session *session)
{
    m_sessions.append(session);
    session->setUserId(userId());
}

ImageDescriptor LocalUser::getCurrentImage() const
{
    if (m_photos.isEmpty()) {
        return ImageDescriptor();
    }
    return m_photos.first();
}

void LocalUser::updateImage(const ImageDescriptor &image)
{
    m_photos.prepend(image);
}

void LocalUser::setPlainPassword(const QString &password)
{
    if (password.isEmpty()) {
        m_passwordSalt.clear();
        m_passwordHash.clear();
        return;
    }
    QByteArray pwdSalt(8, Qt::Uninitialized);
    RandomGenerator::instance()->generate(&pwdSalt);
    const QByteArray pwdData = pwdSalt + password.toUtf8() + pwdSalt;
    const QByteArray pwdHash = QCryptographicHash::hash(pwdData, QCryptographicHash::Sha256);
    setPassword(pwdSalt, pwdHash);
}

void LocalUser::setPassword(const QByteArray &salt, const QByteArray &hash)
{
    m_passwordSalt = salt;
    m_passwordHash = hash;
}

void LocalUser::importContact(const UserContact &contact)
{
    // Check for contact registration status and the contact id setup performed out of this function
    m_importedContacts.append(contact);

    if (contact.id.isValid()) {
        m_contactList.append(contact.id);
    }
}

void LocalUser::bumpDialogUnreadCount(const Peer &peer)
{
    getDialog(peer)->unreadCount += 1;
    m_box.setUnreadCount(m_box.unreadCount() + 1);
}

UserDialog *LocalUser::ensureDialog(const Telegram::Peer &peer)
{
    UserDialog *dialog = getDialog(peer);
    if (!dialog) {
        dialog = new UserDialog();
        dialog->peer = peer;
        m_dialogs.append(dialog);
    }
    return dialog;
}

void LocalUser::addNewMessage(const Peer &peer, quint32 messageId, quint64 messageDate)
{
    UserDialog *dialog = ensureDialog(peer);
    dialog->topMessage = messageId;
    dialog->date = messageDate;

    syncDialogsOrder();
}

UserDialog *LocalUser::getDialog(const Peer &peer)
{
    for (int i = 0; i < m_dialogs.count(); ++i) {
        if (m_dialogs.at(i)->peer == peer) {
            return m_dialogs.at(i);
        }
    }
    return nullptr;
}

const UserDialog *LocalUser::getDialog(const Peer &peer) const
{
    for (int i = 0; i < m_dialogs.count(); ++i) {
        if (m_dialogs.at(i)->peer == peer) {
            return m_dialogs.at(i);
        }
    }
    return nullptr;
}

void LocalUser::syncDialogsOrder()
{
    std::sort(m_dialogs.begin(), m_dialogs.end(), [](const UserDialog *left, const UserDialog *right) -> bool {
        // return true if the first arg should be placed before the second one
        return left->date > right->date;
    });
}

void LocalUser::setUserId(UserId userId)
{
    m_id = userId;
    m_box.setUserId(m_id);
}

void UserPostBox::setUnreadCount(quint32 count)
{
    m_unreadCount = count;
}

} // Server namespace

} // Telegram namespace
