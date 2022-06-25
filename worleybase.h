#ifndef WORLEYBASE_H
#define WORLEYBASE_H

#include <cmath>
#include "updatableframe.h"
#include "core.h"
#include "colorconverter.h"
#include "linearconverter.h"

#define WORLEY_LEFTRIGHT_IMP

typedef void (*WorleyToTriple)(float&, float&, float&, QVector<float>&);
typedef void (*WorleyPointsUpdate)(QVector<float>&, QVector<float>&);

void worleyToGrayscale(float& x, float& y, float& z, QVector<float>& dist);
void worleyToMinGrayscale(float& x, float& y, float& z, QVector<float>& dist);
void worleyToMangoust(float& x, float& y, float& z, QVector<float>& dist);

class WorleyBase: public UpdatableFrame
{
    Q_OBJECT
public:
    WorleyBase(int width, int height, bool normalized = false, QObject*parent = nullptr);
    ColorConverter& col_converter;
    WorleyToTriple dist_converter = &worleyToMangoust;
    virtual void updateFrame() override;

    float R_rate = 1.f, R_offset = 0.f,
          G_rate = 1.f, G_offset = 0.f,
          B_rate = 1.f, B_offset = 0.f;

    void addNormalizedPoint(float x, float y);
    void addPoint(float x, float y);

private:
    void sort_point();

    bool m_normalized_pos = false;
    int m_node_count = 0;
    QVector<float> Xl, Yl;
};

#endif // WORLEYBASE_H
