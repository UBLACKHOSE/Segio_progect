#ifndef SEGIO_TRACE_INFO_H
#define SEGIO_TRACE_INFO_H

#include <iostream>
#include "segyio/segy.h"
#include "chart.h"
#include "chartview.h"
#include "QMap"
#include "QtDebug"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QLineSeries>
#include <QtCore/QtMath>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QChart>
#include "QGroupBox"

class Seismogramm
{
private:
    float* trbuf;
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
    Seismogramm(float*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*);
    QtCharts::QLineSeries *get_series();
};

#endif // SEGIO_TRACE_INFO_H
