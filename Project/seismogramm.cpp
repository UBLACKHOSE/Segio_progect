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
}
