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

#ifndef CCONTACTSMODEL_HPP
#define CCONTACTSMODEL_HPP

#include <QAbstractTableModel>
#include <QList>
#include <QStringList>
#include <QPixmap>

#include "TelegramNamespace.hpp"

struct SContact {
    SContact(const QString &p = QString(), TelegramNamespace::ContactStatus s = TelegramNamespace::ContactStatusUnknown) :
        phone(p),
        status(s),
        wasOnline(0),
        typing(false),
        blocked(false)
    { }

    QString phone;
    QString fullName;
    TelegramNamespace::ContactStatus status;
    quint32 wasOnline;
    bool typing;
    bool blocked;
    QPixmap avatar;
};

class CContactsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Columns {
        Phone,
        FullName,
        Status,
        TypingStatus,
        Avatar,
        Blocked,
        ColumnsCount
    };

    explicit CContactsModel(QObject *parent = 0);

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant data(const QString &phone, int column) const;

    int indexOfContact(const QString &phone) const;

    QStringList contacts() const;

public slots:
    void addContact(const QString &phone);
    bool removeContact(const QString &phone);
    void setContactList(const QStringList &list);
    void setContactStatus(const QString &contact, TelegramNamespace::ContactStatus status);
    void setContactLastOnline(const QString &contact, quint32 onlineDate);
    void setTypingStatus(const QString &contact, bool typingStatus);
    void setContactAvatar(const QString &contact, const QPixmap &avatar);
    void setContactFullName(const QString &contact, const QString &fullName);

private:
    QString contactStatusStr(const SContact &contact) const;

    QList<SContact> m_contacts;

};

inline int CContactsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return ColumnsCount;
}

inline int CContactsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_contacts.count();
}

#endif // CCONTACTSMODEL_HPP
