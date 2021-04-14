#include "jerry.h"
#include "cheese.h"
#include "pellet.h"
#include "tom.h"

//image.fill(Qt::transparent); //fills with transparent

Jerry::Jerry(int initialRow, int initialColumn, int d[20][20])
{
    life = new QGraphicsSimpleTextItem;
    life->setPos(10,10);

    life->setText("ORIGInAL TEXT");

    //scene()->addItem(life);

    for (int i =0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            data[i][j] = d[i][j];
    // Set Image
    QPixmap image("Jerry.png");
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
    t = new QTimer(this);
    //PixMap(image);
    connect(this, SIGNAL(ChangeLife(int)),this, SLOT(ChangeLifeSlot(int)));
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
void Jerry::move()
{
    if (direction == 'u' && data[row - 1][column] != -10)
    {
        row--;
    }
    else if (direction == 'd' && data[row + 1][column] != -10)
    {
        row++;
    }
    else if (direction == 'r' && data[row][column + 1] != -10)
    {
        column++;
    }
    else if (direction == 'l' && data[row][column - 1] != -10)
    {
        column--;
    }
    setPos(50 + 35 * column, 50 + 35 * row);

    if (data[row][column] == -20)
        if (withCheese)
        {
            WinLose(no_lives, ++no_cheese);
            //Function to check on the number of cheese --> if 4 then win
            //The other swap function swapJerry(); from cheese to normal
        }


   QList<QGraphicsItem*> items = collidingItems();
    for (int i = 0; i < items.size(); i++)
    {
        if (typeid(items[i]) == typeid(cheese*))
        {
            if (!withCheese)
            {
            scene()->removeItem(items[i]);
            swapJerry(*this);
            withCheese=true;
            }
        }
        else if (typeid(items[i]) == typeid(pellet*))
        {
            scene()->removeItem(items[i]);
            mode = Invincible;
            isInvincible =true;
            //Opacity***

            //Timer --> 5 seconds to change back to normal --> New function is required to change to normal
            timer->start(5000); //5000 milliseconds
            connect(timer, SIGNAL(timeout()), this, SLOT(BacktoNormal()));
            //Update Life Bar
            LifeBar();
        }
        else if (typeid(*items[i]) == typeid(Tom))
        {
            if(!isInvincible)
            {
                WinLose(--no_lives, no_cheese);
                //Function to check on the lives lost --> if 0 then game over
                //Blink***
                emit ChangeLife(no_lives);
                qDebug() << "We hit tom";
                //timer->start(100);
                //connect(timer, SIGNAL(timeout()), this, SLOT(Blink()));

                //Update life bar
                LifeBar();
            }
        }
    }
}

void Jerry::swapJerry(Jerry& J)
{
     //J.setPixmap(QPixmap("JerrywihCheese.png"));
     QPixmap img("JerrywithCheese.png");
     img = img.scaledToWidth(35);
     img = img.scaledToHeight(35);
     J.setPixmap(img);
}

void Jerry::ChangeLifeSlot(int newLife)
{
    life->setText(QString::number(newLife));
    //life->setPlainText(QString::number(newLife));
}

void Jerry::WinLose(int lifeNum, int cheeseNum)
{
    if (lifeNum == 0)
    {
        //Display "Game Over"
    }
    else if (cheeseNum == 4)
    {
        //Display "Winner Winner, Chicken Dinner"
    }
}
void Jerry::LifeBar()
{
    //Display number of lives and the number of cheese collected
    //Can be represented by pics

    //TO UPDATE: 1. Delete old bar 2. Rewrite the new bar
}
void Jerry::BacktoNormal()
{
    timer->stop();
    //Opacity increases***
    mode = Normal;
    isInvincible = false;
    LifeBar();
}
void Jerry::Blink()
{
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
