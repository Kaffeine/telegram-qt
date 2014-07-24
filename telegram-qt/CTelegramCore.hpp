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

    bool initConnection(const QString &address, quint32 port);
    bool restoreConnection(const QByteArray &secret);

    void requestPhoneStatus(const QString &phoneNumber);
    void requestPhoneCode(const QString &phoneNumber);
    void signIn(const QString &phoneNumber, const QString &authCode);
    void signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName);

    void addContact(const QString &phoneNumber);

    void requestContactList();
    void requestContactAvatar(const QString &contact);

    QStringList contactList() const;

    TelegramNamespace::ContactStatus contactStatus(const QString &phone) const;

    void sendMessage(const QString &phone, const QString &message);
    void setTyping(const QString &phone, bool typingStatus);

signals:
    void connected();
    void phoneCodeRequired();
    void phoneCodeIsInvalid();
    void authenticated();
    void contactListChanged();
    void phoneStatusReceived(const QString &phone, bool registered, bool invited);
    void avatarReceived(const QString &contact, const QByteArray &data, const QString &mimeType);

    void messageReceived(const QString &phone, const QString &message);
    void contactStatusChanged(const QString &phone, TelegramNamespace::ContactStatus status);

protected:
    CTelegramDispatcher *m_dispatcher;

    const CAppInformation *m_appInfo;

};

#endif // CTELECORE_HPP
