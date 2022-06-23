#include "smoothlife.h"

SmoothLife::SmoothLife(int width, int height, QObject *parent) :
    UpdatableFrame(width, height, parent)
{
}

void SmoothLife::update()
{
    m_t_update++;
}

