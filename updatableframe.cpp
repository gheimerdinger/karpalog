#include "updatableframe.h"

UpdatableFrame::UpdatableFrame(int width, int height, QObject *parent):
    QThread(parent),
    m_width(width),
    m_height(height),
    m_update_sem(0)
{
    m_image = new QPixmap(m_width, m_height);

    data_act.resize(m_width * m_height * 4);
    data_prev.resize(m_width * m_height * 4);

    m_update_timer.setInterval(60);
    connect(&m_update_timer, &QTimer::timeout, this, &UpdatableFrame::force_update);
}

void UpdatableFrame::switchUpdateMode()
{
    switch (m_update_mode)
    {
    case UpdateModeEvent:
        setUpdateMode(UpdateModeTimer);
        break;
    case UpdateModeTimer:
        setUpdateMode(UpdateModeEvent);
        break;
    }
}

void UpdatableFrame::askUpdate()
{
    m_mutex_update_mode.lock();
    if (m_update_mode == UpdateModeEvent)
    {
        qDebug() << "RELEASE";
        m_update_sem.release(1);
    }
    m_mutex_update_mode.unlock();
}

void UpdatableFrame::setUpdateMode(UpdateMode new_mode)
{
    m_mutex_update_mode.lock();
    switch (new_mode)
    {
    case UpdateModeEvent:
        m_update_timer.stop();
        break;
    case UpdateModeTimer:
        m_update_timer.start();
        break;
    }
    m_update_mode = new_mode;
    qDebug() << m_update_mode;
    m_mutex_update_mode.unlock();
}


void UpdatableFrame::run()
{
    force_update();
    forever {
        m_update_sem.acquire(1);
        updateFrame();
    }
}

void UpdatableFrame::force_update()
{
    m_update_sem.release(1);
}
