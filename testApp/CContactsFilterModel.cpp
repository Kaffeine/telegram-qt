#include "CContactsFilterModel.hpp"

#include "CContactModel.hpp"

CContactsFilterModel::CContactsFilterModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

void CContactsFilterModel::setFilterList(const QVector<quint32> &filter)
{
    m_filter = filter;
    invalidateFilter();
}

bool CContactsFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (sourceParent.isValid()) {
        return false;
    }

    const quint32 id = sourceModel()->index(sourceRow, CContactModel::Id).data().toUInt();
    return m_filter.contains(id);
}
