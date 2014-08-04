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
        typing(false)
    { }

    QString phone;
    QString fullName;
    TelegramNamespace::ContactStatus status;
    bool typing;
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
        ColumnsCount
    };

    explicit CContactsModel(QObject *parent = 0);

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant data(const QString &phone, int column) const;

    int indexOfContact(const QString &phone) const;

public slots:
    void setContactList(const QStringList &list);
    void setContactStatus(const QString &phone, TelegramNamespace::ContactStatus status);
    void setTypingStatus(const QString &phone, bool typingStatus);
    void setContactAvatar(const QString &phone, const QString &avatarFileName);
    void setContactFullName(const QString &phone, const QString &fullName);

private:
    QString statusToStr(TelegramNamespace::ContactStatus status) const;

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
