/*
    Copyright (C) 2015 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "TLValues.hpp"

#include <QMetaEnum>

QString TLValue::toString() const
{
    static const int index = staticMetaObject.indexOfEnumerator("Value");
    static const QMetaEnum enumerator = staticMetaObject.enumerator(index);

    const char *value = enumerator.valueToKey(m_value);
    if (value) {
        return QString::fromLatin1(value);
    } else {
        return QString(QLatin1String("%1")).arg(m_value, 8, 16, QLatin1Char('0'));
    }
}
