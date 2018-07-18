#include "wrc.h"

void wrc_init(wrc_struct * wrc_s, double krc, int steps_lead, double * num_filter, double * den_filter, int order_filter){
    int i = 0 ;
    for(i = 0 ; i < NUMBER_SAMPLES_PERIOD; i ++){
        wrc_s->rc_input_buffer[i] = 0.0f ;
        wrc_s->rc_output_buffer[i] = 0.0f ;
        wrc_s->freq_buffer[i] = 50.0f ;
    }
    filter_init(&wrc_s->fs, num_filter, den_filter, order_filter) ;
    wrc_s->k_rc = krc ;
    wrc_s->cur_index = 0 ;
    wrc_s->steps_to_lead = steps_lead ;
}

double wrc_update(wrc_struct * wrc_s, double freq_grid, double error){
    double output, n_samples ;
    int steps_left_delay, steps_right_delay ;
    double weight_left, weight_right ;

    // update rc buffer:
    wrc_s->rc_input_buffer[wrc_s->cur_index] = wrc_s->rc_output_buffer[index_move(wrc_s->cur_index, - wrc_s->steps_to_lead)]
                                               + error ;
    // save the frequency into buffer :
    wrc_s->freq_buffer[wrc_s->cur_index] = freq_grid ;

    // Calculate the output buffer:
    n_samples = SAMPLES_PER_SECOND / freq_grid ;
    steps_left_delay = - (int)n_samples - 1 + wrc_s->steps_to_lead ;
    steps_right_delay = steps_left_delay + 1 ;
     
    weight_left = n_samples - (int)n_samples  ;
    weight_right =  1 - weight_left ;
    weight_left *= wrc_s->rc_input_buffer[index_move(wrc_s->cur_index, steps_left_delay)];
    weight_right *= wrc_s->rc_input_buffer[index_move(wrc_s->cur_index, steps_right_delay)];

    output = weight_left + weight_right ;
    wrc_s->rc_output_buffer[wrc_s->cur_index] =  output ;
    // Update index
    wrc_s->cur_index = index_move(wrc_s->cur_index, 1);

    output = filter_calc(&(wrc_s->fs), output) * wrc_s->k_rc ;
    return output ;
}

int index_move(int cur_index, int steps){
    cur_index += steps ;
    if(cur_index < 0){
        cur_index += MAX_NUMBER_SAMPLES_PERIOD ;
    }
    cur_index %= MAX_NUMBER_SAMPLES_PERIOD ;
    return cur_index ;
}

#if SIMULINK_DEBUG 
wrc_struct wrc_struct_sample ;
wrc_struct * wrc_s = & wrc_struct_sample ;
double num_filter[3] = {0.0f, 0.00726436941467171, 0.00668055316076471};
double den_filter[3] = {1.0f, -1.76382275659635, 0.777767679171789};
int order_filter = 2 ;

void wrc_init_simulink(){
    int i = 0 ;
    for(i = 0 ; i < MAX_NUMBER_SAMPLES_PERIOD; i ++){
        wrc_s->rc_input_buffer[i] = 0.0f ;
        wrc_s->rc_output_buffer[i] = 0.0f ;
        wrc_s->freq_buffer[i] = 50.0f ;
    }
    filter_init(& wrc_s->fs, num_filter, den_filter, order_filter) ;
    wrc_s->k_rc = 0.35 ;
    wrc_s->cur_index = 0 ;
    wrc_s->steps_to_lead = 9 ;
}

double wrc_update_simulink(double freq_grid, double error){
    double output, n_samples ;
    int steps_left_delay, steps_right_delay ;
    double weight_left, weight_right ;

    // update rc buffer:
    wrc_s->rc_input_buffer[wrc_s->cur_index] = wrc_s->rc_output_buffer[index_move(wrc_s->cur_index, - wrc_s->steps_to_lead)]
                                               + error ;
    // save the frequency into buffer :
    wrc_s->freq_buffer[wrc_s->cur_index] = freq_grid ;

    // Calculate the output buffer:
    n_samples = SAMPLES_PER_SECOND / freq_grid ;
    steps_left_delay = - (int)n_samples - 1 + wrc_s->steps_to_lead ;
    steps_right_delay = steps_left_delay + 1 ;
     
    weight_left = n_samples - (int)n_samples  ;
    weight_right =  1 - weight_left ;
    weight_left *= wrc_s->rc_input_buffer[index_move(wrc_s->cur_index, steps_left_delay)];
    weight_right *= wrc_s->rc_input_buffer[index_move(wrc_s->cur_index, steps_right_delay)];

    output = weight_left + weight_right ;
    wrc_s->rc_output_buffer[wrc_s->cur_index] =  output ;
    // Update index
    wrc_s->cur_index = index_move(wrc_s->cur_index, 1);

    output = filter_calc(&(wrc_s->fs), output) * wrc_s->k_rc ;
    return output ;
}

#endif