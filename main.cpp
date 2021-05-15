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


    Tom t(18,10,boardData);
    scene.addItem(&t);
    Jerry j(9, 9, boardData,t);
    scene.addItem(&j);
    scene.addItem(j.life);
    scene.addItem(j.win);
    j.setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    j.setFocus();

    t.setFlag(QGraphicsPixmapItem::ItemIsFocusable);





    QTimer timer;
    QTimer tim;
    tim.start(300);
    timer.start(400);
    tim.connect(&tim, SIGNAL(timeout()), &j, SLOT(move()));
    timer.connect(&timer, SIGNAL(timeout()), &t, SLOT(UpdateMotion()));




    cheese c1(1, 1),c2(18,18),c3(1,18),c4(18,1);
    scene.addItem(&c1);
    scene.addItem(&c2);
    scene.addItem(&c3);
    scene.addItem(&c4);

    pellet p1(10,16),p2(15,10);
    scene.addItem(&p1);
    scene.addItem(&p2);

    view.setScene(&scene);
    view.show();
    return a.exec();
}
