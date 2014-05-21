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

#include <QStringList>

#include <QFile>
#include <QTextStream>

#include <stdio.h>

const static int hashMaxLength = 8;

inline int indexOfSeparator(const QString &str, int minIndex)
{
    int dotIndex = str.indexOf(QChar('.'), minIndex);
    int underscoreIndex = str.indexOf(QChar('_'), minIndex);

    if (dotIndex < 0) {
        return underscoreIndex;
    } else if (underscoreIndex < 0) {
        return dotIndex;
    }

    return dotIndex < underscoreIndex ? dotIndex : underscoreIndex;
}

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

        int separatorIndex = 0;
        while ((separatorIndex = indexOfSeparator(name, separatorIndex)) > 0) {
            if ((name.length() < separatorIndex + 1) || (!name.at(separatorIndex + 1).isLetter())) {
                printf("Bad name: %s (line %d)\n", name.toLatin1().constData(), currentLine);
                return -2;
            }
            name[separatorIndex + 1] = name.at(separatorIndex + 1).toUpper();
            name.remove(separatorIndex, 1);
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
