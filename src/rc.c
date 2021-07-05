#include <rc.h>

#ifdef __cplusplus
extern "C"{
#endif

void rc_init(RC_t *s, float q, float *buffer, int n, int lead_steps, float k, Filter_t *p_compensator){
    int i ;

    s->q = q;
    s->n_samples_per_cycle = n;
    s->output_buffer = buffer;

    for(i = 0; i < s->n_samples_per_cycle; i++ ){
        s->output_buffer[i] = 0.0f ;
    }
    s->counter = 0;

    s->lead_steps = lead_steps;
    s->k = k;
    s->p_compensator = p_compensator;
}

float rc_calc(RC_t *s, float error){
    float output = 0.0;
    int idx_output = 0;

    idx_output = s->counter + s->lead_steps;
    if(idx_output > s->n_samples_per_cycle){
        idx_output -= s->n_samples_per_cycle;
    }

    output = s->output_buffer[idx_output];

    /// only if compensation filter is set.
    if(s->p_compensator){
        output = filter_calc(s->p_compensator, output);
    }

    // Simple implementation of Repetitive Controller
    // when Q is a positive constant smaller than 1.
    s->output_buffer[s->counter] = s->q * s->output_buffer[s->counter] + error ;

    s->counter ++;
    if( s->counter >= s->n_samples_per_cycle){
        s->counter = 0 ;
    }

    return output * s->k ;
}

#ifdef __cplusplus
};
#endif
