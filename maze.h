#ifndef MAZE_H
#define MAZE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Maze; }
QT_END_NAMESPACE

class Maze : public QMainWindow
{
    Q_OBJECT

public:
    Maze(QWidget *parent = nullptr);
    ~Maze();

private:
    Ui::Maze *ui;
};
#endif // MAZE_H
