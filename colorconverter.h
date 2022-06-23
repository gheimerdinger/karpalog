#ifndef COLORCONVERTER_H
#define COLORCONVERTER_H

#include <QTypeInfo>

class ColorConverter
{
public:
    static ColorConverter& converter();
    virtual void triple_to_colF(float &r, float &g, float&b, float x, float y, float z) const;
    virtual void triple_to_col(uchar &r, uchar &g, uchar&b, float x, float y, float z) const;

    virtual void couple_to_colF(float &r, float &g, float&b, float x, float y) const;
    virtual void couple_to_col(uchar &r, uchar &g, uchar&b, float x, float y) const;

    virtual void singleton_to_colF(float &r, float &g, float& b, float x) const;
    virtual void singleton_to_col(uchar& r, uchar& g, uchar& b, float x) const;
private:
    static ColorConverter m_color_converter;
};

#endif // COLORCONVERTER_H
