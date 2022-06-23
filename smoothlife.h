#ifndef SMOOTHLIFE_H
#define SMOOTHLIFE_H

#include <QDebug>

#include "updatableframe.h"

class SmoothLife : public UpdatableFrame
{
    Q_OBJECT
public:
    SmoothLife(int width, int height, QObject *parent);
    virtual void update() override;
};

#endif // SMOOTHLIFE_H
