#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(int width, int height, QWidget *parent)
    : QMainWindow(parent)
{
    m_canvas = new QGraphicsView();
    QWidget* main_frame = new QWidget();
    setCentralWidget(main_frame);

    main_frame->setLayout(new QHBoxLayout());

    main_frame->layout()->addWidget(m_canvas);
    m_canvas->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_canvas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_canvas->installEventFilter(this);
    m_canvas->setObjectName("canvas");

    QPushButton* update_mode_bt = new QPushButton("Update mode");
    connect(update_mode_bt, &QPushButton::pressed, this, &MainWindow::askUpdateModeChange);
    main_frame->layout()->addWidget(update_mode_bt);


    m_view = new QGraphicsScene(QRect(0, 0, width, height), m_canvas);

    QGraphicsScene& scene = *m_view;

    scene.setBackgroundBrush(Qt::blue);

    // a gradient background
    QRadialGradient gradient(0, 0, 10);
    gradient.setSpread(QGradient::RepeatSpread);
    scene.setBackgroundBrush(gradient);

    m_image_view = new QGraphicsPixmapItem();
    m_view->addItem(m_image_view);
    m_canvas->setScene(m_view);
    this->setGeometry(0, 0, width, height+50);
    //ui->centralwidget->setGeometry(0, 0, width, height);
    // m_canvas->setGeometry(0, 0, width, height);
    setFixedSize(width, height);

}

MainWindow::~MainWindow()
{
}

void MainWindow::setImage(QPixmap * image)
{
    m_image_view->setPixmap(*image);
}


bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::MouseButtonPress:
        qDebug() << watched->objectName() << event->type();
        emit clickEvent();
        break;
    case QEvent::MouseButtonRelease:
        emit clickEvent();
        return true;
    default:
        break;
    }
    return false;

}
