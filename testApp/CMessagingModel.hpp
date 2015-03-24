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

#ifndef CMESSAGINGMODEL_HPP
#define CMESSAGINGMODEL_HPP

#include <QAbstractTableModel>

#include "TelegramNamespace.hpp"

struct SMessageEntry {
    SMessageEntry(const QString &p = QString(), const QString &m = QString(), quint64 id = 0, quint32 t = 0,
                  TelegramNamespace::MessageDeliveryStatus s = TelegramNamespace::MessageDeliveryStatusUnknown) :
        phone(p),
        message(m),
        messageId(id),
        timestamp(t),
        status(s),
        outgoing(true)
    { }

    QString phone;
    QString message;
    quint64 messageId;
    quint32 timestamp;
    TelegramNamespace::MessageDeliveryStatus status;
    QVariant mediaData;
    bool outgoing;
};

class CMessagingModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Columns {
        Phone,
        Direction,
        Timestamp,
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

    int messageIndex(quint64 messageId) const; // Messages id should be quint32, but it require "outgoing random to incremental message id resolving" (Not implemented yet).

public slots:
    void addMessage(const QString &phone, const QString &message, TelegramNamespace::MessageType type, bool outgoing, quint64 messageId = 0, quint32 timestamp = 0);
    int setMessageMediaData(quint64 messageId, const QVariant &data);
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
