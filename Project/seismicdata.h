#ifndef SEISMICDATA_H
#define SEISMICDATA_H

#include "segyio/segy.h"
#include "QString"
#include "QMap"
#include "QMessageBox"
#include "seismogramm.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <memory>
#include <vector>

class SeismicData
{
private:
    const char *PathToFile;
    char header[SEGY_TEXT_HEADER_SIZE + 1] ;
    char binheader[SEGY_BINARY_HEADER_SIZE];
    segy_file* fp;
    int format;
    int samnr;
    int trace_bsize;
    long trace0;
    int block_size;
    int numtrh;
public:
    SeismicData(QString Path);
public:
    int segy_get_size();
    Seismogramm* getSeismogramm(int,int);
private:
        std::vector<int> in_and_x_line(int*,int*);
        void get__all_inline_and_xline(int*,int*);
        void read_trace(float* trbuf,int tr_num,int loc_tr_num,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*);
        void process_block(float* trbuf,int tr_count,int start,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*);

};

#endif // SEISMICDATA_H
