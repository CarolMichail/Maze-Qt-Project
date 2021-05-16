#ifndef TOM_H
#define TOM_H

#include <QVector>
#include <QObject>
#include <QGraphicsPixmapItem>

const int COUNT =231;
const int INFINITE=9999;
class Tom : public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
private:
    int row, column;
    int jerryVertex;
    int data[20][20];
    int home[9] = { 111, 112, 113, 125, 126, 127, 140, 141, 142};
    bool moving = true;
    QTimer *timer;
    inline bool inHome(int vertex)
    {
        for (int i=0;i<9;i++)
            if (vertex == home[i])
            {
                return true;
            }
        return false;
    }
    QVector<QVector<int> > Dijkstra(int Graph[COUNT][COUNT], int startVertex);

public slots:
     void RandMotion();
     void UpdateMotion();

public:
    Tom(int initialRow, int initialColumn, int d[20][20]);
    void SetJerryVertex(int v);
    int adjMatrix[COUNT][COUNT];
    void stoppMoving();
    void ReturnToOriginalPos();
};

#endif
