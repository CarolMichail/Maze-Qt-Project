#ifndef JERRY_H
#define JERRY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QList>
#include <QTimer>
#include <QPainter>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsScene>
#include "cheese.h"
#include "tom.h"
enum GameMode {Normal, Invincible};

class Jerry: public QObject, public QGraphicsPixmapItem
{ 
        Q_OBJECT
    private:
        cheese *c;
        cheese *c1;
        QPointF position;
        char direction;
        int row, column;
        int data[20][20];
        bool withCheese;
        bool isInvincible;
        bool isOver;
        GameMode mode;
        int no_cheese;
        int no_lives;
        QTimer *timer;
        QTimer *t;
        Tom *tom;
        bool inHome()

        {
            for (int i=0;i<13;i++)
                 if (data[row][column]==home[i])
                 {
                     return true;
                 }
            return false;
        }
        int jerryVertex=0;

    public:
        QGraphicsSimpleTextItem* life;
        QGraphicsSimpleTextItem* win;
        Jerry(int initialRow, int initialColumn, int d[20][20],Tom &t);
        void setRow(int newRow);
        int getRow();
        void setColumn(int newColumn);
        int getColumn();
        void WinLose(int , int);
        void JerryToNormal(Jerry& J);
        void swapJerry(Jerry& J);
        int home[13] = {100, 111, 112, 113, 124, 125, 126, 127, 128, 139, 140, 141, 151};

    public slots:
        void keyPressEvent(QKeyEvent* event);
        void move();

        void BacktoNormal();
        void Blink();
        void LifeBar();
signals:
        void ChangeLife(int newLife);
};

#endif // JERRY_H
