#include "CContactsFilterModel.hpp"

#include "CContactModel.hpp"

#include <QDebug>

CContactsFilterModel::CContactsFilterModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

void CContactsFilterModel::setFilterList(const QVector<quint32> &filter)
{
    if (filter == m_filter) {
        return;
    }
    qDebug() << Q_FUNC_INFO << filter;
    m_filter = filter;
    invalidateFilter();
}

bool CContactsFilterModel::hasContact(quint32 id)
{
    return m_filter.contains(id);
}

void CContactsFilterModel::addContact(quint32 id)
{
    if (m_filter.contains(id)) {
        return;
    }
    m_filter.append(id);
    invalidateFilter();
}

void CContactsFilterModel::removeContact(quint32 id)
{
#if QT_VERSION >= 0x050000
    m_filter.removeAll(id);
#else
    const int index = m_filter.indexOf(id);
    if (index >= 0) {
        m_filter.remove(index);
    }
#endif
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
