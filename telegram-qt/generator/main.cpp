#include <QStringList>

#include <QFile>
#include <QTextStream>

#include <stdio.h>

const static int hashMaxLength = 8;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <source>\n", argv[0]);
        return 0;
    }

    QFile sourceFile(QString::fromLatin1(argv[1]));

    if (!sourceFile.open(QIODevice::ReadWrite))
        return -1;

    QTextStream input(&sourceFile);

    int currentLine = 0;
    while (!input.atEnd()) {
        QString line = input.readLine();
        ++currentLine;

        if (line.simplified().isEmpty() || (line.startsWith(QLatin1String("---")) && line.endsWith(QLatin1String("---")))) {
            continue;
        }

        int hashIndex = line.indexOf(QChar('#'));
        if ((hashIndex < 1) || (hashIndex + 1 > line.length())) {
            printf("Bad string: %s (line %d)\n", line.toLatin1().constData(), currentLine);
            return -1;
        }

        QString name = line.left(hashIndex);

        name[0] = name.at(0).toUpper();

        int dotIndex = 0;
        while ((dotIndex = name.indexOf(QChar('.'), dotIndex)) > 0) {
            if ((name.length() < dotIndex + 1) || (!name.at(dotIndex + 1).isLetter())) {
                printf("Bad name: %s (line %d)\n", name.toLatin1().constData(), currentLine);
                return -2;
            }
            name[dotIndex + 1] = name.at(dotIndex + 1).toUpper();
            name.remove(dotIndex, 1);
        }

        QString value = line.mid(hashIndex + 1, hashMaxLength);
        int endOfValue = value.indexOf(QChar(' '));
        if (endOfValue > 0) {
            value.truncate(endOfValue);
        }
//        printf("Line %d: name: %s, value: %s\n", currentLine, name.toLatin1().constData(), value.toLatin1().constData());

        if (!input.atEnd())
            printf("%s = 0x%s,\n", name.toLatin1().constData(), value.toLatin1().constData());
        else
            printf("%s = 0x%s\n", name.toLatin1().constData(), value.toLatin1().constData());
    }

    return 0;
}
