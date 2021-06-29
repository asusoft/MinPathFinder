#include "graph.h"

/*! Gets all data in a file
\param[in] file file to be read
\throw error while reading file
\return lines lines of the file
*/
QStringList getDataFromFile(QString absolutePath);

/*! Writes output data
  \param[in] filePath file to write in
  \param[in] lines lines of output data
*/
void writeToOutputFile(QString filePath, QStringList lines);

/// <summary>
/// Gets the absolute path to a file
/// <param name="path">absolute path to the file</param>
/// </summary>
QString getFileDirectory(char* path);

/// <summary>
/// Gets the error that happen while execution
/// <param name="err">error number</param>
/// <returns> error message</returns>
/// </summary>
QString getErrorMessage(GraphError err);
