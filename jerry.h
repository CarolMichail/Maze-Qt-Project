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
        GameMode mode;
        int no_cheese;
        int no_lives;
        QTimer *timer;
        QTimer *t;
        //QPainter p;

    public:
                QGraphicsSimpleTextItem* life;
        Jerry(int initialRow, int initialColumn, int d[20][20]);
        void setRow(int newRow);
        int getRow();
        void setColumn(int newColumn);
        int getColumn();
        void WinLose(int , int);
        void LifeBar();
        void BacktoNormal();
        void Blink();
    public slots:
        void keyPressEvent(QKeyEvent* event);
        void move();
        void swapJerry(Jerry& J);
        void ChangeLifeSlot(int newLife);
signals:
        void ChangeLife(int newLife);
};

#endif // JERRY_H
