#include "seg.h"
#include <iostream>

Seg::Seg(const char *Path)
{
    PathToFile = Path;
}



void Seg::segy_file_open(){
    fp = segy_open(PathToFile, "r");
    if (!fp) fprintf(stderr, "segyio-cath: %s: No such file or directory\n", PathToFile);

    //проверка на НЕПОНЯЛ
    int err = segy_binheader(fp, binheader);
    if (err) std::cout<<"Unable to read binheader";


    //НЕПОНЯЛ
    samnr = segy_samples(binheader);
    //возврощает формат,хотя в данном случае 1.
    format = segy_format(binheader);

    switch (format) {
    case SEGY_IBM_FLOAT_4_BYTE:
    case SEGY_SIGNED_INTEGER_4_BYTE:
    case SEGY_SIGNED_SHORT_2_BYTE:
    case SEGY_FIXED_POINT_WITH_GAIN_4_BYTE:
    case SEGY_IEEE_FLOAT_4_BYTE:
    case SEGY_SIGNED_CHAR_1_BYTE:
        break;

    case 0:
        format = SEGY_IBM_FLOAT_4_BYTE;
        break;

    case SEGY_NOT_IN_USE_1:
    case SEGY_NOT_IN_USE_2:
    default:
        std::cout<< "sample format field is garbage. "
            "falling back to 4-byte float. "
            "override with --format";
        format = SEGY_IBM_FLOAT_4_BYTE;
    }

    //segy_trsize вычисляет размер трассировки в байтах, определяемый форматом трассировки.
    trace_bsize = segy_trsize(format, samnr);

    // байтовое смещение первого заголовка трассировки.
    trace0 = segy_trace0(binheader);

    //количество трасс
    err = segy_traces(fp, &numtrh, trace0, trace_bsize);
    if (err)
       std::cout<< "Unable to determine number of traces in file";

}


int Seg::segy_get_size(){
    return numtrh;
}



