#include "maze.h"
#include "ui_maze.h"

void Maze::wait( qint64 millisecondsWait ) {
    QEventLoop loop;
        QTimer t;
        t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
        t.start(millisecondsWait);
        loop.exec();

}

Maze::Maze(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Maze)
{
    ui->setupUi(this);

    qApp->installEventFilter(this);
    this->setWindowTitle("Sparse Matrix Calculator - NTPU");
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::WindowSystemMenuHint);
    this->setWindowFlag(Qt::WindowMinimizeButtonHint);
    this->setWindowFlag(Qt::WindowMaximizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    //Create drop shadow for main window
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setXOffset(0);
    shadow->setYOffset(0);
    shadow->setColor(QColor(0,0,0,60));
    ui->frame_main->setGraphicsEffect(shadow);

    drag_pos = new QPoint(0,0);
    global_pos = new QPoint(0,0);
    global_size_status = 0;
    ui->centralwidget->setContentsMargins(9,9,9,9);

    QSizeGrip *sizegrip = new QSizeGrip(this->ui->frame_size_grip);
    sizegrip->setStyleSheet("width: 20px; height: 20px; margin 0px; padding: 0px;");

    grid_maze = new QGridLayout();

    list_label_maze.resize(maze_height);
    for(int i=0; i<maze_height; i++)
    {
        for(int j=0; j<maze_length; j++){
            list_label_maze[i].append(new QWidget());
        }
    }
    for(int i=0; i<maze_height; i++)
    {
        for(int j=0; j<maze_length; j++){
            //list_label_maze[i][j]->setAlignment(Qt::AlignCenter);
            list_label_maze[i][j]->setMaximumWidth(pixel_size);
            list_label_maze[i][j]->setMaximumHeight(pixel_size);
            list_label_maze[i][j]->setMinimumWidth(pixel_size);
            list_label_maze[i][j]->setMinimumHeight(pixel_size);
            //list_label_maze[i][j]->setText(QString::number(i*maze_length+j));
            //line_edit_matrix_a[i]->setPlaceholderText(QString("0"));
            //line_edit_maze[i]->setFont(QFont("Open Sans SemiBold", 9));
            list_label_maze[i][j]->setStyleSheet(QString("background-color: rgb(14, 23, 32);\n	border-radius: 0px;\n"));
            QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect();
            eff->setOpacity(0);
            list_label_maze[i][j]->setGraphicsEffect(eff);



            grid_maze->addWidget(list_label_maze[i][j], i, j);
        }
    }

    ui->frame_maze->setMaximumHeight(pixel_size*maze_height);
    ui->frame_maze->setMinimumHeight(pixel_size*maze_height);
    ui->frame_maze->setMaximumWidth(pixel_size*maze_length);
    ui->frame_maze->setMinimumWidth(pixel_size*maze_length);

    ui->frame_maze->setLayout(grid_maze);
    ui->frame_maze->layout()->setSpacing(0);


}

Maze::~Maze()
{
    delete ui;
}


bool Maze::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *ev = static_cast<QMouseEvent *>(event);
        if (ev->buttons() & Qt::LeftButton)
        {
            this->drag_pos->setX(ev->globalPosition().x());
            this->drag_pos->setY(ev->globalPosition().y());
            ev->accept();
        }
    }
    if (obj == ui->frame_main && event->type() == QEvent::MouseMove)
    {
        QMouseEvent *ev = static_cast<QMouseEvent *>(event);
        if (ev->buttons() & Qt::LeftButton)
        {
            if(this->windowState() == Qt::MaximumSize){
                this->global_size_status = Qt::WindowNoState;
                ui->centralwidget->setContentsMargins(9,9,9,9);
                ui->frame_main->setStyleSheet(QString("QFrame{\nbackground-color: rgb(4, 15, 23);\nborder-radius:10px\n}"));
                this->setWindowState(Qt::WindowNoState);
            }
            QPoint move_to = (this->pos() + ev->globalPosition() - *this->drag_pos).toPoint();
            this->move(move_to);
            qDebug() << this->pos() << " " << drag_pos << "\n";
            this->drag_pos->setX(ev->globalPosition().x());
            this->drag_pos->setY(ev->globalPosition().y());
            this->global_pos->setX(ev->globalPosition().x());
            this->global_pos->setY(ev->globalPosition().y());
            qDebug() << "set :: " << ev->globalPosition() << "\n\n";
            ev->accept();
        }
    }

    return QObject::eventFilter(obj, event);
}


void Maze::on_pushButton_close_clicked()
{
    exit(EXIT_FAILURE);
}


void Maze::on_pushButton_minimize_clicked()
{
    ui->centralwidget->setContentsMargins(9,9,9,9);
    ui->frame_main->setStyleSheet(QString("QFrame{\nbackground-color: rgb(4, 15, 23);\nborder-radius:10px\n}"));
    this->setWindowState(Qt::WindowMinimized);
}


void Maze::on_pushButton_maximize_clicked()
{
    if(this->windowState() == Qt::WindowNoState){
        this->global_size_status = Qt::WindowMaximized;
        this->global_width = this->width();
        this->global_height = this->height();
        ui->centralwidget->setContentsMargins(0,0,0,0);
        ui->frame_main->setStyleSheet(QString("QFrame{\nbackground-color: rgb(4, 15, 23);\nborder-radius:0px\n}"));
        this->setWindowState(Qt::WindowMaximized);
    } else {
        this->global_size_status = Qt::WindowNoState;
        ui->centralwidget->setContentsMargins(9,9,9,9);
        ui->frame_main->setStyleSheet(QString("QFrame{\nbackground-color: rgb(4, 15, 23);\nborder-radius:10px\n}"));
        this->setWindowState(Qt::WindowNoState);
        //this->resize(this->global_width, this->global_height);
        //this->move(*global_pos);
    }

}

bool Maze::is_in_bound(int r, int c){
    if(r < 0 || c < 0) { return 0; }
    if(r >= maze_height || c >= maze_length) { return 0; }
    return 1;
}

void Maze::fade_animation(QWidget *w){
    //w->setStyleSheet(QString("\n	background-color: rgb(14, 23, 32);\n	border-radius: 0px;\n"));
    QGraphicsOpacityEffect *eff = static_cast<QGraphicsOpacityEffect*>(w->graphicsEffect());
    w->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(350);
    a->setStartValue(0);
    a->setEndValue(0.99);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
}


void Maze::fade_start(){
    int now_dist=0;
    bool visited[maze_height][maze_length];
    memset(visited, false, sizeof visited);
    int src_x = maze_height/2, src_y = maze_length/2-1;

    visited[src_x][src_y] = true;
    visited[src_x][src_y+1] = true;

    std::queue<std::pair<std::pair<int, int>, int>> q;
    std::vector<std::pair<int, int>> v;

    std::pair<std::pair<int, int>, int> s = {{src_x, src_y}, 0};
    std::pair<std::pair<int, int>, int> d = {{src_x, src_y+1}, 0};
    q.push(s);
    q.push(d);

    while (!q.empty())
    {
        std::pair<std::pair<int, int>, int> curr = q.front();
        std::pair<int, int> pt = curr.first;
        /*
        QEventLoop loop;
        QTimer::singleShot(1, &loop, &QEventLoop::quit);
        loop.exec();
        */
        wait(1);
        if(curr.second!=now_dist){
            now_dist = curr.second;
            while(!v.empty()){
                int lvalue = (v.end()-1)->first;
                int rvalue = (v.end()-1)->second;
                v.pop_back();
                fade_animation(list_label_maze[lvalue][rvalue]);
            }
        }
        v.push_back({pt.first, pt.second});
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int row = pt.first + rowNum[i];
            int col = pt.second + colNum[i];

            if (is_in_bound(row, col) && !visited[row][col])
            {
                visited[row][col] = true;
                std::pair<std::pair<int, int>, int> Adjcell = { { row, col }, curr.second+1 };
                q.push(Adjcell);
            }
        }
        fade_animation(list_label_maze[maze_height-1][maze_length-1]);
        fade_animation(list_label_maze[maze_height-1][0]);
        fade_animation(list_label_maze[0][maze_length-1]);
        fade_animation(list_label_maze[0][0]);
     }

    /*
    for(int i=0; i<maze_height; i++)
    {
        for(int j=0; j<maze_length; j++){
            fade_animation(list_label_maze[i][j]);
            //list_label_maze[i][j]->setStyleSheet(QString("QLabel {\n	background-color: rgba(14, 23, 32, 255);\n	border-radius: 0px;\n}"));
            wait(1);
        }
    }
    */
}

void Maze::nullfunc(){
    return;
}

