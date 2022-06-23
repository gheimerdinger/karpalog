#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int width, int height, QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void setImage(QPixmap*)    ;

private:
    QGraphicsView* m_canvas;
    QGraphicsScene* m_view;
    QGraphicsPixmapItem* m_image_view;


    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);
};
#endif // MAINWINDOW_H
