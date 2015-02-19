#ifndef CTESTDISPATCHER_HPP
#define CTESTDISPATCHER_HPP

#include "CTelegramDispatcher.hpp"

class CTestDispatcher : public CTelegramDispatcher
{
    Q_OBJECT
public:
    explicit CTestDispatcher(QObject *parent = 0);

    void testProcessUpdate(const TLUpdate &update);
    void testSetDcConfiguration(const QVector<TLDcOption> newDcConfiguration);
    QVector<TLDcOption> testGetDcConfiguration() const { return m_dcConfiguration; }

};

#endif // CTESTDISPATCHER_HPP
