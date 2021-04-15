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
#include <QDebug>

enum GameMode {Normal, Invincible};

class Jerry: public QObject, public QGraphicsPixmapItem
{ 
        Q_OBJECT
    private:
    //QLabel lifeLabel;
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
        //QPainter p;

    public:
        QGraphicsSimpleTextItem* life;
        QGraphicsSimpleTextItem* win;
        Jerry(int initialRow, int initialColumn, int d[20][20]);
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

        //void ChangeLifeSlot(int newLife);
        void BacktoNormal();
        //void Blink();
        void LifeBar();
signals:
        void ChangeLife(int newLife);
};

#endif // JERRY_H
