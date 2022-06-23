#include "updatableframe.h"

UpdatableFrame::UpdatableFrame(int width, int height, QObject *parent):
    QObject(parent),
    m_width(width),
    m_height(height)
{
    m_image = new QPixmap(m_width, m_height);

    data_act.resize(m_width * m_height * 4);
    data_prev.resize(m_width * m_height * 4);
}
