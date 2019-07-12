#include "fir_rc.h"

#if DEBUG 
fir_rc_struct fir_rc_s ;
fir_rc_struct * p_fir_rc_s = & fir_rc_s;
filter_s f_s ;
filter_s * p_f_s = &f_s ;

float num_filter[3] = {0.0f, 0.00726436941467171, 0.00668055316076471};
float den_filter[3] = {1.0f, -1.76382275659635, 0.777767679171789};
int order_filter = 2 ;

void init_fir_rc_debug(){
    int i ; 

    for(i = 0 ; i < MAX_STEPS_FOR_BUFFER; i ++){
        p_fir_rc_s->q_output_buffer[i] = 0.0 ;
        p_fir_rc_s->delay_prev_buffer[i] = 0.0 ;
        p_fir_rc_s->q_input_buffer[i] = 0.0 ;
    }
    p_fir_rc_s->q_input_index = 0 ;
    p_fir_rc_s->q_output_index = 0 ;
    p_fir_rc_s->delay_prev_index = 0 ; 

    p_fir_rc_s->lead_steps = 7 ;

    // Setup the coeff of  filter
    filter_init(p_f_s, num_filter, den_filter, order_filter) ;
    p_fir_rc_s->pfs = p_f_s ;

    p_fir_rc_s->q_main = 0.95 ;
    p_fir_rc_s->q_lr = (1 - p_fir_rc_s->q_main) * 0.5 ;

    p_fir_rc_s->k_rc = 0.8 ;
    p_fir_rc_s->w_dr = 0.5 ;
    p_fir_rc_s->w_dl = 0.5 ;
}

float calc_fir_rc_debug(float freq_grid, float error){
    int n_samples, n_samples_ceiling, index_left, index_right, index_delay_selected ;
    float ret_fir_rc = 0.0, n_samples_float ;

    // update buffer before the delay 
    p_fir_rc_s->delay_prev_buffer[p_fir_rc_s->delay_prev_index] = error + 
        p_fir_rc_s->q_output_buffer[index_move(p_fir_rc_s->q_output_index, - p_fir_rc_s->lead_steps)] ;
    
    n_samples_float = SAMPLE_FREQUENCY / freq_grid ;
    n_samples = (int) n_samples_float ;
    n_samples_ceiling = n_samples + 1 ;

    index_left = index_move(p_fir_rc_s->delay_prev_index, -n_samples_ceiling + p_fir_rc_s->lead_steps + 1) ;
    index_right = index_move(p_fir_rc_s->delay_prev_index, -n_samples + p_fir_rc_s->lead_steps + 1) ;

    p_fir_rc_s->w_dl = n_samples_float - (float)n_samples ;
    p_fir_rc_s->w_dr = (float)n_samples_ceiling - n_samples_float ;

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

#else

void init_fir_rc(fir_rc_struct * p_fir_rc_s, filter_s * p_f_s, float q_main, float k_rc, int steps_lead){
    int i ; 

    for(i = 0 ; i < MAX_STEPS_FOR_BUFFER; i ++){
        p_fir_rc_s->q_output_buffer[i] = 0.0 ;
        p_fir_rc_s->delay_prev_buffer[i] = 0.0 ;
        p_fir_rc_s->q_input_buffer[i] = 0.0 ;
    }
    p_fir_rc_s->q_output_index = 0 ;
    p_fir_rc_s->delay_prev_index = 0 ;
    p_fir_rc_s->q_input_index = 0 ;

    p_fir_rc_s->lead_steps = steps_lead ;
    
    p_fir_rc_s->k_rc = k_rc ;
    p_fir_rc_s->pfs = p_f_s ;

    p_fir_rc_s->q_main = q_main ;
    p_fir_rc_s->q_lr = (1 - p_fir_rc_s->q_main) * 0.5 ;

    p_fir_rc_s->w_dr = 0.5 ;
    p_fir_rc_s->w_dl = 0.5 ;
}

float calc_fir_rc(fir_rc_struct * p_fir_rc_s, float freq_grid, float error){
    int n_samples, n_samples_ceiling, index_left, index_right, index_delay_selected ;
    float ret_fir_rc = 0.0, n_samples_float ;

    // update buffer before the delay 
    p_fir_rc_s->delay_prev_buffer[p_fir_rc_s->delay_prev_index] = error + 
        p_fir_rc_s->q_output_buffer[index_move(p_fir_rc_s->q_output_index, - p_fir_rc_s->lead_steps)] ;
    
    n_samples_float = SAMPLE_FREQUENCY / freq_grid ;
    n_samples = (int) n_samples_float ;
    n_samples_ceiling = n_samples + 1 ;

    index_left = index_move(p_fir_rc_s->delay_prev_index, -n_samples_ceiling + p_fir_rc_s->lead_steps + 1) ;
    index_right = index_move(p_fir_rc_s->delay_prev_index, -n_samples + p_fir_rc_s->lead_steps + 1) ;

    p_fir_rc_s->w_dl = n_samples_float - (float)n_samples ;
    p_fir_rc_s->w_dr = (float)n_samples_ceiling - n_samples_float ;

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

