#ifndef RC_H
#define RC_H

#include <filter.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct RC{
    /// q value for repetitive controller
    float q;
    /// pointer to buffer
    float *output_buffer;
    /// index for output buffer
    int counter;
    /// number of samples per cycle
    int n_samples_per_cycle;

    int lead_steps;
    Filter_t *p_compensator;
    float k;
} RC_t;

/**
 * Initialize repetitive controller.
 * @param s pointer to RC_t struct
 * @param q q value of RC controller
 * @param buffer pointer to RC buffer
 * @param n number of samples per cycle
 * @param lead_steps: lead_steps to compensate phase lag
 * @param p_compensator: pointer to Filter_t struct instance;
 *  If p_compensator is NULL, then no calculation is done for compensation filter.
 */
void rc_init(RC_t *s, float q, float *buffer, int n, int lead_steps, float k, Filter_t *p_compensator);

/**
 * Calculate repetitive controller.
 * @param s pointer to RC_t struct
 * @param error input error
 * @return controller output
 */
float rc_calc(RC_t *s, float error);

#ifdef __cplusplus
};
#endif

#endif
