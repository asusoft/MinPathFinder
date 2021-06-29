#include <QtCore/QCoreApplication>
#include <QDir>
#include <QTextStream>
#include "functions.h"
#include <regex>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
       QTextStream out(stdout);

       QString graphFilePath = getPath(argv[1]);
       QString pointsFilePath = getPath(argv[2]);
       QString outFilePath = getPath(argv[3]);

       try {
           QStringList fromToPoints = readFile(pointsFilePath)[0].split(QChar(';'));
           if (fromToPoints.length() < 2)
               throw GraphError{ 9 };

           Graph graph = Graph(readFile(graphFilePath));

           int minDistance = graph.getDistanceTo(fromToPoints[0], fromToPoints[1]);
           QStringList minPath = minDistance == -1 ? QStringList() : graph.getMinPathTo(fromToPoints[0], fromToPoints[1]);

           if (minDistance == -1)
               writeToFile(outFilePath, QStringList(QString::fromUtf8(u8"Путь между указанными точками отсутствует")));
           else {
               QStringList outLines;
               QString pathLine;

               for (int i = 0; i < minPath.length(); i++)
                   pathLine += minPath[i] + "-";

               pathLine = pathLine.mid(0, pathLine.length() - 1);
               outLines.append(pathLine);
               outLines.append(QString::number(minDistance));

               writeToFile(outFilePath, outLines);
           }
       }
       catch (GraphError err) {
           try {
               QStringList outLines;
               outLines.append(getErrorMessage(err));
               writeToFile(outFilePath, outLines);
           }
           catch (GraphError err) {
               out << "\n" << getErrorMessage(err);
           }
       }

       return 0;
}
