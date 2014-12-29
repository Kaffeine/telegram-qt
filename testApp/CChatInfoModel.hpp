#ifndef CCHATINFOMODEL_HPP
#define CCHATINFOMODEL_HPP

#include <QAbstractTableModel>

#include "TelegramNamespace.hpp"

class CChatInfoModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Columns {
        Id,
        Title,
        ParticipantsCount,
        ColumnsCount
    };

    explicit CChatInfoModel(QObject *parent = 0);

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void addChat(int id);
    bool haveChat(quint32 id);
    void setChat(const TelegramNamespace::GroupChat &chat);

private:
    QList<TelegramNamespace::GroupChat> m_chats;

};

inline int CChatInfoModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return ColumnsCount;
}

inline int CChatInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_chats.count();
}

#endif // CCHATINFOMODEL_HPP
