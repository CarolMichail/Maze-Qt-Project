#ifndef TOM_H
#define TOM_H

#include <QObject>
#include <QGraphicsPixmapItem>


class Tom : public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
private:
    int row, column;
    int data[20][20];
     QTimer *timer;

public slots:
void advance();
//void doCollision();
public:
    Tom(int initialRow, int initialColumn, int d[20][20]);


};

#endif
