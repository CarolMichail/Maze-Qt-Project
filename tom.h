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
    int data[20][20];
     QTimer *timer;
     bool inHome(int vertex)

     {
         for (int i=0;i<13;i++)
              if (vertex==home[i])
              {
                  return true;
              }
         return false;
     }

        QVector<QVector<int> > Dijkstra(int Graph[COUNT][COUNT], int startVertex);
      bool moving=true;
      int jerryVertex;


public slots:
     void RandMotion();
     void advance();
     void UpdateMotion();

public:
    Tom(int initialRow, int initialColumn, int d[20][20]);
    int home[13] = {100, 111, 112, 113, 124, 125, 126, 127, 128, 139, 140, 141, 151};
    int step;
    void SetJerryVertex(int v);
    int adjMatrix[COUNT][COUNT];
    void stoppMoving();
    void ReturnToOriginalPos();
};

#endif
