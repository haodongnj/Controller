#ifndef RC_H
#define RC_H

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
} RC_t;

/**
 * Initialize repetitive controller.
 * @param s pointer to RC_t struct
 * @param q q value of RC controller
 * @param buffer pointer to RC buffer
 * @param n number of samples per cycle
 */
void rc_init(RC_t *s, float q, float *buffer, int n);

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
