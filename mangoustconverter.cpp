#include "mangoustconverter.h"

float   MangoustConverter::R_rate = 0.25f,
        MangoustConverter::R_offset = 0.f,
        MangoustConverter::G_rate = 1.f,
        MangoustConverter::G_offset = 0.f,
        MangoustConverter::B_rate = 0.5f,
        MangoustConverter::B_offset = 0.5f;

MangoustConverter &MangoustConverter::converter()
{
    return m_converter;
}


void MangoustConverter::couple_to_colF(float &r, float &g, float &b, float x, float y) const
{
    triple_to_colF(r, g, b, x, y, 0);
}

void MangoustConverter::couple_to_col(uchar &r, uchar &g, uchar &b, float x, float y) const
{
    triple_to_col(r, g, b, x, y, 0);
}

void MangoustConverter::singleton_to_colF(float &r, float &g, float &b, float x) const
{
    triple_to_colF(r, g, b, x, 0, 0);
}

void MangoustConverter::singleton_to_col(uchar &r, uchar &g, uchar &b, float x) const
{
    triple_to_col(r, g, b, x, 0, 0);
}

void MangoustConverter::triple_to_colF(float &r, float &g, float &b, float x, float y, float z) const
{
    r = R_offset + x * R_rate;
    g = G_offset + y * G_rate;
    b = B_offset + z * B_rate;
}

void MangoustConverter::triple_to_col(uchar &r, uchar &g, uchar &b, float x, float y, float z) const
{
    r = (uchar) ((R_offset + x * R_rate) * 255);
    g = (uchar) ((G_offset + y * G_rate) * 255);
    b = (uchar) ((B_offset + z * B_rate) * 255);
}
