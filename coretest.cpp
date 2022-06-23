#include "coretest.h"

WorleyBase::WorleyBase(int width, int height, bool normalized, QObject *parent):
    UpdatableFrame(width, height, parent),
    col_converter(MangoustConverter::converter())
{
    m_normalized_pos = normalized;
}

void WorleyBase::update()
{

    m_t_update += 1;
}

void WorleyBase::addNormalizedPoint(float x, float y)
{
    m_node_count++;
    if (!m_normalized_pos)
    {
        x *= m_width;
        y *= m_height;
    }
    Xl.append(x);
    Yl.append(y);
}

void WorleyBase::addPoint(float x, float y)
{
    m_node_count++;
    if (m_normalized_pos)
    {

    }
}
