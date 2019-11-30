#ifndef TELEGRAMQT_BIG_NUMBER_P_HPP
#define TELEGRAMQT_BIG_NUMBER_P_HPP

#include <QByteArray>

#include <openssl/bn.h>

namespace Telegram {

namespace Utils {

struct SslBigNumberContext
{
    SslBigNumberContext() :
        m_context(BN_CTX_new())
    {
    }

    ~SslBigNumberContext()
    {
        BN_CTX_free(m_context);
    }

    BN_CTX *context() { return m_context; }

private:
    BN_CTX *m_context = nullptr;
};

inline BIGNUM *&getBigNum(void *&pointer)
{
    return reinterpret_cast<BIGNUM*&>(pointer);
}

inline const BIGNUM *getBigNum(const void *pointer)
{
    return reinterpret_cast<const BIGNUM*>(pointer);
}

static QByteArray bignumToByteArray(const BIGNUM *number)
{
    QByteArray result;
    result.resize(BN_num_bytes(number));
    BN_bn2bin(number, (uchar *) result.data());
    return result;
}

} // Utils namespace

} // Telegram namespace

#endif // TELEGRAMQT_BIG_NUMBER_P_HPP
