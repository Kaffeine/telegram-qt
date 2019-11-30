#include "BigNumber_p.hpp"
#include "BigNumber.hpp"

namespace Telegram {

namespace Utils {

BigNumber::BigNumber()
{
    BIGNUM *&own = getBigNum(d);
    own = BN_new();
}

BigNumber::BigNumber(BigNumber &&number) :
    d(number.d)
{
    number.d = nullptr;
}

BigNumber::BigNumber(const BigNumber &number) :
    BigNumber()
{
    BIGNUM *&own = getBigNum(d);
    const BIGNUM *their = getBigNum(number.d);
    BN_copy(own, their);
}

BigNumber::~BigNumber()
{
    if (d) {
        BIGNUM *&own = getBigNum(d);
        BN_free(own);
    }
}

BigNumber BigNumber::fromHex(const QByteArray &hex)
{
    BigNumber result;
    BIGNUM *&own = getBigNum(result.d);

    if (BN_hex2bn(&own, hex.constData()) != 0) {
        return result;
    }
    return BigNumber();
}

BigNumber BigNumber::fromByteArray(const QByteArray &bin)
{
    BigNumber result;
    BIGNUM *&own = getBigNum(result.d);
    if (BN_bin2bn((uchar *) bin.constData(), bin.length(), own) != 0) {
        return result;
    }
    return BigNumber();
}

QByteArray BigNumber::toByteArray() const
{
    const BIGNUM *own = getBigNum(d);
    return bignumToByteArray(own);
}

BigNumber BigNumber::mod_exp(const BigNumber &exponent, const BigNumber &modulus) const
{
    BigNumber result;
    SslBigNumberContext context;

    BIGNUM *&resultBN = getBigNum(result.d);
    const BIGNUM *argumentBN = getBigNum(d);
    const BIGNUM *exponentBN = getBigNum(exponent.d);
    const BIGNUM *modulusBN = getBigNum(modulus.d);

    BN_mod_exp(resultBN, argumentBN, exponentBN, modulusBN, context.context());
    return result;
}

} // Utils namespace

} // Telegram namespace
