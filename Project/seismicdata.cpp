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


int SeismicData::segy_get_size(){
    return numtrh;
}




void SeismicData::read_trace(float* trbuf,int tr_num,int loc_tr_num,
                             int* source_x,
                             int* source_y,
                             int* CDP_x,
                             int* CDP_y,
                             int* yline,
                             int* xline,
                             int* group_x,
                             int* group_y,
                             int* shot_point,
                             int* offset,
                             int* trace_id,
                             int* in_line,
                             int* x_line){

    char traceh[SEGY_TRACE_HEADER_SIZE];
    //std::cout << "loc_tr_num" << loc_tr_num << std::endl;


    int err = segy_traceheader(fp, tr_num, traceh, trace0, trace_bsize);
    if (err != 0) {
        QMessageBox msgBox;
        msgBox.setText("Unable to read trace %d\n" + tr_num);
        msgBox.exec();
        std::exit(err);
    }

    int sample_count;
    err = segy_get_field(traceh, SEGY_TR_SAMPLE_COUNT, &sample_count);

    if (err != 0) {
        QMessageBox msgBox;
        msgBox.setText("Invalid trace header field: %d\n" + SEGY_TR_SAMPLE_COUNT);
        msgBox.exec();
        std::exit(err);
    }

    if (sample_count != samnr) {
        QMessageBox msgBox;
        msgBox.setText("Only fixed size traces are supperted\n");
        msgBox.exec();
        std::exit(1);
    }

    err = segy_get_field(traceh, SEGY_TR_SOURCE_X, &source_x[loc_tr_num]);

    if (err != 0) {
        QMessageBox msgBox;
        msgBox.setText("Invalid trace header field: %d\n" + SEGY_TR_SOURCE_X);
        msgBox.exec();
        std::exit(err);
    }

    err = segy_get_field(traceh, SEGY_TR_SOURCE_Y, &source_y[loc_tr_num]);

    if (err != 0) {
        QMessageBox msgBox;
        msgBox.setText("Invalid trace header field: %d\n"+SEGY_TR_SOURCE_Y);
        msgBox.exec();
        std::exit(err);
    }


    err = segy_get_field(traceh, SEGY_TR_CROSSLINE, &xline[loc_tr_num]);

    if (err != 0) {
        QMessageBox msgBox;
        msgBox.setText("Invalid trace header field: %d\n"+SEGY_TR_CROSSLINE);
        msgBox.exec();
        std::exit(err);
    }

    err = segy_get_field(traceh, SEGY_TR_INLINE, &yline[loc_tr_num]);

    if (err != 0) {
        QMessageBox msgBox;
        msgBox.setText("Invalid trace header field: %d\n"+SEGY_TR_INLINE);
        msgBox.exec();
        std::exit(err);
    }


    err = segy_get_field(traceh, SEGY_TR_CDP_X, &CDP_x[loc_tr_num]);

    if (err != 0) {
        QMessageBox msgBox;
        msgBox.setText("Invalid trace header field: %d\n"+SEGY_TR_CDP_X);
        msgBox.exec();
        std::exit(err);
    }

    err = segy_get_field(traceh, SEGY_TR_CDP_Y, &CDP_y[loc_tr_num]);

    if (err != 0) {
        QMessageBox msgBox;
        msgBox.setText("Invalid trace header field: %d\n"+SEGY_TR_CDP_Y);
        msgBox.exec();
        std::exit(err);
    }


    err = segy_get_field(traceh, SEGY_TR_GROUP_X, &group_x[loc_tr_num]);

    if (err != 0) {
        QMessageBox msgBox;
        msgBox.setText("Invalid trace header field: %d\n"+SEGY_TR_GROUP_X);
        msgBox.exec();
        std::exit(err);
    }

    err = segy_get_field(traceh, SEGY_TR_GROUP_Y, &group_y[loc_tr_num]);

    if (err != 0) {
        QMessageBox msgBox;
        msgBox.setText("Invalid trace header field: %d\n"+SEGY_TR_GROUP_Y);
        msgBox.exec();
        std::exit(err);
    }

    err = segy_get_field(traceh, SEGY_TR_SHOT_POINT, &shot_point[loc_tr_num]);

    if (err != 0) {
        QMessageBox msgBox;
        msgBox.setText("Invalid trace header field: %d\n"+SEGY_TR_SHOT_POINT);
        msgBox.exec();
        std::exit(err);
    }

    err = segy_get_field(traceh, SEGY_TR_OFFSET, &offset[loc_tr_num]);

    if (err != 0) {
        QMessageBox msgBox;
        msgBox.setText("Invalid trace header field: %d\n"+SEGY_TR_OFFSET);
        msgBox.exec();
        std::exit(err);
    }

    err = segy_get_field(traceh, SEGY_TR_SEQ_FILE, &trace_id[loc_tr_num]);

    if (err != 0) {
        QMessageBox msgBox;
        msgBox.setText("Invalid trace header field: %d\n"+SEGY_TR_SEQ_FILE);
        msgBox.exec();
        std::exit(err);
    }

    err = segy_readtrace(fp, tr_num, trbuf, trace0, trace_bsize);
    segy_to_native(format, samnr, trbuf);
    if (err!= 0){
        QMessageBox msgBox;
        msgBox.setText("trace read error: %d\n"+err);
        msgBox.exec();
    }
}


void SeismicData::process_block(float* trbuf,int tr_count,int start,
                                int* source_x,
                                int* source_y,
                                int* CDP_x,
                                int* CDP_y,
                                int* yline,
                                int* xline,
                                int* group_x,
                                int* group_y,
                                int* shot_point,
                                int* offset,
                                int* trace_id,
                                int* in_line,
                                int* x_line)
{
    int tr_num;

    for (int loc_tr_num = 0; loc_tr_num < tr_count; loc_tr_num++) {
        tr_num = start+loc_tr_num;
        read_trace(trbuf + loc_tr_num * samnr,tr_num,loc_tr_num,source_x,source_y,CDP_x,CDP_y,yline,xline,group_x,group_y,shot_point,offset,trace_id,in_line,x_line);
    }
}



void SeismicData::get__all_inline_and_xline(int* in_line, int* x_line){
    char traceh[SEGY_TRACE_HEADER_SIZE];
    for (int tr_num = 0; tr_num < numtrh; tr_num++) {
        int err = segy_traceheader(fp, tr_num, traceh, trace0, trace_bsize);
        err = segy_get_field(traceh, SEGY_TR_INLINE, &in_line[tr_num]);
        err = segy_get_field(traceh, SEGY_TR_CROSSLINE, &x_line[tr_num]);
    }
}


std::vector<int> SeismicData::in_and_x_line(int* x_line,int* in_line){
    std::vector<int> trace;
    trace.push_back(0);
    int prev_xline = x_line[0], prev_inline = in_line[0];
    for (int loc_tr_num = 0; loc_tr_num < numtrh; loc_tr_num++) {
        if (in_line[loc_tr_num]!= prev_inline || x_line[loc_tr_num]!= prev_xline) {
            prev_inline = in_line[loc_tr_num];
            prev_xline = x_line[loc_tr_num];
            trace.push_back(loc_tr_num);
            qDebug() << loc_tr_num << ' ' << in_line[loc_tr_num] << ' ' << x_line[loc_tr_num] << endl;
        }
    }

    return trace;
}


Seismogramm* SeismicData::getSeismogramm(int in_line,int x_line){

    Seismogramm *seis;
    char traceh[SEGY_TRACE_HEADER_SIZE];
    bool pos_str =true;
    int iln,xln;
    int start=0,stop=0;
    int* tr_x_line = new int[numtrh];
    int* tr_in_line = new int[numtrh];
    get__all_inline_and_xline(tr_in_line,tr_x_line);
    std::vector<int> traces_count = in_and_x_line(tr_x_line,tr_in_line);

    for(int i=0; i < traces_count.size()-1;i++)
    {
        if(tr_x_line[traces_count[i]]==x_line &&tr_in_line[traces_count[i]]==in_line){
            stop = traces_count[i+1];
            start = traces_count[i];
        }
    }

    auto * trbuf = new float[(stop - start) * trace_bsize];
    int* source_x= new int[stop-start]{1};
    int* source_y =new int[stop-start]{1};
    int* CDP_x =new int[stop-start]{1};
    int* CDP_y =new int[stop-start]{1};
    int* yline =new int[stop-start]{1};
    int* xline =new int[stop-start]{1};
    int* group_x =new int[stop-start]{1};
    int* group_y =new int[stop-start]{1};
    int* shot_point =new int[stop-start]{1};
    int* offset =new int[stop-start]{1};
    int* trace_id =new int[stop-start]{1};
    int* tr_2_in_line =new int[stop-start];
    int* tr_2_x_line =new int[stop-start];
    process_block(trbuf,stop - start,start,source_x,source_y,CDP_x,CDP_y,yline,xline,group_x,group_y,shot_point,offset,trace_id,tr_2_in_line,tr_2_x_line);
    seis = new Seismogramm(trbuf,source_x,source_y,CDP_x,CDP_y,yline,xline,group_x,group_y,shot_point,offset,trace_id,tr_2_in_line,tr_2_x_line);
    return seis;

}
