#include "TLValues.hpp"

#include <QMetaEnum>

QString TLValue::toString() const
{
    static const int index = staticMetaObject.indexOfEnumerator("Value");
    static const QMetaEnum enumerator = staticMetaObject.enumerator(index);

    return QString::fromLatin1(enumerator.valueToKey(m_value));
}
