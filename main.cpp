#include "maze.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Maze w;
    int c=1;
    w.show();
    return a.exec();
}
