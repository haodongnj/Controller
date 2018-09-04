#include "irc.h"

#if SIMULINK_DEBUG 
irc_struct irc ;
irc_struct * irc_s = & irc ;
double num_filter[3] = {0.0f, 0.00726436941467171, 0.00668055316076471};
double den_filter[3] = {1.0f, -1.76382275659635, 0.777767679171789};
int order_filter = 2 ;

void irc_init_simulink(){
    int i = 0 ;
    irc_s->cur_index = 0 ;
    irc_s->k_rc = 0.35 ;
    irc_s->q_center = 0.9 ;
    irc_s->q_lr = (1 - irc_s->q_center) /2 ;
    irc_s->steps_lead = 9 ;
    irc_s->last_error = 0.0f ;
    irc_s->last_phase = DOUBLE_PI - 0.95 * SLICE_ANGLE ;
    irc_s->last_left_index = left_index(irc_s->last_phase) ;
    for(i = 0 ; i < NUMBER_SAMPLES_PERIOD; i ++){
        irc_s->rc_input_buffer[i] = 0.0f ;
        irc_s->rc_output_buffer[i] = 0.0f ;
        irc_s->rc_filtered_buffer[i] = 0.0f ;
    }
    filter_init(&(irc_s->fs), num_filter, den_filter, order_filter) ;
}

double irc_update_simulink(double error, double phase){
    double weight_left, weight_right, weighted_error, fetched_output ;
    double phase_advance = phase_diff(phase, 
                            irc_s->last_phase) ;
    double output = 0.0f ;
    int cur_phase_left_index = left_index(phase) ;
    int steps_to_interpolate = steps_to_interp( cur_phase_left_index, 
                                            irc_s->last_left_index);

    int i = 0, index_to_calc, index_center_output;
    double phase_to_calc ;

    for(i = 1 ; i <= steps_to_interpolate; i ++){
        index_to_calc = index_move(irc_s->last_left_index, i) ;
        index_center_output = index_move(irc_s->cur_index, irc_s->steps_lead - NUMBER_SAMPLES_PERIOD + 2); // + 2 is necessary

        phase_to_calc = index_to_calc * SLICE_ANGLE ;
        weight_left = phase_diff(phase, phase_to_calc) / phase_advance ;
        weight_right = 1 - weight_left ;

        weighted_error = weight_left * irc_s->last_error + 
            weight_right * error ;

        irc_s->rc_input_buffer[irc_s->cur_index] = weighted_error + 
            irc_s->rc_output_buffer[index_move(irc_s->cur_index, -irc_s->steps_lead)];

        output = irc_s->rc_input_buffer[index_center_output] * irc_s->q_center + 
            irc_s->rc_input_buffer[index_move(index_center_output, -1)] * irc_s->q_lr + 
            irc_s->rc_input_buffer[index_move(index_center_output, 1)] * irc_s->q_lr ;

        irc_s->rc_output_buffer[index_move(irc_s->cur_index, 2)] = output ; // + 2 is necessary

        output = filter_calc(&(irc_s->fs), output) ;
        irc_s->rc_filtered_buffer[index_move(irc_s->cur_index, 2)] = output ;// + 2 is necessary

        irc_s->cur_index = index_move(irc_s->cur_index, 1 );
    }
    
    
    irc_s->last_left_index = irc_s->cur_index ;
    irc_s->last_phase = phase ;
    irc_s->last_error = error ;

    // Fetch the output ;
    weight_right = (phase - left_slice(phase)) / SLICE_ANGLE ;
    weight_left = 1 - weight_right ;
    fetched_output = weight_left * irc_s->rc_filtered_buffer[cur_phase_left_index] + 
            weight_right * irc_s->rc_filtered_buffer[index_move(cur_phase_left_index, 1)] ;

    return fetched_output * irc_s->k_rc ;
}


#endif

void irc_init(irc_struct * irc_s, double * num_filter, double * den_filter, int order_filter){
    int i = 0 ;
    irc_s->cur_index = 0 ;
    irc_s->k_rc = 0.2 ;
    irc_s->q_center = 0.95 ;
    irc_s->q_lr = (1 - irc_s->q_center) /2 ;
    irc_s->steps_lead = 12 ;
    irc_s->last_error = 0.0f ;
    irc_s->last_phase = DOUBLE_PI_RC - 0.95 * SLICE_ANGLE ;
    irc_s->last_left_index = left_index(irc_s->last_phase) ;
    for(i = 0 ; i < NUMBER_SAMPLES_PERIOD; i ++){
        irc_s->rc_input_buffer[i] = 0.0f ;
        irc_s->rc_output_buffer[i] = 0.0f ;
        irc_s->rc_filtered_buffer[i] = 0.0f ;
    }
    filter_init(&(irc_s->fs), num_filter, den_filter, order_filter) ;
}

double irc_update(irc_struct * irc_s, double error, double phase){
    double weight_left, weight_right, weighted_error, fetched_output ;
    double phase_advance = phase_diff(phase,
                            irc_s->last_phase) ;
    double output = 0.0f ;
    int cur_phase_left_index = left_index(phase) ;
    int steps_to_interpolate = steps_to_interp( cur_phase_left_index,
                                            irc_s->last_left_index);

    int i = 0, index_to_calc, index_center_output;
    double phase_to_calc ;

    for(i = 1 ; i <= steps_to_interpolate; i ++){
        index_to_calc = index_move(irc_s->last_left_index, i) ;
        index_center_output = index_move(irc_s->cur_index, irc_s->steps_lead - NUMBER_SAMPLES_PERIOD + 2); // + 2 is necessary

        phase_to_calc = index_to_calc * SLICE_ANGLE ;
        weight_left = phase_diff(phase, phase_to_calc) / phase_advance ;
        weight_right = 1 - weight_left ;

        weighted_error = weight_left * irc_s->last_error +
            weight_right * error ;

        irc_s->rc_input_buffer[irc_s->cur_index] = weighted_error +
            irc_s->rc_output_buffer[index_move(irc_s->cur_index, -irc_s->steps_lead)];

        output = irc_s->rc_input_buffer[index_center_output] * irc_s->q_center +
            irc_s->rc_input_buffer[index_move(index_center_output, -1)] * irc_s->q_lr +
            irc_s->rc_input_buffer[index_move(index_center_output, 1)] * irc_s->q_lr ;

        irc_s->rc_output_buffer[index_move(irc_s->cur_index, 2)] = output ; // + 2 is necessary

        output = filter_calc(&(irc_s->fs), output) ;
        irc_s->rc_filtered_buffer[index_move(irc_s->cur_index, 2)] = output ;// + 2 is necessary

        irc_s->cur_index = index_move(irc_s->cur_index, 1 );
    }


    irc_s->last_left_index = irc_s->cur_index ;
    irc_s->last_phase = phase ;
    irc_s->last_error = error ;

    // Fetch the output ;
    weight_right = (phase - left_slice(phase)) / SLICE_ANGLE ;
    weight_left = 1 - weight_right ;
    fetched_output = weight_left * irc_s->rc_filtered_buffer[cur_phase_left_index] +
            weight_right * irc_s->rc_filtered_buffer[index_move(cur_phase_left_index, 1)] ;

    return fetched_output * irc_s->k_rc ;
}

double left_slice(double cur_phase){
    int index = (int)(cur_phase / SLICE_ANGLE) ;
    return index * SLICE_ANGLE ;
}

int left_index(double cur_phase){
    int index = (int)(cur_phase/SLICE_ANGLE) ;
    index %= NUMBER_SAMPLES_PERIOD ;
    return index ;
}

int steps_to_interp(int cur_index, int last_index){
    int steps = cur_index - last_index ;
    if( steps == -199  ){
        steps = 1 ;
    }
    else if( steps == -198 ){
        steps = 2 ;
    }
    else if( steps == -197){
        steps = 3 ;
    }
    else if (steps == -196){
        steps = 4 ;
    }
    return steps ;
}

double phase_diff(double phase, double phase_to_diff){
    double phase_diff = phase - phase_to_diff ;
    if(phase_diff < 0){
        phase_diff += DOUBLE_PI_RC ; // in case that phase_diff > (2 * pi)
    }
    if(phase_diff > DOUBLE_PI_RC){ // Important, do not modify!
        phase_diff -= DOUBLE_PI_RC ;
    }
    return phase_diff ;
}

int index_move(int cur_index, int steps){
    cur_index += steps ;
    if(cur_index < 0){
        cur_index += NUMBER_SAMPLES_PERIOD ;
    }
    cur_index %= NUMBER_SAMPLES_PERIOD ;
    return cur_index ;
}
