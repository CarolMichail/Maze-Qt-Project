#ifndef PELLET_H
#define PELLET_H

#include <QGraphicsPixmapItem>

class pellet : public QGraphicsPixmapItem
{
public:
    pellet(int initialRow, int initialColumn);
};

#endif // PELLET_H
