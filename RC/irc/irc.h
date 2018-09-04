#ifndef IRC_H
#define IRC_H

#include "filter.h"

#define NUMBER_SAMPLES_PERIOD 200U
#define SIMULINK_DEBUG 0
#define SLICE_ANGLE 0.0314159265359f
#define DOUBLE_PI_RC  6.28318530718f

typedef struct irc_structure{
    double rc_input_buffer[NUMBER_SAMPLES_PERIOD];
    double rc_output_buffer[NUMBER_SAMPLES_PERIOD] ;
    double rc_filtered_buffer[NUMBER_SAMPLES_PERIOD] ;
    int cur_index ;
    int steps_lead ;
    double q_center ;
    double q_lr ;
    double k_rc ;
    double last_phase ;
    double last_left_index ;
    double last_error ;
    filter_s fs ;
}irc_struct;

#if SIMULINK_DEBUG 

void irc_init_simulink();
double irc_update_simulink(double error, double phase);

#endif

void irc_init(irc_struct *,  double *, double *, int);
double irc_update(irc_struct *, double error, double phase);

double left_slice(double cur_phase);
int left_index(double cur_phase);
int steps_to_interp(int cur_index, int last_index);
double phase_diff(double phase, double phase_to_diff);
int index_move(int cur_index, int steps);

#endif
