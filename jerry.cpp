#include "jerry.h"
#include "cheese.h"
#include "pellet.h"

Jerry::Jerry(int initialRow, int initialColumn, int d[20][20], Tom & t)
{
    const QFont fon("Comic Sans MS",15);
    win = new QGraphicsSimpleTextItem;
    win->setFont(fon);
    life = new QGraphicsSimpleTextItem;
    life->setFont(fon);
    life->setPos(10,10);
    this->tom = &t;
    timer = new QTimer(this);

    //Copies the passed array to that of Jerry
    for (int i =0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            data[i][j] = d[i][j];

    // Sets the initial image of Jerry
    QPixmap image("JerrySmallSquared.png");
    image = image.scaledToWidth(35);
    image = image.scaledToHeight(35);
    setPixmap(image);

    // Sets the initial position of Jerry, which is in its house.
    setPos(50 + 35 * initialColumn, 50 + 35 * initialRow);
    row = initialRow;
    column = initialColumn;

    //Setting initial values of attributes
    no_lives = 3;
    no_cheese = 0;
    withCheese = false;
    isInvincible = false;
    isOver=false;
    mode = Normal;

    //Displays the initial text bar that describes the mode of the game, number of cheese collected
    // and number of lives left
    LifeBar();
}

//Function that takes the input from the keyboard and sets the direction accordingly
void Jerry::keyPressEvent(QKeyEvent* event)
{
    if (!isOver)
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
}


void Jerry::move()
{
    //Updates the position of Jerry according to the direction chosen by the user
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
    //Jerry's current node is updated in the Tom class to help in Tom's motion
    tom->SetJerryVertex(data[row][column]);

    //If Jerry is at home with a piece of cheese in hand then the cheese is placed in Jerry's house.
    if (inHome())
        if (withCheese)
        {
            //Incrementing the number of cheese collected and checking if the player has won or not yet
            WinLose(no_lives, ++no_cheese);
            //Jerry no longer carries the piece
            withCheese= false;
            //Jerry's image is changed back to one without cheese
            JerryToNormal();
            //Updates the text bar to change the text of the number of cheese collected.
            LifeBar();
            //The place of the piece of cheese added depends on how many pieces are collected
            if (no_cheese == 1)
            {
                 c_home = new cheese(9, 9);
                 scene()->addItem(c_home);
            }
            else if (no_cheese == 2)
            {
                c_home = new cheese(9, 11);
                scene()->addItem(c_home);
            }
            else if (no_cheese == 3)
            {
                c_home = new cheese(11, 9);
                scene()->addItem(c_home);
            }
            else if (no_cheese == 4)
            {
                c_home = new cheese(11, 11);
                scene()->addItem(c_home);
            }
        }

    //Handling Collisions:
    QList<QGraphicsItem*> items = collidingItems();
    for (int i = 0; i < items.size(); i++)
    {
        //If the item that collided with Jerry is a piece of cheese outside Jerry's home.
        //Disregarding cheese already collected, which is inside Jerry's house.
        if (typeid(*items[i]) == typeid(cheese) && !inHome())
        {
            //If collision happens without a piece already collected.
            //If collision occurs while Jerry has a piece in hand, nothing will happen.
            if (!withCheese)
            {
                //Remove the piece from the scene
                scene()->removeItem(items[i]);
                //Save and store its position in case it needs to be returned back after colliding with Tom.
                C_Position = (*items[i]).pos();
                //Call the function that changes the image of Jerry (Jerry with Cheese in hand).
                JerryToCheese();
                //Switch the bool to true in case Jerry collides with another piece of cheese.
                withCheese = true;
            }
        }

        //If a pellet is collected:
        else if (typeid(*items[i]) == typeid(pellet))
        {
            //Remove the pellet from the scene.
            scene()->removeItem(items[i]);
            //Change the mode of the Game to Invincible (enum).
            mode = Invincible;
            //Switch the bool to true in case Jerry collides with Tom.
            isInvincible = true;
            //Timer that allows invincibilty for 5 seconds only.
            //The timer calls the function slot BacktoNormal
            timer->start(5000); //5000 milliseconds
            connect(timer, SIGNAL(timeout()), this, SLOT(BacktoNormal()));
            //Updates the Life Bar (text bar at the top)
            LifeBar();
        }

        //If Jerry collides with Tom
        else if (typeid(*items[i]) == typeid(Tom))
        {
            //Tom is returned to its initial position
            tom->ReturnToOriginalPos();
            //In case the mode was normal (not invincible):
            if(!isInvincible)
            {
                //Jerry is returned to its initial position
                row = column = 9;
                setPos(50+ 35 * column, 50 + 35 * row);
                //If Jerry carries a piece of cheese:
                if (withCheese)
                {
                    //Return the piece of cheese to its original position using the position previously saved.
                    if (C_Position.x() == 85 && C_Position.y() == 85)
                    {
                            c_return = new cheese(1, 1);
                            scene()->addItem(c_return);
                    }

                    else if (C_Position.x() == 85 && C_Position.y() == 680)
                    {
                            c_return = new cheese(18, 1);
                            scene()->addItem(c_return);
                    }

                    else if (C_Position.x() == 680 && C_Position.y() == 85)
                    {
                            c_return = new cheese(1, 18);
                            scene()->addItem(c_return);
                    }
                    else if (C_Position.x() == 680 && C_Position.y() == 680)
                    {

                            c_return = new cheese(18, 18);
                            scene()->addItem(c_return);
                    }

                }
                //After returning the cheese, Jerry, and Tom to their original places, Jerry's image needs to be changed
                JerryToNormal();
                withCheese = false;

                //Update the Life Bar (text bar at the top) by decrementing the lives left by one.
                if (no_lives > 0)
                  no_lives--;
               LifeBar();
            }
        }
    }
    //Call WinLose to check on the lives left and the number of cheese collected
    //To chech whether the game has ended and whether the player lost or won.
    WinLose(no_lives, no_cheese);
}

//Function that changes the image of Jerry to one with cheese.
void Jerry::JerryToCheese()
{
     QPixmap img("JerrySmallSquaredwithCheese.png");
     img = img.scaledToWidth(35);
     img = img.scaledToHeight(35);
     setPixmap(img);
}

//Function that changes the image of Jerry from one with cheese to one without cheese.
void Jerry::JerryToNormal()
{
     QPixmap img("JerrySmallSquared.png");
     img = img.scaledToWidth(35);
     img = img.scaledToHeight(35);
     setPixmap(img);
     cheese c(18,18);
}

//Function that checks whether the player had lost or won.
void Jerry::WinLose(int lifeNum, int cheeseNum)
{
    //Setting the position of the text bar that displays "Win" or "Lose"
    win->setPos(250,-20);
    //If the player lost (no lives are left).
    if (lifeNum == 0)
    {
        //The game is over. The bool is used in presskeyEvent function
        // to forbid taking any input from the keyboard again.
        isOver = true;
        win->setText("Game Over");
        //Function that causes tom to stop moving again
        tom->stoppMoving();
        //Direction is set to an empty string
        direction = ' ';
    }
    //If the player won (collected all four pieces of cheese).
    else if (cheeseNum == 4)
    {
        //Similar assignments to attributes but different text is set.
        direction = ' ';
        tom->stoppMoving();
        isOver = true;
        win->setText("Winner, Winner Cheese Dinner");
    }
    //If the number of lives does not equal to zero or the collected cheese pieces is not 4, then nothing will happen
}

//This function updates the life bar (text bar) which displays the mode of the game, the number of lives left, and the
//number of cheese collected
void Jerry::LifeBar()
{
    //Display number of lives and the number of cheese collected
    QString word;
    if (mode == Normal)
        word = "Normal";
    else word = "Invincible";
    QString sentence= "Lives left: " + QString::number(no_lives) + "   Cheese collected: " + QString::number(no_cheese) + "  Current Mode: "+ word;
    life->setText(sentence);
}

//This function changes all related states of the game to normal after being invincible
void Jerry::BacktoNormal()
{
    //This is used to stop the timer count of 5 seconds.
    timer->stop();
    //Mode of the game is changed to normal after being invincible
    mode = Normal;
    //Jerry is no longer invincible
    isInvincible = false;
    //LifeBar is called to update the text of the mode of the game.
    LifeBar();
}
