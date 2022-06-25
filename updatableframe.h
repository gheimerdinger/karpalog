#ifndef UPDATABLEFRAME_H
#define UPDATABLEFRAME_H

#include <QObject>
#include <QDebug>

#include <QMutex>
#include <QSemaphore>
#include <QTimer>

#include <QElapsedTimer>

#include <QThread>
#include <QVector>
#include <QImage>
#include <QPixmap>


#define TIME_MEASURE

enum UpdateMode{
    UpdateModeTimer,
    UpdateModeEvent
};

class UpdatableFrame : public QThread
{
    Q_OBJECT
public:
    explicit UpdatableFrame(int width, int height, QObject *parent = nullptr);

    virtual void updateFrame() = 0;

signals:
    void updatedPixmap(QPixmap*);

public slots:
    void switchUpdateMode();
    void setUpdateMode(UpdateMode);
    void askUpdate();

protected:
    UpdateMode m_update_mode = UpdateModeEvent;

    QVector<uchar> data_act;
    QVector<uchar> data_prev;

    QPixmap* m_image;
    QImage m_buffer;

    int m_width;
    int m_height;

    int m_t_update = 0;

    QMutex m_mutex_update_mode;
    QTimer m_update_timer;
    QSemaphore m_update_sem;

    // QThread interface
    void run() override;

private slots:
    void force_update();
};

#endif // UPDATABLEFRAME_H
