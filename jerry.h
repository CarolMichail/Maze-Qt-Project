#ifndef JERRY_H
#define JERRY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QList>

#include <QGraphicsScene>
class Jerry: public QObject, public QGraphicsPixmapItem
{ 
        Q_OBJECT
    private:
        char direction;
        int row, column;
        int data[10][10];
        bool withCheese;
        bool isInvincible;
    public:
        Jerry(int initialRow, int initialColumn, int d[10][10]);
        void setRow(int newRow);
        int getRow();
        void setColumn(int newColumn);
        int getColumn();
    public slots:
        void keyPressEvent(QKeyEvent* event);
        void move();
        void swapJerry(Jerry& J);

};

#endif // JERRY_H
