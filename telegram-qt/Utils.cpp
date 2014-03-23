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

#include "Utils.hpp"

#include <openssl/rand.h>

#include <QCryptographicHash>

Utils::Utils(QObject *parent) :
    QObject(parent)
{
}

int Utils::randomBytes(char *buffer, int count)
{
    return RAND_bytes((unsigned char *) buffer, count);
}

// Slightly modified version of Euclidean algorithm. Once we are looking for prime numbers, we can drop parity of asked numbers.
quint64 Utils::greatestCommonOddDivisor(quint64 a, quint64 b)
{
    while (a != 0 && b != 0) {
        while (!(b & 1)) {
            b >>= 1;
        }
        while (!(a & 1)) {
            a >>= 1;
        }
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }
    return b == 0 ? a : b;
}

// Yet another copy of some unknown pq-solver algorithm.
// Links:
// https://github.com/DrKLO/Telegram/blob/433f59c5b9ed17543d8e206c83f0bc7c7edb43a6/TMessagesProj/jni/jni.c#L86
// https://github.com/ex3ndr/telegram-mt/blob/91b1186e567b0484d6f371b8e5c61c425daf867e/src/main/java/org/telegram/mtproto/secure/pq/PQLopatin.java#L35
// https://github.com/vysheng/tg/blob/1dad2e89933085ea1e3d9fb1becb1907ce5de55f/mtproto-client.c#L296
quint64 Utils::findDivider(quint64 number)
{
    int it = 0;
    unsigned long long g = 0;
    for (int i = 0; i < 3 || it < 10000; i++) {
        int q = ((lrand48() & 15) + 17) % number;
        unsigned long long x = (long long)lrand48 () % (number - 1) + 1, y = x;
        int lim = 1 << (i + 18);
        int j;
        for (j = 1; j < lim; j++) {
            ++it;
            unsigned long long a = x, b = x, c = q;
            while (b) {
                if (b & 1) {
                    c += a;
                    if (c >= number) {
                        c -= number;
                    }
                }
                a += a;
                if (a >= number) {
                    a -= number;
                }
                b >>= 1;
            }
            x = c;
            unsigned long long z = x < y ? number + x - y : x - y;
            g = greatestCommonOddDivisor (z, number);
            if (g != 1) {
                return g;
            }
            if (!(j & (j - 1))) {
                y = x;
            }
        }
        if (g > 1 && g < number) {
            return g;
        }
    }

    return 1;
}

QByteArray Utils::sha1(const QByteArray &data)
{
    return QCryptographicHash::hash(data, QCryptographicHash::Sha1);
}
