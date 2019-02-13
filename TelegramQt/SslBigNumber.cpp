#include "SslBigNumber.hpp"

#include <openssl/bn.h>

namespace Telegram {

namespace Utils {

struct SslBigNumberContext {
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

SslBigNumber::SslBigNumber() :
    m_number(BN_new())
{
}

SslBigNumber::SslBigNumber(SslBigNumber &&other) :
    m_number(other.m_number)
{
    other.m_number = nullptr;
}

SslBigNumber::SslBigNumber(const SslBigNumber &other) :
    m_number(BN_new())
{
    BN_copy(m_number, other.m_number);
}

SslBigNumber::~SslBigNumber()
{
    if (m_number) {
        BN_free(m_number);
    }
}

SslBigNumber SslBigNumber::fromHex(const QByteArray &hex)
{
    SslBigNumber result;
    if (BN_hex2bn(&result.m_number, hex.constData()) != 0) {
        return result;
    }
    return SslBigNumber();
}

SslBigNumber SslBigNumber::fromByteArray(const QByteArray &bin)
{
    SslBigNumber result;
    if (BN_bin2bn((uchar *) bin.constData(), bin.length(), result.m_number) != 0) {
        return result;
    }
    return SslBigNumber();
}

QByteArray SslBigNumber::toByteArray(const BIGNUM *number)
{
    QByteArray result;
    result.resize(BN_num_bytes(number));
    BN_bn2bin(number, (uchar *) result.data());
    return result;
}

QByteArray SslBigNumber::toByteArray() const
{
    return toByteArray(m_number);
}

SslBigNumber SslBigNumber::mod_exp(const SslBigNumber &exponent, const SslBigNumber &modulus) const
{
    SslBigNumberContext context;
    SslBigNumber result;
    BN_mod_exp(result.m_number, number(), exponent.number(), modulus.number(), context.context());
    return result;
}

} // Utils namespace

} // Telegram namespace
