#include "CTestDispatcher.hpp"

CTestDispatcher::CTestDispatcher(QObject *parent) :
    CTelegramDispatcher(parent)
{
}

void CTestDispatcher::testProcessUpdate(const TLUpdate &update)
{
    return processUpdate(update);
}

void CTestDispatcher::testSetDcConfiguration(const QVector<TLDcOption> newDcConfiguration)
{
    m_dcConfiguration = newDcConfiguration;
}
