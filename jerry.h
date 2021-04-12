#ifndef JERRY_H
#define JERRY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QList>

#include <QGraphicsScene>

enum GameMode {Normal, Invincible};

class Jerry: public QObject, public QGraphicsPixmapItem
{ 
        Q_OBJECT
    private:
        char direction;
        int row, column;
        int data[10][10];
        bool withCheese;
        bool isInvincible;
        GameMode mode;
        int no_cheese;
        int no_lives;
    public:
        Jerry(int initialRow, int initialColumn, int d[10][10]);
        void setRow(int newRow);
        int getRow();
        void setColumn(int newColumn);
        int getColumn();
        void WinLose(int , int);
        void LifeBar();
    public slots:
        void keyPressEvent(QKeyEvent* event);
        void move();
        void swapJerry(Jerry& J);

};

#endif // JERRY_H
