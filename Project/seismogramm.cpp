#include "seismogramm.h"

Seismogramm::Seismogramm(float* buf,int* tr_source_x,
int* tr_source_y,
int* tr_CDP_x,
int* tr_CDP_y,
int* tr_yline,
int* tr_xline,
int* tr_group_x,
int* tr_group_y,
int* tr_shot_point,
int* tr_offset,
int* tr_trace_id,
int* tr_in_line,
int* tr_x_line)
{
    source_x = tr_source_x;
    source_y = tr_source_y;
    CDP_x = tr_CDP_x;
    CDP_y = tr_CDP_y;
    yline = tr_yline;
    xline = tr_xline;
    group_x = tr_group_x;
    group_y = tr_group_y;
    shot_point = tr_shot_point;
    offset = tr_offset;
    trace_id = tr_trace_id;
    in_line = tr_in_line;
    x_line = tr_x_line;
    trbuf = buf;
}

QtCharts::QLineSeries *Seismogramm::get_series(){
    QtCharts::QLineSeries *series = new QtCharts::QLineSeries();
    for (int i = 0; i < 500; i++) {
        QPointF p((qreal) i, qSin(M_PI / 50 * i) * 100);
        p.ry() += QRandomGenerator::global()->bounded(20);
        *series << p;
    }
    return series;
}



