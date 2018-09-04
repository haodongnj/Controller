#include "wdvrc.h"

#if SIMULINK_DEBUG 
dvrc_struct dvrc_s ;
dvrc_struct * p_dvrc_s = & dvrc_s;
filter_s f_s ;
filter_s * p_f_s = &f_s ;

double num_filter[3] = {0.0f, 0.00726436941467171, 0.00668055316076471};
double den_filter[3] = {1.0f, -1.76382275659635, 0.777767679171789};
int order_filter = 2 ;


void init_dvrc_simulink(){
    int i ; 
    double phase_angle ;
    for(i = 0 ; i < MAX_STEPS_FOR_BUFFER; i ++){
        phase_angle = i * SLICE_ANGLE ;
        phase_angle = (phase_angle > DOUBLE_PI_DVRC) ? (phase_angle - DOUBLE_PI_DVRC) : (phase_angle) ;
        p_dvrc_s->phase_buffer[i] =  phase_angle ;
        p_dvrc_s->q_output_buffer[i] = 0.0 ;
        p_dvrc_s->delay_prev_buffer[i] = 0.0 ;
    }
    p_dvrc_s->lead_steps = 1;

    // Setup the coeff of  filter
    filter_init(p_f_s, num_filter, den_filter, order_filter) ;
    p_dvrc_s->pfs = p_f_s ;

    p_dvrc_s->q_main = 0.95 ;
    p_dvrc_s->q_lr = (1 - p_dvrc_s->q_main) * 0.5 ;
    p_dvrc_s->weight_dm = 0.5 ;
    p_dvrc_s->weight_dl = 0.5 ;
    p_dvrc_s->error_flag = 0 ;

    p_dvrc_s->q_output_index = 0 ;
    p_dvrc_s->delay_prev_index = 0 ;
    p_dvrc_s->phase_index = 0 ;
}

double calc_dvrc_simulink(double phase, double error, int flag_start_calc){
    int steps_delay = find_varying_delay(p_dvrc_s, phase) ;
    int index_delay_selected ;
    double ret_dvrc = 0.0, w_dl, w_dm ;

    // When in closedloop, RC results
    if( flag_start_calc){
        // update buffer before the delay 
        p_dvrc_s->delay_prev_buffer[p_dvrc_s->delay_prev_index] = error + 
            p_dvrc_s->q_output_buffer[index_move(p_dvrc_s->q_output_index, - p_dvrc_s->lead_steps)] ;
        
        // update buffer of q filtered buffer:
        index_delay_selected = index_move(p_dvrc_s->delay_prev_index, -steps_delay + p_dvrc_s->lead_steps) ;

        w_dl = p_dvrc_s->delay_prev_buffer[index_delay_selected] * p_dvrc_s->q_main + 
            p_dvrc_s->delay_prev_buffer[index_move(index_delay_selected, 1)] * p_dvrc_s->q_lr + 
            p_dvrc_s->delay_prev_buffer[index_move(index_delay_selected, -1)] * p_dvrc_s->q_lr ;

        w_dl = w_dl * p_dvrc_s->weight_dl ;

        index_delay_selected = index_move(index_delay_selected, -1) ;

        w_dm = p_dvrc_s->delay_prev_buffer[index_delay_selected] * p_dvrc_s->q_main + 
            p_dvrc_s->delay_prev_buffer[index_move(index_delay_selected, 1)] * p_dvrc_s->q_lr + 
            p_dvrc_s->delay_prev_buffer[index_move(index_delay_selected, -1)] * p_dvrc_s->q_lr ;

        w_dm = w_dm * p_dvrc_s->weight_dm ;
        
        ret_dvrc = w_dl + w_dm ;

        p_dvrc_s->q_output_buffer[p_dvrc_s->q_output_index] = ret_dvrc ;

        ret_dvrc = filter_calc(p_dvrc_s->pfs, ret_dvrc) ; // Lowpass filter 

        // update index:
        p_dvrc_s->q_output_index = index_move(p_dvrc_s->q_output_index, 1);
        p_dvrc_s->delay_prev_index = index_move(p_dvrc_s->delay_prev_index, 1);

    }

    p_dvrc_s->phase_buffer[ p_dvrc_s-> phase_index ] = phase ;
    // Update phase index 
    p_dvrc_s->phase_index = index_move(p_dvrc_s->phase_index, 1) ;

    // When in openloop, only phase_buffer and phase_index is updated.
    if(!flag_start_calc){
        return steps_delay ;
    }else{
        return ret_dvrc ;
    }
}

#endif 


int index_move(int cur_index, int steps_to_move){
    int ret_index = cur_index + steps_to_move ;
    if(ret_index >= MAX_STEPS_FOR_BUFFER){
        ret_index -= MAX_STEPS_FOR_BUFFER ;
    }
    else if( ret_index < 0 ){
        ret_index += MAX_STEPS_FOR_BUFFER ;
    }
    return ret_index ;
}

int find_varying_delay(dvrc_struct * ps, double cur_phase){
    // Simple implementation:
    int i = 0, index_moved, ret_steps = STEPS_AT_BASE_FREQ  ;
    double min_abs_error = DOUBLE_PI_DVRC, temp_error ; // A number big enough  
    double phase_step, phase_error_dm, phase_error_dl ;

    for(i = MIN_STEPS_FOR_BUFFER; i < MAX_STEPS_FOR_BUFFER; i ++){
        index_moved = index_move(ps->phase_index, -i) ;
        temp_error = compare_phase_angle(cur_phase, ps->phase_buffer[index_moved]) ;
        if( temp_error >= 0){
            phase_step = compare_phase_angle( ps->phase_buffer[index_move(index_moved, 1)] ,
                ps->phase_buffer[index_moved]) ;
            // in case of 0 division error
            if(phase_step == 0){
                phase_step = SLICE_ANGLE ;
                ps->error_flag |= 1 ;
            }
            ps->weight_dl = temp_error / phase_step ;
            if(ps->weight_dl > 1.0){
                ps->weight_dl = 1.0 ;
                ps->error_flag |= 2 ;
            }
            ps->weight_dm = 1.0 - ps->weight_dl ;

            return (i - 1) ;
        }
    }
    return 200 ;
}

double compare_phase_angle(double cur_phase, double prev_phase){
    double error = cur_phase - prev_phase ;
    if(error >  PI_DVRC ){
        error -= DOUBLE_PI_DVRC ;
    }
    else if( error < -PI_DVRC ){
        error += DOUBLE_PI_DVRC ;
    }

    return error ;
}