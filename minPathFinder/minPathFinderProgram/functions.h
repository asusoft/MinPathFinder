#include "graph.h"

QStringList readFile(QString absolutePath);

void writeToFile(QString absolutePath, QStringList lines);

QString getPath(char* path);

QString getErrorMessage(GraphError err);
