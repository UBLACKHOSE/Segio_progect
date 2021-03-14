#ifndef SEGIO_TRACE_INFO_H
#define SEGIO_TRACE_INFO_H

#include <iostream>
#include "segyio/segy.h"
#include "seismicdata.h"
#include "QMap"
#include "QtDebug"

class Segio_trace_info
{
private:
    float trbuf;
    int* source_x;
    int* source_y;
    int* CDP_x;
    int* CDP_y;
    int* yline;
    int* xline;
    int* group_x;
    int* group_y;
    int* shot_point;
    int* offset;
    int* trace_id;
    int* in_line;
    int* x_line;
public:
    Segio_trace_info();
};

#endif // SEGIO_TRACE_INFO_H
