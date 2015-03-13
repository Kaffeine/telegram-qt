#include "TLValues.hpp"

#include <QMetaEnum>

QString TLValue::toString() const
{
//    return QString(QLatin1String("%1")).arg(m_value, 8, 16, QLatin1Char('0'));
    static const int index = staticMetaObject.indexOfEnumerator("Value");
    static const QMetaEnum enumerator = staticMetaObject.enumerator(index);

    return QString::fromLatin1(enumerator.valueToKey(m_value));
}
