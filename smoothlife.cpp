#include "smoothlife.h"

SmoothLife::SmoothLife(int width, int height, QObject *parent) :
    UpdatableFrame(width, height, parent)
{
}

void SmoothLife::updateFrame()
{
    m_t_update++;
}

