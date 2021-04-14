#include "tom.h"

Tom::Tom(int initialRow, int initialColumn, int d[20][20])
{
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            data[i][j] = d[i][j];
    row = initialRow;
    column = initialColumn;
    // Set Image
    QPixmap image("Tom.jpeg");
    image = image.scaledToWidth(35);
    image = image.scaledToHeight(35);
    setPixmap(image);
    // Set Position
    setPos(50 + 35 * column, 50 + 35 * row);


}
void Tom::advance()//advancing the position, responsible for moving
{
    qreal speed =5;

//if(!phase)return; // if just calling it with no animation required so dont move,
setPos(mapToParent(0, -speed));
}

