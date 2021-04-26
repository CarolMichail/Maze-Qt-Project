#include "tom.h"
#include "jerry.h"

Tom::Tom(int initialRow, int initialColumn, int d[20][20])
{
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            data[i][j] = d[i][j];
    row = initialRow;
    column = initialColumn;
    // Set Image
    QPixmap image("tomm.png");
    image = image.scaledToWidth(35);
    image = image.scaledToHeight(35);
    setPixmap(image);
    // Set Position
    setPos(50 + 35 * column, 50 + 35 * row);

}
/*void Tom:: movement()
{
    if(data[row][column] != -10);
}*/
void Tom::advance()//advancing the position, responsible for moving
{
    qreal speed = 5;
    RandMotion();


//if(!phase)return; // if just calling it with no animation required so dont move,
setPos(mapToParent(0, -speed));
}

void Tom::RandMotion()
{
    srand(time(NULL));
    int x = qrand()% 4 + 1;
    //for ( int i=0; i < 13; i++)
    //{
        if (x==1 && data[row - 1][column] != -10)// && data[row - 1][column] != home[i])
        {
            int i;
            for (i=0; i < 13; i++)
                if (data[row - 1][column] == home[i])
                    break;
            if (i == 13)
                row--;
        }
        else if (x==2 && data[row + 1][column] != -10)// && data[row + 1][column] != home[i])
        {
            int i;
            for (i=0; i < 13; i++)
                if (data[row + 1][column] == home[i])
                    break;
            if (i == 13)
            row++;
        }
        else if (x==3 && data[row][column + 1] != -10)// && data[row][column + 1] != home[i])
        {
            int i;
            for (i=0; i < 13; i++)
                if (data[row][column + 1] == home[i])
                    break;
            if (i == 13)
            column++;
        }
        else if (x==4 && data[row][column - 1] != -10)// && data[row][column - 1] != home[i])
        {
            int i;
            for (i=0; i < 13; i++)
                if (data[row][column - 1] == home[i])
                    break;
            if (i == 13)
            column--;
        }
    //}
    setPos(50 + 35 * column, 50 + 35 * row);
}








