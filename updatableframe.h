#ifndef UPDATABLEFRAME_H
#define UPDATABLEFRAME_H

#include <QObject>
#include <QVector>
#include <QImage>
#include <QPixmap>


class UpdatableFrame : public QObject
{
    Q_OBJECT
public:
    explicit UpdatableFrame(int width, int height, QObject *parent = nullptr);

    virtual void update() = 0;

signals:
    void updatedPixmap(QPixmap*);

protected:
    QVector<uchar> data_act;
    QVector<uchar> data_prev;

    QPixmap* m_image;
    QImage m_buffer;

    int m_width;
    int m_height;

    int m_t_update = 0;

};

#endif // UPDATABLEFRAME_H
