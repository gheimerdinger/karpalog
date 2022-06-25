#include "mainwindow.h"
#include "smoothlife.h"
#include "worleybase.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int width = 720, height = 576;

    MainWindow w(width, height);
    WorleyBase worley(width, height, false, nullptr);
    // worley.dist_converter = worleyToGrayscale;

    QObject::connect(&worley, &SmoothLife::updatedPixmap, &w, &MainWindow::setImage);
    QObject::connect(&w, &MainWindow::clickEvent, &worley, &UpdatableFrame::askUpdate);
    QObject::connect(&w, &MainWindow::askUpdateModeChange, &worley, &UpdatableFrame::switchUpdateMode);
    for (int i = 0; i < 20; i++)
    {
        int x = std::rand()%width;
        int y = std::rand()%height;
        worley.addPoint(x, y);
    }
    worley.start(QThread::HighPriority);

    w.show();
    return a.exec();
}
