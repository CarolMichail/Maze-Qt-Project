#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include <cheese.h>
#include <pellet.h>
#include <jerry.h>
#include <tom.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsView view;
    QGraphicsScene scene;
    view.setWindowTitle("Tom And Jerry Game");
    view.setFixedSize(1000,1000);
    view.setBackgroundBrush(QBrush(Qt::gray));
    int boardData[20][20];
    QFile file("board.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString temp;
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
        {
            stream >> temp;
            boardData[i][j]=temp.toInt();
        }


    QPixmap q1("border.png");
    q1 = q1.scaledToWidth(35);
    q1 = q1.scaledToHeight(35);
    QPixmap q2("brick.png");
    q2 = q2.scaledToWidth(35);
    q2 = q2.scaledToHeight(35);
    QGraphicsPixmapItem boardImages[20][20];
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
        {
            //set image
            if ((boardData[i][j] == -10)||(boardData[i][j]== -20))
                boardImages[i][j].setPixmap(q1);
            else
                if(boardData[i][j] != -10 && boardData[i][j]!= -20)
                boardImages[i][j].setPixmap(q2);

            // Set Position
            boardImages[i][j].setPos(50 + (35 * j), 50 + (35 * i));
            // Add to the Scene
            scene.addItem(&boardImages[i][j]);
        }


    //Declaration of Tom and Jerry and adding them to the scene
    Tom t(18,10,boardData);
    Jerry j(9, 9, boardData,t);
    scene.addItem(&t);
    scene.addItem(&j);


    //Adding the text bars to the scene
    scene.addItem(j.life);
    scene.addItem(j.win);


    //Setting the flags for Tom and Jerry and stting the focus on Jerry
    t.setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    j.setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    j.setFocus();


    //Timers to call the moving functions of both Tom and Jerry
    QTimer Ttimer;
    QTimer Jtimer;
    Jtimer.start(100);
    Ttimer.start(300);
    Jtimer.connect(&Jtimer, SIGNAL(timeout()), &j, SLOT(move()));
    Ttimer.connect(&Ttimer, SIGNAL(timeout()), &t, SLOT(UpdateMotion()));


    //Declaration of the 4 pieces of cheese and adding them to the scene
    cheese c1(1, 1),c2(18,18),c3(1,18),c4(18,1);
    scene.addItem(&c1);
    scene.addItem(&c2);
    scene.addItem(&c3);
    scene.addItem(&c4);


    //Declaration of the 2 pellets and adding them to the scene
    pellet p1(10,16),p2(15,10);
    scene.addItem(&p1);
    scene.addItem(&p2);


    //Setting the scene on the graphics view
    view.setScene(&scene);
    view.show();

    return a.exec();
}
