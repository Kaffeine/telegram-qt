/*
    Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef CTELEGRAMCORE_HPP
#define CTELEGRAMCORE_HPP

#include "telegramqt_export.h"
#include "TelegramNamespace.hpp"

#include <QObject>
#include <QVector>
#include <QStringList>

class CAppInformation;
class CTelegramDispatcher;

class TELEGRAMQT_EXPORT CTelegramCore : public QObject
{
    Q_OBJECT
public:
    explicit CTelegramCore(QObject *parent = 0);
    ~CTelegramCore();

    inline const CAppInformation *appInfo() { return m_appInfo; }
    void setAppInformation(const CAppInformation *newAppInfo);

    QByteArray connectionSecretInfo() const;

    Q_INVOKABLE TelegramNamespace::ConnectionState connectionState() const;
    Q_INVOKABLE QString selfPhone() const;
    Q_INVOKABLE QStringList contactList() const;
    Q_INVOKABLE QList<quint32> chatList() const;
    Q_INVOKABLE TelegramNamespace::ContactStatus contactStatus(const QString &contact) const;
    Q_INVOKABLE quint32 contactLastOnline(const QString &contact) const;
    Q_INVOKABLE QString contactFirstName(const QString &contact) const;
    Q_INVOKABLE QString contactLastName(const QString &contact) const;
    Q_INVOKABLE QString contactUserName(const QString &contact) const;
    Q_INVOKABLE QString contactAvatarToken(const QString &contact) const;
    Q_INVOKABLE QString chatTitle(quint32 chatId) const;

    static qint32 localTypingRecommendedRepeatInterval(); // Recommended application local typing state re-set interval.

    bool getChatInfo(TelegramNamespace::GroupChat *chatInfo, quint32 chatId) const;
    bool getChatParticipants(QStringList *participants, quint32 chatId);

public Q_SLOTS:
    void setMessageReceivingFilterFlags(quint32 flags); // TelegramNamespace::MessageFlags. Messages with at least one of the passed flags will be filtered out.
    void setAcceptableMessageTypes(quint32 types); // TelegramNamespace::MessageType
    void setAutoReconnection(bool enable);

    // By default, the app would ping server every 15 000 ms and instruct the server to close connection after 10 000 more ms. Use 0 to disable ping.
    void setPingInterval(quint32 ms);

    bool initConnection(const QString &address, quint32 port);
    bool restoreConnection(const QByteArray &secret);
    void closeConnection();
    bool logOut();

    void requestPhoneStatus(const QString &phoneNumber);
    void requestPhoneCode(const QString &phoneNumber);
    void signIn(const QString &phoneNumber, const QString &authCode);
    void signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName);

    void addContact(const QString &phoneNumber);
    void addContacts(const QStringList &phoneNumbers);

    void deleteContact(const QString &phoneNumber);
    void deleteContacts(const QStringList &phoneNumbers);

    void requestContactAvatar(const QString &contact);
    void requestMessageMediaData(quint32 messageId);

    quint64 sendMessage(const QString &identifier, const QString &message); // Message id is random number
    /* Typing status is valid for 6 seconds. It is recommended to repeat typing status with localTypingRecommendedRepeatInterval() interval. */
    void setTyping(const QString &contact, bool typingStatus);
    void setMessageRead(const QString &contact, quint32 messageId);

    // Set visible (not actual) online status.
    void setOnlineStatus(bool onlineStatus);

    // Both methods result in userNameStatusUpdated() emission
    void checkUserName(const QString &userName);
    void setUserName(const QString &newUserName);

    quint32 createChat(const QStringList &phones, const QString &title);
    bool addChatUser(quint32 chatId, const QString &contact, quint32 forwardMessages = 0);

    // Not "Chat" methods can be used instead.
    quint64 sendChatMessage(quint32 chatId, const QString &message); // Message id is random number
    void setChatTyping(quint32 chatId, bool typingStatus);
    void setChatMessageRead(const quint32 &chatId, quint32 messageId);

Q_SIGNALS:
    void connectionStateChanged(TelegramNamespace::ConnectionState status);

    void phoneCodeRequired();
    void loggedOut(bool result);
    void authSignErrorReceived(TelegramNamespace::AuthSignError errorCode, const QString &errorMessage); // Error message description: https://core.telegram.org/api/errors#400-bad-request
    void contactListChanged();
    void contactProfileChanged(const QString &contact); // First and/or last name was changed
    void phoneStatusReceived(const QString &phone, bool registered, bool invited);

    void avatarReceived(const QString &contact, const QByteArray &data, const QString &mimeType, const QString &avatarToken);
    void messageMediaDataReceived(const QString &contact, quint32 messageId, const QByteArray &data, const QString &mimeType, TelegramNamespace::MessageType type);

    void messageReceived(const QString &contact, const QString &message, TelegramNamespace::MessageType type, quint32 messageId, quint32 flags, quint32 timestamp);
    void chatMessageReceived(quint32 chatId, const QString &contact, const QString &message, TelegramNamespace::MessageType type, quint32 messageId, quint32 flags, quint32 timestamp);

    void contactStatusChanged(const QString &contact, TelegramNamespace::ContactStatus status);
    void contactTypingStatusChanged(const QString &contact, bool typingStatus);
    void contactChatTypingStatusChanged(quint32 chatId, const QString &contact, bool typingStatus);

    void sentMessageStatusChanged(const QString &contact, quint64 messageId, TelegramNamespace::MessageDeliveryStatus status); // Message id is random number

    void chatAdded(quint32 publichChatId);
    void chatChanged(quint32 publichChatId);

    void authorizationErrorReceived();

    void userNameStatusUpdated(const QString &userName, TelegramNamespace::AccountUserNameStatus status);

private:
    CTelegramDispatcher *m_dispatcher;

    const CAppInformation *m_appInfo;

};

inline void CTelegramCore::addContact(const QString &phoneNumber)
{
    addContacts(QStringList() << phoneNumber);
}

inline void CTelegramCore::deleteContact(const QString &phoneNumber)
{
    deleteContacts(QStringList() << phoneNumber);
}

inline quint64 CTelegramCore::sendChatMessage(quint32 chatId, const QString &message)
{
    return sendMessage(QString(QLatin1String("chat%1")).arg(chatId), message);
}

inline void CTelegramCore::setChatTyping(quint32 chatId, bool typingStatus)
{
    setTyping(QString(QLatin1String("chat%1")).arg(chatId), typingStatus);
}

inline void CTelegramCore::setChatMessageRead(const quint32 &chatId, quint32 messageId)
{
    setMessageRead(QString(QLatin1String("chat%1")).arg(chatId), messageId);
}

#endif // CTELECORE_HPP
