#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QEvent>

#include "updatableframe.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int width, int height, QWidget *parent = nullptr);
    ~MainWindow();

    // QObject interface
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void clickEvent();
    void askUpdateModeChange();


public slots:
    void setImage(QPixmap*)    ;

private:
    QGraphicsView* m_canvas;
    QGraphicsScene* m_view;
    QGraphicsPixmapItem* m_image_view;


};
#endif // MAINWINDOW_H
