#include "mainwindow.h"
#include "smoothlife.h"
#include "coretest.h"

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int width = 600, height = 500;

    MainWindow w(width, height);
    CoreTest smooth(width, height, &w);

    qDebug() << "mama";
    QObject::connect(&smooth, &SmoothLife::updatedPixmap, &w, &MainWindow::setImage);
    qDebug() << "mia";
    w.show();
    return a.exec();
}
