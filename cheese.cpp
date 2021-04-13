#include "cheese.h"

cheese::cheese(int initialRow, int initialColumn)
{
    // Set Image
    QPixmap image("Cheese.png");
    image = image.scaledToWidth(35);
    image = image.scaledToHeight(35);
    setPixmap(image);
    // Set Position
    setPos(50 + 35 * initialColumn, 50 + 35 * initialRow);
}
