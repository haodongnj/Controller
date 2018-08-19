#ifndef DVRC_H
#define DVRC_H

#define MAX_STEPS_FOR_BUFFER 205 
#define MIN_STEPS_FOR_BUFFER 196

#define SIMULINK_DEBUG 1 


typedef struct dvrc_structure{
    double phase_buffer[MAX_STEPS_FOR_BUFFER] ;
    double output_buffer[MAX_STEPS_FOR_BUFFER] ;
    int lead_steps ;

}dvrc_struct ;


void init_dvrc_simulink() ;

double calc_dvrc_simulink() ;

#endif