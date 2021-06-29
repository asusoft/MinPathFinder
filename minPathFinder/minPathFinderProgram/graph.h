
#include <QtCore/QCoreApplication>

struct GraphError {
    int errorCode;
    int data[10];
};

class Graph
{
public:

    /// <summary>
    /// Initializes the graphic
    ///< / summary>
    /// <param name= "lines" >On the first line there is a list of points from the file, on the others there is a distance matrix</param>
    Graph(QStringList lines);

    /// <summary>
    /// Returns the distance from a point to a point in the graph
    /// </summary>
    /// <param name="pointName">Point name< / param>
    /// <returns>The distance from the specified point to the calculated one. If the points are not connected, returns -1</returns>
    int getDistanceTo(QString fromPointName, QString toPointName);

    /// <summary>
    /// Returns the complete shortest path from point to point in the graph
    ///</summary>
    /// <param name="pointName"></param>
    /// <returns>A list of point names that represent the shortest path. If the points are not connected, returns an empty list</returns>
    QStringList getMinPathTo(QString fromPointName, QString toPointName);

    QStringList getPointNames();
    QList<QList<int>> getDistanceMatrix();

private:
    /// <summary>
    /// A sequential list of the names of all points in the graph
    /// </summary>
    QStringList pointNames;

    /// <summary>
    /// Weighted adjacency matrix
    /// </summary>
    QList<QList<int>> distancesMatrix;

    /// <summary>
    /// The index of the point from which the calculation was made using Dijkstra's algorithm
    /// </summary>
    int originPointIndex;

    /// <summary>
    /// The name of the point from where the calculation was performed using Dijkstra's algorithm
    /// </summary>
    QString originPointName;

    /// <summary>
    /// List of placemarks calculated by Dijkstra's algorithm for a specific point
    /// </summary>
    QList<int> pointLabels;

    /// <summary>
    /// Calculates the distance to all points of the graph from a certain point
    /// </summary>
    /// <param name="point Name">The point to calculate the distance to </param>
    void calculateLabelsFromPoint(QString pointName);

    /// <summary>
    /// Returns the numeric index of a point by its name
    /// </summary>
    ///<param name="point Name">Point name</param>
    /// <returns>The index of the point. -1 if such a point does not exist in the graph</returns>
    int getPointIndex(QString pointName);

    /// <summary>
    /// Finds the index of the minimum value in the list
    /// </summary>
    /// <param name= "list" >List of values</param>
    /// <returns>Index of the minimum value</returns>
    int getIndexOfMin(QList<int> list);

    /// <summary>
    /// Returns the distance to all points from the specified
    /// < / summary>
    /// <param name="to Point">Index of the point from which we are looking for the distance</param>
    /// <returns>List of distances to all points</returns>
    QList<int> getConnectedPoints(int toPoint);
};
