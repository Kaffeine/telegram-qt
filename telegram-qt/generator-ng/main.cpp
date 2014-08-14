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

#include <QDebug>
#include <QFile>

#include "GeneratorNG.hpp"

/* Replacing helper */
bool replaceSection(const QString &fileName, const QString &startMarker, const QString &endMarker, const QString &newContent)
{
    QFile fileToProcess(fileName);

    if (!fileToProcess.open(QIODevice::ReadOnly))
        return false;

    QString fileContent = fileToProcess.readAll();
    fileToProcess.close();

    bool winNewLines = fileContent.indexOf(QLatin1String("\r\n")) > 0;

    if (winNewLines) {
        fileContent.replace(QLatin1String("\r\n"), QLatin1String("\n"));
    }

    int startPos = fileContent.indexOf(startMarker);
    int endPos   = fileContent.indexOf(endMarker);

    if (startPos >= 0) {
        if (endPos < 0) {
            printf("There is only start marker in the file %s. Error.\n", fileName.toLocal8Bit().constData());
            return false;
        }

        endPos += endMarker.length();
    } else {
        return false;
    }

    const QString previousContent = fileContent.mid(startPos, endPos - startPos);

    if (previousContent == startMarker + newContent + endMarker) {
        printf("Nothing to do: new and previous contents are exactly same.\n");
        return true;
    }

    fileContent.remove(startPos, endPos - startPos);
    fileContent.insert(startPos, startMarker + newContent + endMarker);

    if (!fileToProcess.open(QIODevice::WriteOnly)) {
        printf("Can not write file: %s.\n", fileName.toLocal8Bit().constData());
        return false;
    }

    if (winNewLines) {
        fileContent.replace(QLatin1String("\n"), QLatin1String("\r\n"));
    }

    fileToProcess.write(fileContent.toLatin1());

    fileToProcess.close();

    printf("Replacing is done.\n");

    return true;
}

bool replacingHelper(const QString &fileName, int spacing, const QString &marker, const QString &newContent)
{
    const QString space(spacing, QChar(' '));

    if (!replaceSection(fileName,
                        QString("%1// Generated %2\n").arg(space).arg(marker),
                        QString("%1// End of generated %2\n").arg(space).arg(marker), newContent)) {
        printf("Can not update file %s with marker %s.\n", fileName.toLatin1().constData(), marker.toLatin1().constData());
        return false;
    } else {
        return true;
    }
}

/* End of replacing helper */

void debugType(const TLType &type)
{
    qDebug() << type.name;
    foreach (const TLSubType &subType, type.subTypes) {
        qDebug() << "    " << subType.name;
        foreach (const TLParam &member, subType.members) {
            qDebug() << "        " << member.type << member.name;
        }
    }
}

int main(int argc, char *argv[])
{
    QFile specsFile("json");
    specsFile.open(QIODevice::ReadOnly);

    const QByteArray data = specsFile.readAll();

    if (data.isEmpty()) {
        return 1;
    }

    specsFile.close();

    GeneratorNG generator;
    generator.loadData(data);
    generator.generate();

    replacingHelper(QLatin1String("../TLTypes.hpp"), 0, QLatin1String("TLTypes"), generator.codeOfTLTypes);
    replacingHelper(QLatin1String("../CTelegramStream.hpp"), 4, QLatin1String("read operators"), generator.codeStreamReadDeclarations);
    replacingHelper(QLatin1String("../CTelegramStream.hpp"), 4, QLatin1String("write operators"), generator.codeStreamWriteDeclarations);
    replacingHelper(QLatin1String("../CTelegramStream.cpp"), 0, QLatin1String("read operators implementation"), generator.codeStreamReadImplementation);
    replacingHelper(QLatin1String("../CTelegramStream.cpp"), 0, QLatin1String("write operators implementation"), generator.codeStreamWriteImplementation);
    replacingHelper(QLatin1String("../CTelegramConnection.hpp"), 4, QLatin1String("Telegram API methods declaration"), generator.codeConnectionDeclaration);
    replacingHelper(QLatin1String("../CTelegramConnection.cpp"), 0, QLatin1String("Telegram API methods implementation"), generator.codeConnectionImplementation);

    return 0;
}
