#ifndef CTESTCORE_HPP
#define CTESTCORE_HPP

#include "CTelegramCore.hpp"

class CTestCore : public CTelegramCore
{
    Q_OBJECT
public:
    explicit CTestCore(QObject *parent = 0);
    void setClientNonce(TLNumber128 newClientNonce);
    void setServerNonce(TLNumber128 newServerNonce);
    void setNewNonce(TLNumber256 newNewNonce);
    void setAuthKey(const QByteArray &newKey);

    SAesKey testGenerateClientToServerAesKey(const QByteArray &messageKey) const;
};

#endif // CTESTCORE_HPP
