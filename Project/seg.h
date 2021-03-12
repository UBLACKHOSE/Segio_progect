#ifndef SEG_H
#define SEG_H

#include "segyio/segy.h"

class Seg
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
    int block_size = 1000;

public:
    Seg(const char *Path);
public:
    void segy_file_open();
    int segy_get_size();
};

#endif // SEG_H
