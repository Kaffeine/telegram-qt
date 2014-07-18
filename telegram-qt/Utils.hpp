/*
    Copyright (C) 2014 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef UTILS_HPP
#define UTILS_HPP

#include <QObject>
#include <QByteArray>

#include "crypto-rsa.hpp"
#include "crypto-aes.hpp"

class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = 0);
    static int randomBytes(QByteArray *array);
    static int randomBytes(quint64 *number);
    static int randomBytes(char *buffer, int count);
    static quint64 greatestCommonOddDivisor(quint64 a, quint64 b);
    static quint64 findDivider(quint64 number);
    static QByteArray sha1(const QByteArray &data);
    static quint64 getFingersprint(const QByteArray &data, bool lowerOrderBits = true);
    static quint64 getRsaFingersprint(const SRsaKey &key);
    static SRsaKey loadHardcodedKey();
    static SRsaKey loadRsaKeyFromFile(const QString &fileName);
    static SRsaKey loadRsaKey();
    static QByteArray binaryNumberModExp(const QByteArray &data, const QByteArray &mod, const QByteArray &exp);
    static QByteArray rsa(const QByteArray &data, const SRsaKey &key);
    static QByteArray aesDecrypt(const QByteArray &data, const SAesKey &key);
    static QByteArray aesEncrypt(const QByteArray &data, const SAesKey &key);
    static QByteArray unpackGZip(const QByteArray &data);

};

inline int Utils::randomBytes(QByteArray *array)
{
    return randomBytes(array->data(), array->size());
}

inline int Utils::randomBytes(quint64 *number)
{
    return randomBytes((char *) number, 8);
}

inline QByteArray Utils::rsa(const QByteArray &data, const SRsaKey &key)
{
    return binaryNumberModExp(data, key.key, key.exp);
}

#endif // UTILS_HPP
