#include "colorconverter.h"
ColorConverter ColorConverter::m_color_converter;

ColorConverter &ColorConverter::converter()
{
    return m_color_converter;
}

void ColorConverter::triple_to_colF(float &r, float &g, float &b, float x, float y, float z) const
{
    r = x; g = y; b = z;
}

void ColorConverter::triple_to_col(uchar &r, uchar &g, uchar &b, float x, float y, float z) const
{
    r = (uchar) (x); g = (uchar) (y); b = (uchar) (z);
}

void ColorConverter::couple_to_colF(float &r, float &g, float &b, float x, float y) const
{
    r = x; g = y; b = 0;
}

void ColorConverter::couple_to_col(uchar &r, uchar &g, uchar &b, float x, float y) const
{
    r = (uchar) (x); g = (uchar) (y); b = 0;
}

void ColorConverter::singleton_to_colF(float &r, float &g, float &b, float x) const
{
    r = x; g = 0; b = 0;
}

void ColorConverter::singleton_to_col(uchar &r, uchar &g, uchar &b, float x) const
{
    r = (uchar) (x); g = 0; b = 0;
}
