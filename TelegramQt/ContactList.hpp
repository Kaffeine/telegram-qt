#ifndef TELEGRAMQT_CONTACT_LIST_HPP
#define TELEGRAMQT_CONTACT_LIST_HPP

#include <QObject>
#include <QVector>

#include "ReadyObject.hpp"

namespace Telegram {

class PendingOperation;

namespace Client {

class ContactsApi;
class ContactListPrivate;

class TELEGRAMQT_EXPORT ContactList : public QObject, public ReadyObject
{
    Q_OBJECT
public:
    ~ContactList() override;

    QVector<quint32> list() const;

    bool isReady() const override;
    PendingOperation *becomeReady() override;

Q_SIGNALS:
    void listChanged(const QVector<quint32> &added, const QVector<quint32> &removed);

protected:
    explicit ContactList(ContactsApi *api);

    Q_DISABLE_COPY(ContactList)
    Q_DECLARE_PRIVATE_D(d.data(), ContactList)
    QScopedPointer<ContactListPrivate> d;
};

} // Client namespace

} // Telegram namespace

#endif // TELEGRAMQT_CONTACT_LIST_HPP
