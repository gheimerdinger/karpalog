#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(int width, int height, QWidget *parent)
    : QMainWindow(parent)
{
    m_canvas = new QGraphicsView();
    setCentralWidget(m_canvas);
    m_canvas->installEventFilter(this);
    m_canvas->setObjectName("canvas");

    m_canvas->setStyleSheet("background-color: red;");

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
    qDebug() << m_canvas->sizePolicy() << m_canvas->width() << m_canvas->height() << "vs" << this->width() << this->height();
    // this->setGeometry(0, 0, width, height);
    // ui->centralwidget->setGeometry(0, 0, width, height);
    // m_canvas->setGeometry(0, 0, width, height);
    setFixedSize(width, height);

}

MainWindow::~MainWindow()
{
}

void MainWindow::setImage(QPixmap * image)
{
    qDebug() << m_canvas->geometry();
    m_image_view->setPixmap(*image);
}



bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
        qDebug() << watched->objectName() <<  event->type();
        return false;
    default:
        break;
    }
    return true;

}
