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

class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = 0);
    static int randomBytes(char *buffer, int count);
    static quint64 greatestCommonOddDivisor(quint64 a, quint64 b);
    static quint64 findDivider(quint64 number);
    static QByteArray sha1(const QByteArray &data);
    static SRsaKey loadKey();
    static QByteArray rsa(const QByteArray &data, const SRsaKey &key);

};

#endif // UTILS_HPP
