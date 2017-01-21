#ifndef CCONTACTSFILTERMODEL_HPP
#define CCONTACTSFILTERMODEL_HPP

#include <QSortFilterProxyModel>

class CContactsFilterModel : public QSortFilterProxyModel
{
public:
    explicit CContactsFilterModel(QObject *parent = nullptr);
    void setFilterList(const QVector<quint32> &filter);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    QVector<quint32> m_filter;

};

#endif // CCONTACTSFILTERMODEL_HPP
