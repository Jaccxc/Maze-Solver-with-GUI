#ifndef MAZE_H
#define MAZE_H

#include <QMainWindow>
#include <QGraphicsDropShadowEffect>
#include <QCoreApplication>
#include <QMouseEvent>
#include <QSizeGrip>
#include <QButtonGroup>
#include <QLineEdit>
#include <QIntValidator>
#include <QPalette>
#include <QLabel>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QTimer>
#include <QThread>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <utility>
#include <queue>
#include <windows.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Maze; }
QT_END_NAMESPACE

class Maze : public QMainWindow
{
    Q_OBJECT

public:
    Maze(QWidget *parent = nullptr);
    ~Maze();

    QVector<QVector<QWidget*>> list_label_maze;

    void wait(qint64);
    void fade_start();

private slots:
    void on_pushButton_close_clicked();

    void on_pushButton_minimize_clicked();

    void on_pushButton_maximize_clicked();

private:
    constexpr static int rowNum[] = {-1, 0, 0, 1};
    constexpr static int colNum[] = {0, -1, 1, 0};
    constexpr static int maze_length = 48;
    constexpr static int maze_height = 27;
    Ui::Maze *ui;

    QGridLayout *grid_maze;
    QPoint *drag_pos;
    QPoint *global_pos;
    int global_size_status;
    int global_width;
    int global_height;
    int pixel_size = 30;

    void nullfunc();
    void fade_animation(QWidget*);
    bool is_in_bound(int r, int c);
    bool eventFilter(QObject *obj, QEvent *event) override;//in header
};
#endif // MAZE_H
