#ifndef LINEARCONVERTER_H
#define LINEARCONVERTER_H

#include "colorconverter.h"

class LinearConverter : public ColorConverter
{
public:
    static LinearConverter &converter();
    static float R_rate, R_offset,
                 G_rate, G_offset,
                 B_rate, B_offset;

private:
    static LinearConverter m_converter;

    // ColorConverter interface
public:
    void couple_to_colF(float &r, float &g, float &b, float x, float y) const;
    void couple_to_col(uchar &r, uchar &g, uchar &b, float x, float y) const;
    void singleton_to_colF(float &r, float &g, float &b, float x) const;
    void singleton_to_col(uchar &r, uchar &g, uchar &b, float x) const;
    void triple_to_colF(float &r, float &g, float &b, float x, float y, float z) const;
    void triple_to_col(uchar &r, uchar &g, uchar &b, float x, float y, float z) const;
};

#endif // LINEARCONVERTER_H
