#ifndef CHEESE_H
#define CHEESE_H

#include <QGraphicsPixmapItem>

class cheese : public QGraphicsPixmapItem
{
public:
    cheese(int initialRow, int initialColumn);
};

#endif // CHEESE_H
