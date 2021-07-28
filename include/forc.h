#ifndef FORC_H
#define FORC_H

#include <filter.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct FORC{

    float *delay_buf;
    float *q_output_buf;

    int idx_delay;
    int idx_q_output;

    int max_steps_each_period;
    int f_control;

    Filter_t q_filter;
    float q_num[3];
    float q_den[3];
    float q_x_buffer[4];
    float q_y_buffer[4];

    Filter_t fractional_filter;
    float f_num[2];
    float f_den[2];
    float f_x_buffer[3];
    float f_y_buffer[3];

    int lead_steps ;
    Filter_t *p_compensator;
    float k ;
}FORC_t;

/**
 * Initialize FORC.
 * @param s pointer to FORC_t struct
 * @param q q value, a zero phase low pass filter is used
 * @param buffer pointer to buffer used for calculation
 * @param n maximum number of samples per cycle  and the minimum size of buffer
 * @param lead_steps lead steps for phase compensation
 * @param k gain of RC
 * @param p_compensator pointer to compensation filter
 * @param f_control control frequency
 *  If p_compensator is NULL, then no calculation is done for compensation filter,
 *  which is highly unrecommended.
 */
void init_forc(FORC_t *s, float q, float *buffer, int n, int lead_steps, float k, Filter_t *p_compensator, float f_control);

/**
 * Calculate FORC.
 * @param s pointer to FORC_t struct.
 * @param error error
 * @param f frequency, 0 is not  allowed otherwise zero division fault would happen
 * @return controller output
 */
float calc_forc(FORC_t *s, float error, float f);

#ifdef __cplusplus
};
#endif

#endif
