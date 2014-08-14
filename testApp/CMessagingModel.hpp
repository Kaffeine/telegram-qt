#ifndef CMESSAGINGMODEL_HPP
#define CMESSAGINGMODEL_HPP

#include <QAbstractTableModel>

#include "TelegramNamespace.hpp"

struct SMessageEntry {
    SMessageEntry(const QString &p = QString(), const QString &m = QString(), quint64 id = 0,
                  TelegramNamespace::MessageDeliveryStatus s = TelegramNamespace::MessageDeliveryStatusUnknown) :
        phone(p),
        message(m),
        messageId(id),
        status(s)
    { }

    QString phone;
    QString message;
    quint64 messageId;
    TelegramNamespace::MessageDeliveryStatus status;
};

class CMessagingModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Columns {
        Phone,
        MessageId,
        Message,
        Status,
        ColumnsCount
    };

    explicit CMessagingModel(QObject *parent = 0);

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

public slots:
    void addMessage(const QString &phone, const QString &message, quint64 messageId = 0);
    void setMessageDeliveryStatus(const QString &phone, quint64 messageId, TelegramNamespace::MessageDeliveryStatus status);

private:
    QList<SMessageEntry> m_messages;

};

inline int CMessagingModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return ColumnsCount;
}

inline int CMessagingModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_messages.count();
}

#endif // CMESSAGINGMODEL_HPP
