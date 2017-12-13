#ifndef CCONTACTSFILTERMODEL_HPP
#define CCONTACTSFILTERMODEL_HPP

#include <QSortFilterProxyModel>

class CContactsFilterModel : public QSortFilterProxyModel
{
public:
    explicit CContactsFilterModel(QObject *parent = nullptr);

    QVector<quint32> filter() const { return m_filter; }
    void setFilterList(const QVector<quint32> &filter);

    bool hasContact(quint32 id);
    void addContact(quint32 id);
    void removeContact(quint32 id);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    QVector<quint32> m_filter;

};

#endif // CCONTACTSFILTERMODEL_HPP
