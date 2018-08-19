#include "dvrc.h"

#ifdef SIMULINK_DEBUG 
dvrc_struct dvrc_s ;
dvrc_struct * p_dvrc_s ;
#endif 

void init_dvrc_simulink(){
    int i ; 
    for(i = 0 ; i < MAX_STEPS_FOR_BUFFER; i ++){
        p_dvrc_s->phase_buffer[i] = 0.0 ;
        p_dvrc_s->output_buffer[i] = 0.0 ;
    }
    p_dvrc_s->leadsteps = 9 ;
    
}

double calc_dvrc_simulink(){

}

