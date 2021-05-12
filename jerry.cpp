#include "jerry.h"
#include "cheese.h"
#include "pellet.h"
#include "tom.h"

//image.fill(Qt::transparent); //fills with transparent

Jerry::Jerry(int initialRow, int initialColumn, int d[20][20])
{
    win = new QGraphicsSimpleTextItem;
    life = new QGraphicsSimpleTextItem;
    life->setPos(10,10);
    for (int i =0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            data[i][j] = d[i][j];
    // Set Image
    QPixmap image("JerrySmallSquared.png");
    image = image.scaledToWidth(35);
    image = image.scaledToHeight(35);
    setPixmap(image);
    // Set Position
    setPos(50 + 35 * initialColumn, 50 + 35 * initialRow);
    row = initialRow;
    column = initialColumn;
    withCheese = false;
    isInvincible = false;
    no_lives = 3;
    no_cheese = 0;
    timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(Blink()));
    t = new QTimer(this);
    isOver=false;
    mode = Normal;
    LifeBar();
    //PixMap(image);
}
void Jerry::setRow(int newRow)
{ row = newRow; }
int Jerry::getRow()
{ return row; }
void Jerry::setColumn(int newColumn)
{ column = newColumn; }
int Jerry::getColumn()
{ return column; }
void Jerry::keyPressEvent(QKeyEvent* event)
{
    if (!isOver){
    if (event->key() == Qt::Key_Up)
    {
        direction = 'u';
    }
    else if (event->key() == Qt::Key_Down)
    {
        direction = 'd';
    }
    else if (event->key() == Qt::Key_Right)
    {
        direction = 'r';
    }
    else if (event->key() == Qt::Key_Left)
    {
        direction = 'l';
    }
    }
}

void Jerry::move()
{
    if (direction == 'u' && data[row - 1][column] != -10 && data[row - 1][column] != -20)
    {
        row--;
    }
    else if (direction == 'd' && data[row + 1][column] != -10 && data[row + 1][column] != -20)
    {
        row++;
    }
    else if (direction == 'r' && data[row][column + 1] != -10 && data[row][column + 1] != -20)
    {
        column++;
    }
    else if (direction == 'l' && data[row][column - 1] != -10 && data[row][column - 1] != -20)
    {
        column--;
    }
    setPos(50 + 35 * column, 50 + 35 * row);

    for (int i = 0; i < 13;i++)
    {
    if (data[row][column] == home[i]) //Not -20
        if (withCheese)
        {
            WinLose(no_lives, ++no_cheese);
            withCheese= false;
            JerryToNormal(*this);
            LifeBar();
            if (no_cheese == 1)
            {
                 c = new cheese(9, 9);
                 scene()->addItem(c);
            }
            else if (no_cheese == 2)
            {
                c = new cheese(9, 11);
                scene()->addItem(c);
            }
            else if (no_cheese == 3)
            {
                c = new cheese(11, 9);
                scene()->addItem(c);
            }
            else if (no_cheese == 4)
            {
                c = new cheese(11, 11);
                scene()->addItem(c);
            }
        }
    }

#include <QDebug>

   QList<QGraphicsItem*> items = collidingItems();
    for (int i = 0; i < items.size(); i++)
    {


        if (typeid(*items[i]) == typeid(cheese))
        {
            if (!withCheese)
            {
                //*(items[i])->isHome = true;
                scene()->removeItem(items[i]);
                position = (*items[i]).pos();
                swapJerry(*this);
                withCheese = true;
            }
        }
        else if (typeid(*items[i]) == typeid(pellet))
        {
            scene()->removeItem(items[i]);
            mode = Invincible;
            isInvincible =true;
            //Opacity***

            //DONE: Timer --> 5 seconds to change back to normal --> New function is required to change to normal
            timer->start(5000); //5000 milliseconds
            connect(timer, SIGNAL(timeout()), this, SLOT(BacktoNormal()));
            LifeBar();
        }
        else if (typeid(*items[i]) == typeid(Tom))
        {
            if(!isInvincible)
            {
                if (withCheese)
                {
                    qDebug() << position.x() << "  "<<position.y();
                    if (position.x() == 85 && position.y() == 85)
                    {
                            c1 = new cheese(1, 1);
                            scene()->addItem(c1);
                    }

                    else if (position.x() == 85 && position.y() == 680)
                    {
                            c1 = new cheese(1, 18);
                            scene()->addItem(c1);
                    }

                    else if (position.x() == 680 && position.y() == 85)
                    {
                            c1 = new cheese(18, 1);
                            scene()->addItem(c1);
                    }
                    else if (position.x() == 680 && position.y() == 680)
                    {
                            qDebug() << position.x() << "  "<<position.y();
                            c1 = new cheese(18, 18);
                            scene()->addItem(c1);
                    }

                }


                   JerryToNormal(*this);
                   withCheese = false;


                if (no_lives >= 0)
                  no_lives--;
               WinLose(no_lives, no_cheese);
                //Blink***
               //timer->start(30);
               //timer->start(60);
               //connect(timer, SIGNAL(timeout()), this, SLOT(Blink()));
               //timer->stop();
               LifeBar();
            }
        }
    }
}


void Jerry::swapJerry(Jerry& J)
{
     QPixmap img("JerrySmallSquaredwithCheese.png");
     img = img.scaledToWidth(35);
     img = img.scaledToHeight(35);
     J.setPixmap(img);
}


void Jerry::JerryToNormal(Jerry& J)
{
     QPixmap img("JerrySmallSquared.png");
     img = img.scaledToWidth(35);
     img = img.scaledToHeight(35);
     J.setPixmap(img);
     cheese c(18,18);

}


void Jerry::WinLose(int lifeNum, int cheeseNum)
{
    win->setPos(500,10);
    if (lifeNum == 0)
    {
        isOver = true;
        win->setText("Game Over");
    }
    else if (cheeseNum == 4)
    {
        isOver = true;
        win->setText("Winner, Winner Chicken Dinner");
    }
}
void Jerry::LifeBar()
{
    //Display number of lives and the number of cheese collected
    //Can be represented by pics
    QString word;
    if (mode == Normal)
        word = "Normal";
    else word = "Invincible";
    QString part1= "Lives left: " + QString::number(no_lives) + "   Cheese collected: " + QString::number(no_cheese) + "  Current Mode: "+ word;
    life->setText(part1);

}
void Jerry::BacktoNormal()
{
    timer->stop();
    //Opacity increases***
    mode = Normal;
    isInvincible = false;
    LifeBar();
}


#include <QDebug>
void Jerry::Blink()
{
    qDebug() << "here";
    if (this->isVisible())
        this->setVisible(false);
    else
        this->setVisible(true);
}




/*void Jerry::PixMap(QImage)
{
    QPainter paint(&pic);
    Opacity(pic, paint, 0.5)
}
*/


/*void Jerry::Opacity(QPixmap pic, QPainter paint, int value)
{
    paint.setOpacity(value);
    paint.drawPixmap(0, 0, pic);
    paint.end();
}
*/
