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

#ifndef CRYPTOAES_HPP
#define CRYPTOAES_HPP

#include <QByteArray>

struct SAesKey {
    QByteArray key;
    QByteArray iv;

    inline SAesKey(const QByteArray &initialKey = QByteArray(), const QByteArray &initialIV = QByteArray()) :
        key(initialKey), iv(initialIV) { }

    inline SAesKey &operator=(const SAesKey &anotherKey)
    {
        key = anotherKey.key;
        iv  = anotherKey.iv;
        return *this;
    }
};

#endif // CRYPTOAES_HPP
