#ifndef TOM_H
#define TOM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "jerry.h"

class Tom : public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
private:
    int row, column;
    int data[20][20];
     QTimer *timer;

     //void movement();

public slots:
     void RandMotion();
     void advance();
     //void doCollision();
public:
    Tom(int initialRow, int initialColumn, int d[20][20]);
    int home[13] = {100, 111, 112, 113, 124, 125, 126, 127, 128, 139, 140, 141, 151};


};

#endif
