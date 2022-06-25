
#include "worleybase.h"

WorleyBase::WorleyBase(int width, int height, bool normalized, QObject *parent):
    UpdatableFrame(width, height, parent),
    col_converter(LinearConverter::converter())
{
    m_normalized_pos = normalized;
}

void WorleyBase::updateFrame()
{
    Q_ASSERT_X(m_node_count > 1, "WorleyBase::update()", "incomplete node definition");
#ifdef TIME_MEASURE
    QElapsedTimer timer;
    timer.start();
#endif

    LinearConverter::R_rate = R_rate;
    LinearConverter::R_offset = R_offset;
    LinearConverter::G_rate = G_rate;
    LinearConverter::G_offset = G_offset;
    LinearConverter::B_rate = B_rate;
    LinearConverter::B_offset = B_offset;


#pragma omp parallel
{
    QVector<float> result_dists;
    result_dists.reserve(m_node_count); // optimum memory size
#ifdef WORLEY_LEFTRIGHT_IMP
    int base_index = 0, // node index of center
            default_index = -1, // dist index of insertion
            act_offset = 0; // node index of look around
#endif
    int act_index = -1, // current dist index for insertion
            col_index = 0; // current color to modify
    float act_dist = 0, // current inserted dist
            x_read = 0, // current vector x from point to node
            y_read = 0, // current vector y from point to node
            col_x, col_y, col_z;  // triplet from dist list
#ifdef WORLEY_LEFTRIGHT_IMP
    bool left_finished = false, right_finished = false; // left/right look around termination
#endif
    #pragma omp for
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            // data preparation
            result_dists.clear();

#ifdef WORLEY_LEFTRIGHT_IMP
            // first distance insertion
            x_read = m_normalized_pos ? ((float) x) / m_width : x;
            y_read = m_normalized_pos ? ((float) y) / m_height: y;
            x_read -= Xl[base_index];
            y_read -= Yl[base_index];
            act_dist = x_read*x_read + y_read*y_read;
            result_dists.append(act_dist);
            // preparation for first loop
            default_index = 1;
            act_offset = 1;
            left_finished = base_index - act_offset < 0;
            right_finished = base_index + act_offset >= m_node_count;
            // loop calculation
            while (!left_finished || !right_finished)
            {
                if (!left_finished)
                {
                    x_read = m_normalized_pos ? ((float) x) / m_width : x;
                    y_read = m_normalized_pos ? ((float) y) / m_height: y;
                    x_read -= Xl[base_index - act_offset];
                    y_read -= Yl[base_index - act_offset];
                    act_dist = x_read*x_read + y_read*y_read;
                    act_index = result_dists.length();
                    while (act_index > 0 && act_dist < result_dists[act_index - 1])
                    {
                        --act_index;
                    }
                    result_dists.insert(act_index, act_dist);
                    ++default_index;
                }
                if (!right_finished)
                {
                    x_read = m_normalized_pos ? ((float) x) / m_width : x;
                    y_read = m_normalized_pos ? ((float) y) / m_height: y;
                    x_read -= Xl[base_index + act_offset];
                    y_read -= Yl[base_index + act_offset];
                    act_dist = x_read*x_read + y_read*y_read;
                    act_index = result_dists.length();
                    while (act_index > 0 && act_dist < result_dists[act_index - 1])
                    {
                        --act_index;
                    }
                    result_dists.insert(act_index, act_dist);
                    ++default_index;
                }
                ++act_offset;
                left_finished |= base_index - act_offset < 0;
                right_finished |= base_index + act_offset >= m_node_count;
            }
#else
            for (int m = 0; m < m_node_count; ++m)
            {
                x_read = Xl[m] - x;
                y_read = Yl[m] - y;
                act_dist = x_read*x_read + y_read*y_read;
                act_index = result_dists.length();
                while (act_index > 0 && act_dist < result_dists[act_index - 1])
                {
                    --act_index;
                }
                result_dists.insert(act_index, act_dist);
            }
#endif
            dist_converter(col_x, col_y, col_z, result_dists);
            col_index = (y*m_width + x)*4;
            data_act[col_index + 3] = 0xFF;
            col_converter.triple_to_col(
                        data_act[col_index + 2], data_act[col_index + 1], data_act[col_index + 0],
                        col_x, col_y, col_z
                        );
        }
#ifdef WORLEY_LEFTRIGHT_IMP
        while (base_index + 1 < m_node_count && y > Yl[base_index])
        {
            ++base_index;
        }
#endif
    }

    // POINTS UPDATE
    float m_x = m_width / 2.f,
        m_y = m_height / 2.f,
        rX = std::cos(3.14f/200.f),
        rY = std::sin(3.14f/200.f);
    for (int m = 0; m < m_node_count; m++)
    {
        Xl[m] -= m_x;
        Yl[m] -= m_y;
        float n_x = Xl[m],
            n_y = Yl[m];
        Xl[m] = n_x * rX - n_y * rY;
        Yl[m] = n_x * rY + n_y * rX;
        Xl[m] += m_x;
        Yl[m] += m_y;
    }
}
#ifdef TIME_MEASURE
    qDebug() << "TIME WORLEY : " << timer.elapsed();
#endif
    data_act.swap(data_prev);

    m_t_update += 1;
    m_buffer = QImage(data_prev.data(), m_width, m_height, QImage::Format_RGB32);
    m_image->convertFromImage(m_buffer);
    emit updatedPixmap(m_image);
}

void WorleyBase::addNormalizedPoint(float x, float y)
{
    if (!m_normalized_pos)
    {
        x *= m_width;
        y *= m_height;
    }
    int index = 0;
    while (index < m_node_count && (y > Yl[index] || (y == Yl[index] && x > Xl[index])))
    {
        index++;
    }
    m_node_count++;
    Xl.insert(index, x);
    Yl.insert(index, y);
}

void WorleyBase::addPoint(float x, float y)
{
    if (m_normalized_pos)
    {
        x /= m_width;
        y /= m_height;
    }
    int index = 0;
    while (index < m_node_count && (y > Yl[index] || (y == Yl[index] && x > Xl[index])))
    {
        index++;
    }
    m_node_count++;
    Xl.insert(index, x);
    Yl.insert(index, y);
}

void worleyToMangoust(float &x, float &y, float &z, QVector<float>& dist)
{
    x = 0; y = 0; z = 0;
    float W = 1.f, Ws = 0.f, tmp_x, tmp_d;
    for (int m = 0; m < dist.length(); m++)
    {
        tmp_d = std::sqrt(dist[m]);
        tmp_x = std::cos(tmp_d / 10);
        x += tmp_x* W;
        y += std::sin(tmp_d / 10) * W;
        z += std::sin(tmp_x * 3.1459) * W;

        Ws += W;
        W /= 2.f;
    }
    x /= Ws; y /= Ws; z /= Ws;

    LinearConverter::R_rate = 55.f/255.f; LinearConverter::R_offset = 0.0f;
    LinearConverter::G_rate = 1.f; LinearConverter::G_offset = 0.f;
    LinearConverter::B_rate = 100.f/255.f; LinearConverter::B_offset = 0.5f;
    //qDebug() << x << y << z;
}

void worleyToGrayscale(float &x, float &y, float &z, QVector<float> &dist)
{
    x = dist[0]/dist[1];
    y = x;
    z = x;
}

void worleyToMinGrayscale(float &x, float &y, float &z, QVector<float> &dist)
{
    x = dist[0]/dist[1];
    for (int i = 1; i + 1 < dist.length(); i++)
    {
        y = dist[i]/dist[i+1];
        if (y < x)
            x = y;
    }
    y = x;
    z = x;
}
