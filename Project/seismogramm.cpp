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
int* tr_x_line,
int tr_samnr,
float tr_fallback,int tr_size)
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
    samnr = tr_samnr;
    dt = tr_fallback;
    size = tr_size;
}

int Seismogramm::getSampleInterval(){
    return dt;
}

int Seismogramm::getTracesSize(){
    return size;
}


float* Seismogramm::getTraces(int j){
    return trbuf;
}

int Seismogramm::getBufferSize(){
    return samnr;
}


float Seismogramm::getMaxValue(){

    float max = -10000;
    for(int i =0;i<=size; i++){
        if(trbuf[i] > 0 && trbuf[i] > max){
                max = trbuf[i];
        }else if(-trbuf[i] > max){
            max = -trbuf[i];
        }
    }
    return max;
}



