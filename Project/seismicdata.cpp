#include "seismicdata.h"
#include <iostream>

SeismicData::SeismicData(QString Path)
{
    QByteArray ba = Path.toLocal8Bit();
    PathToFile = ba.data();
    block_size = 1000;
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

void SeismicData::process_block(){

}

int SeismicData::segy_get_size(){
    return numtrh;
}


QMap<QString,int> SeismicData::get_trace_by_id(int id){
    QMap<QString,int> seg_info;
    char traceh[SEGY_TRACE_HEADER_SIZE];
    //std::cout << "loc_tr_num" << loc_tr_num << std::endl;


    int err = segy_traceheader(fp, id, traceh, trace0, trace_bsize);
    if (err != 0) {
        fprintf(stderr, "Unable to read trace %d\n", id);
        std::exit(err);
    }

    int sample_count;
    err = segy_get_field(traceh, SEGY_TR_SAMPLE_COUNT, &sample_count);
    if (err != 0) {
        fprintf(stderr, "Invalid trace header field: %d\n", SEGY_TR_SAMPLE_COUNT);
        std::exit(err);
    }

    if (sample_count != samnr) {
        fprintf(stderr, "Only fixed size traces are supperted\n");
        std::exit(1);
    }



    int bufer;
    err = segy_get_field(traceh, SEGY_TR_SOURCE_X, &bufer);
    if (err != 0) {
        fprintf(stderr, "Invalid trace header field: %d\n", SEGY_TR_SOURCE_X);
        std::exit(err);
    }
    seg_info.insert("source_x",bufer);


    err = segy_get_field(traceh, SEGY_TR_SOURCE_Y, &bufer);
    if (err != 0) {
        fprintf(stderr, "Invalid trace header field: %d\n", SEGY_TR_SOURCE_X);
        std::exit(err);
    }
    seg_info.insert("source_y",bufer);


    err = segy_get_field(traceh, SEGY_TR_CROSSLINE, &bufer);

    if (err != 0) {
        fprintf(stderr, "Invalid trace header field: %d\n", SEGY_TR_SOURCE_X);
        std::exit(err);
    }

    seg_info.insert("xline",bufer);

    err = segy_get_field(traceh, SEGY_TR_INLINE, &bufer);

    if (err != 0) {
        fprintf(stderr, "Invalid trace header field: %d\n", SEGY_TR_SOURCE_Y);
        std::exit(err);
    }

    seg_info.insert("yline",bufer);

    err = segy_get_field(traceh, SEGY_TR_CDP_X, &bufer);

    if (err != 0) {
        fprintf(stderr, "Invalid trace header field: %d\n", SEGY_TR_CDP_X);
        std::exit(err);
    }

    seg_info.insert("CDP_x",bufer);

    err = segy_get_field(traceh, SEGY_TR_CDP_Y, &bufer);

    if (err != 0) {
        fprintf(stderr, "Invalid trace header field: %d\n", SEGY_TR_CDP_Y);
        std::exit(err);
    }

    seg_info.insert("CDP_y",bufer);

    err = segy_get_field(traceh, SEGY_TR_GROUP_X, &bufer);

    if (err != 0) {
        fprintf(stderr, "Invalid trace header field: %d\n", SEGY_TR_GROUP_X);
        std::exit(err);
    }

    seg_info.insert("group_x",bufer);

    err = segy_get_field(traceh, SEGY_TR_GROUP_Y, &bufer);

    if (err != 0) {
        fprintf(stderr, "Invalid trace header field: %d\n", SEGY_TR_GROUP_Y);
        std::exit(err);
    }

    seg_info.insert("group_y",bufer);

    err = segy_get_field(traceh, SEGY_TR_SHOT_POINT, &bufer);

    if (err != 0) {
        fprintf(stderr, "Invalid trace header field: %d\n", SEGY_TR_SHOT_POINT);
        std::exit(err);
    }

    seg_info.insert("shot_point",bufer);

    err = segy_get_field(traceh, SEGY_TR_OFFSET, &bufer);

    if (err != 0) {
        fprintf(stderr, "Invalid trace header field: %d\n", SEGY_TR_OFFSET);
        std::exit(err);
    }

    seg_info.insert("offset",bufer);

    err = segy_get_field(traceh, SEGY_TR_SEQ_FILE, &bufer);

    if (err != 0) {
        fprintf(stderr, "Invalid trace header field: %d\n", SEGY_TR_SEQ_FILE);
        std::exit(err);
    }

    seg_info.insert("trace_id",bufer);



    return seg_info;
}


//QMultiMap<QString,int> segy_get_otg(Segio_trace_info seg_inf){
//    QMultiMap<QString,int> map;

//    qDebug()<< seg_inf.x_line[0];

//}
