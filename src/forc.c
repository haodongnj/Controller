#include <forc.h>

void init_forc(FORC_t *s, float q_main, int lead_steps, float k, Filter* p_compensator){
    int i ; 

    for(i = 0 ; i < MAX_STEPS_FOR_BUFFER; i ++){
        p_fir_rc_s->q_output_buffer[i] = 0.0 ;
        p_fir_rc_s->delay_prev_buffer[i] = 0.0 ;
        p_fir_rc_s->q_input_buffer[i] = 0.0 ;
    }
    p_fir_rc_s->q_output_index = 0 ;
    p_fir_rc_s->delay_prev_index = 0 ;
    p_fir_rc_s->q_input_index = 0 ;

    p_fir_rc_s->lead_steps = lead_steps;
    
    p_fir_rc_s->k_rc = k_rc ;
    p_fir_rc_s->pfs = p_f_s ;

    p_fir_rc_s->q_main = q_main ;
    p_fir_rc_s->q_lr = (1 - p_fir_rc_s->q_main) * 0.5 ;

    p_fir_rc_s->w_dr = 0.5 ;
    p_fir_rc_s->w_dl = 0.5 ;
}

float calc_forc(FORC_t *s, float error, float f){
    int n_samples, n_samples_ceiling, index_left, index_right, index_delay_selected ;
    float ret_fir_rc = 0.0, n_samples_float ;

    // update buffer before the delay 
    p_fir_rc_s->delay_prev_buffer[p_fir_rc_s->delay_prev_index] = error + 
        p_fir_rc_s->q_output_buffer[index_move(p_fir_rc_s->q_output_index, - p_fir_rc_s->lead_steps)] ;
    
    n_samples_float = s->f_control / f;
    n_samples = (int) n_samples_float ;
    n_samples_ceiling = n_samples + 1 ;

    index_left = index_move(p_fir_rc_s->delay_prev_index, -n_samples_ceiling + p_fir_rc_s->lead_steps + 1) ;
    index_right = index_move(p_fir_rc_s->delay_prev_index, -n_samples + p_fir_rc_s->lead_steps + 1) ;

    w_left = n_samples_float - (float)n_samples ;
    w_right = (float)n_samples_ceiling - n_samples_float ;

    p_fir_rc_s->q_input_buffer[p_fir_rc_s->q_input_index] = 
        p_fir_rc_s->w_dl * p_fir_rc_s->delay_prev_buffer[index_left] + 
        p_fir_rc_s->w_dr * p_fir_rc_s->delay_prev_buffer[index_right] ;

    index_delay_selected = index_move(p_fir_rc_s->q_input_index, -1 ) ;

    ret_fir_rc = p_fir_rc_s->q_input_buffer[index_delay_selected] * p_fir_rc_s->q_main + 
        p_fir_rc_s->q_input_buffer[index_move(index_delay_selected, 1)] * p_fir_rc_s->q_lr + 
        p_fir_rc_s->q_input_buffer[index_move(index_delay_selected, -1)] * p_fir_rc_s->q_lr ;

    p_fir_rc_s->q_output_buffer[p_fir_rc_s->q_output_index] = ret_fir_rc ;

    ret_fir_rc = filter_calc(p_fir_rc_s->pfs, ret_fir_rc) ; // Lowpass filter

    // update index:
    p_fir_rc_s->q_input_index = index_move(p_fir_rc_s->q_input_index, 1) ;
    p_fir_rc_s->q_output_index = index_move(p_fir_rc_s->q_output_index, 1) ;
    p_fir_rc_s->delay_prev_index = index_move(p_fir_rc_s->delay_prev_index, 1) ;

    return ret_fir_rc * p_fir_rc_s->k_rc; 
}

int index_forward(FORC_t s, int cur_index, int steps_forward){
    int idx = cur_index + steps_forward;

    while( idx >= s->max_steps_each_period){
        idx -= s->max_steps_each_period;
    }

    while( idx < 0 ){
        idx += s->max_steps_each_period;
    }
    return idx;
}

