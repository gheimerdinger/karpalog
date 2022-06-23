#ifndef CORETEST_H
#define CORETEST_H

#include "updatableframe.h"
#include "core.h"
#include "colorconverter.h"
#include "mangoustconverter.h"


typedef void (*WorleyToTriple)(float&, float&, float&, QVector<float>);

void worleyToMangoust(float& x, float& y, float& z, QVector<float> dist);

class WorleyBase: public UpdatableFrame
{
    Q_OBJECT
public:
    WorleyBase(int width, int height, bool normalized = false, QObject*parent = nullptr);
    ColorConverter& col_converter;
    WorleyToTriple dist_converter = &worleyToMangoust;
    virtual void update() override;

    void addNormalizedPoint(float x, float y);
    void addPoint(float x, float y);

private:
    bool m_normalized_pos = false;
    int m_node_count = 0;
    QVector<float> Xl, Yl;
};

#endif // CORETEST_H
