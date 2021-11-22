#include "maze.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Maze w;
    w.show();
    w.wait(2000);
    w.fade_start();
    //w.list_label_maze[10][10]->setStyleSheet(QString("QLabel {\nbackground-color: rgb(4, 150, 230);\nborder-radius:0px\n}"));

    return a.exec();
}
