#ifndef JERRY_H
#define JERRY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsScene>
#include "cheese.h"
#include "tom.h"

enum GameMode {Normal, Invincible};

class Jerry: public QObject, public QGraphicsPixmapItem
{ 
    Q_OBJECT
    private:
        QPointF C_Position;
        QTimer *timer;
        Tom *tom;
        cheese *c_home;
        cheese *c_return;
        char direction;
        int row, column;
        int no_cheese;
        int no_lives;
        int data[20][20];
        int home[9] = { 111, 112, 113, 125, 126, 127, 140, 141, 142};
        bool withCheese;
        bool isInvincible;
        bool isOver;
        GameMode mode;
        inline bool inHome()

        {
            for (int i=0;i<9;i++)
                 if (data[row][column]==home[i])
                 {
                     return true;
                 }
            return false;
        }

    public:
        QGraphicsSimpleTextItem* life;
        QGraphicsSimpleTextItem* win;
        Jerry(int initialRow, int initialColumn, int d[20][20],Tom &t);
        void WinLose(int , int);
        void JerryToNormal();
        void JerryToCheese();
        void LifeBar();
        
    public slots:
        void keyPressEvent(QKeyEvent* event);
        void move();
        void BacktoNormal();
};

#endif // JERRY_H
