#ifndef WRC_H
#define WRC_H
#include "filter.h"

#define NUMBER_SAMPLES_PERIOD 200
#define MAX_NUMBER_SAMPLES_PERIOD 205 
#define SAMPLES_PER_SECOND 1e4f

#define SIMULINK_DEBUG 1 

typedef struct wrc_structure{
    double rc_input_buffer[MAX_NUMBER_SAMPLES_PERIOD] ;
    double freq_buffer[MAX_NUMBER_SAMPLES_PERIOD] ;
    filter_s fs ;
    int cur_index ;
    int steps_to_lead ;
    double k_rc ;
    double rc_output_buffer[MAX_NUMBER_SAMPLES_PERIOD] ;
} wrc_struct ;

void wrc_init(wrc_struct * wrc_s, double krc, int steps_lead, double * num_filter, double * den_filter, int order_filter);
double wrc_update(wrc_struct * wrc_s, double freq_grid, double error);
int index_move(int cur_index, int steps);

#if SIMULINK_DEBUG
void wrc_init_simulink();
double wrc_update_simulink(double freq_grid, double error);
#endif

#endif