#include <QtCore/QCoreApplication>
#include <QDir>
#include <QTextStream>
#include "functions.h"
#include <regex>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
       QTextStream out(stdout);

       QString graphFilePath = getFileDirectory(argv[1]);
       QString pointsFilePath = getFileDirectory(argv[2]);
       QString outFilePath = getFileDirectory(argv[3]);

       try {
           QStringList fromToPoints = getDataFromFile(pointsFilePath)[0].split(QChar(';'));
           if (fromToPoints.length() < 2)
               throw GraphError{ 9 };

           Graph graph = Graph(getDataFromFile(graphFilePath));

           int minDistance = graph.getDistanceTo(fromToPoints[0], fromToPoints[1]);
           QStringList minPath = minDistance == -1 ? QStringList() : graph.getMinPathTo(fromToPoints[0], fromToPoints[1]);

           if (minDistance == -1)
               writeToOutputFile(outFilePath, QStringList(QString::fromUtf8(u8"There is no path from source to destination point")));
           else {
               QStringList outLines;
               QString pathLine;

               for (int i = 0; i < minPath.length(); i++)
                   pathLine += minPath[i] + "-";

               pathLine = pathLine.mid(0, pathLine.length() - 1);
               outLines.append(pathLine);
               outLines.append(QString::number(minDistance));

               writeToOutputFile(outFilePath, outLines);
           }
       }
       catch (GraphError err) {
           try {
               QStringList outLines;
               outLines.append(getErrorMessage(err));
               writeToOutputFile(outFilePath, outLines);
           }
           catch (GraphError err) {
               out << getErrorMessage(err);
           }
       }

       return 0;
}
