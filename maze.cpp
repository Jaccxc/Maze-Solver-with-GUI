#include "maze.h"
#include "ui_maze.h"

Maze::Maze(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Maze)
{
    ui->setupUi(this);
}

Maze::~Maze()
{
    delete ui;
}

