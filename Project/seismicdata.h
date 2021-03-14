#ifndef SEISMICDATA_H
#define SEISMICDATA_H

#include "segyio/segy.h"
#include "QString"
#include "QMap"
#include "segio_trace_info.h"

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
    int numtrh;
    int block_size;

public:
    SeismicData(QString Path);
public:
    QMap<QString,int> get_trace_by_id(int id);
    int segy_get_size();
    //QMultiMap<QString,int> segy_get_otg(Segio_trace_info seg);
private:
    void process_block();
};

#endif // SEISMICDATA_H
