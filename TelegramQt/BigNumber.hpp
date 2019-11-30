#ifndef TELEGRAMQT_BIG_NUMBER_HPP
#define TELEGRAMQT_BIG_NUMBER_HPP

#include <QByteArray>

namespace Telegram {

namespace Utils {

class BigNumber
{
public:
    BigNumber();
    BigNumber(BigNumber &&number);
    BigNumber(const BigNumber &number);

    ~BigNumber();

    static BigNumber fromHex(const QByteArray &hex);
    static BigNumber fromByteArray(const QByteArray &bin);

    QByteArray toByteArray() const;

    BigNumber mod_exp(const BigNumber &exponent, const BigNumber &modulus) const;

private:
    void *d = nullptr;
};

} // Utils namespace

} // Telegram namespace

#endif // TELEGRAMQT_BIG_NUMBER_HPP
