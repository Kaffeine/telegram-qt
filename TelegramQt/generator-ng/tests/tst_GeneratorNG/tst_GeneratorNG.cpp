#include <QObject>
#include <QTest>
#include <QDebug>

#include "GeneratorNG.hpp"

class tst_GeneratorNG : public QObject
{
    Q_OBJECT
public:
    explicit tst_GeneratorNG(QObject *parent = nullptr);
private slots:
};

tst_GeneratorNG::tst_GeneratorNG(QObject *parent) :
    QObject(parent)
{
}

QTEST_APPLESS_MAIN(tst_GeneratorNG)

#include "tst_GeneratorNG.moc"
