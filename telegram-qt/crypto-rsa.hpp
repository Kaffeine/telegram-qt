/*
    Copyright (C) 2014-2015 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef CRYPTO_RSA_HPP
#define CRYPTO_RSA_HPP

#include <QByteArray>

struct SRsaKey {
    QByteArray key;
    QByteArray exp;
    quint64 fingersprint;

    inline SRsaKey(const QByteArray &initialKey = QByteArray(), const QByteArray &initialExp = QByteArray(), const quint64 initialFingersprint = 0) :
        key(initialKey), exp(initialExp), fingersprint(initialFingersprint) { }

    inline SRsaKey &operator=(const SRsaKey &anotherKey)
    {
        key = anotherKey.key;
        exp = anotherKey.exp;
        fingersprint = anotherKey.fingersprint;
        return *this;
    }
};

#endif // CRYPTO_RSA_HPP
