#include <rc.h>

#ifdef __cplusplus
extern "C"{
#endif

void rc_init(RC_t *s, float q, float *buffer, int n){
    int i ;

    s->q = q;
    s->n_samples_per_cycle = n;
    s->output_buffer = buffer;

    for(i = 0; i < s->n_samples_per_cycle; i++ ){
        s->output_buffer[i] = 0.0f ;
    }
    s->counter = 0;
}

float rc_calc(RC_t *s, float error){
    float output = s->output_buffer[s->counter];

    // Simple implementation of Repetitive Controller 
    // when Q is a positive constant smaller than 1.
    s->output_buffer[s->counter] = s->q * s->output_buffer[s->counter] + error ;

    s->counter ++;
    if( s->counter >= s->n_samples_per_cycle){
        s->counter = 0 ;
    }

    return output ;
}

#ifdef __cplusplus
};
#endif
