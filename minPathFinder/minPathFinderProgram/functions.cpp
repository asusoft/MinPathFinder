#include "functions.h"
#include <QTextStream>
#include <QDir>

#include <regex>

QRegExp rx("*.txt");

QStringList getDataFromFile(QString absolutePath) {
    rx.setPatternSyntax(QRegExp::Wildcard);

    QStringList result;
    QFile inputFile(absolutePath);

    if (!rx.exactMatch(inputFile.fileName()))
        throw GraphError{ 6 };

    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&inputFile);
        in.setCodec("UTF-8");

        while (!in.atEnd())
        {
            QString line = in.readLine();
            result.append(line);
        }

        inputFile.close();
    }
    else
        throw GraphError{ 7 };

    return result;
}

void writeToOutputFile(QString absolutePath, QStringList lines) {
    QFile outputFile(absolutePath);

    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&outputFile);
        stream.setGenerateByteOrderMark(true);
        stream.setCodec("UTF-8");

        for (int i = 0; i < lines.length(); i++)
            stream << lines[i] << endl;

        outputFile.close();
    }
    else
        throw GraphError{ 8 };
}

QString getFileDirectory(char* dir) {
    QString result(dir);

    if (result.startsWith(QChar('.')))
        result = QDir::currentPath() + result.mid(1);

    return result;
}

QString getErrorMessage(GraphError err) {
    switch (err.errorCode)
    {
        case 0:
            return QString::fromUtf8(u8"The number of points should be the same as the number of rows in the adjacency matrix.");
        case 1:
            return QString::fromUtf8(u8"Points should be more than one.");
        case 2:
            return QString::fromUtf8(u8"The number of points should be the same as the number of elements in each row of the adjacency matrix.");
        case 3:
            return QString::fromUtf8(u8"Error! Elements must be in positive format");
        case 4:
            return QString::fromUtf8(u8"The points cannot be connected to themselves.");
        case 5:
            return QString::fromUtf8(u8"The end or start point was not found in the list of all points.");
        case 6:
            return QString::fromUtf8(u8"The file extension is specified incorrectly. The file must have the .txt extension");
        case 7:
            return QString::fromUtf8(u8"The input file cannot be accessed. The file may not exist");
        case 8:
            return QString::fromUtf8(u8"The output file cannot be created.");
        case 9:
            return QString::fromUtf8(u8"The source and destination points missing or it is entered incorrectly.");
        default:
            return QString::fromUtf8(u8"Unknown error occured");
    }
}
