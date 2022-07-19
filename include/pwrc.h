#ifndef PWRC_H
#define PWRC_H

#include <filter.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PWRC_DOUBLE_PI  6.283185307179586f

typedef struct PWRC {
  float *delay_buf;
  float *q_output_buf;
  float *phase_buf;

  int n;
  int lead_steps;
  int cur_idx;
  int last_period_phase_idx;
  int cnt_phase_pass_mark_position;
  int cnt_avoid_twice_marking;
  Filter_t *p_compensator;
  float _q_input_buffer[3];
  float d0;
  float d1;
  int _cur_idx_q_input;
  float k;
} PWRC_t;

/**
 * initialize PWRC_t struct
 * @param s pointer to PWRC_t struct
 * @param delay_buf buffer for internal delay
 * @param q_output_buf buffer for output of q filter
 * @param phase_buf buffer for phases
 * @param n size of above 3 buffers, they should have the same size
 * @param lead_steps lead steps of RC
 * @param k RC gain
 * @param q q efficient of q filter in form of d1 * z + d0 + d1 * z^(-1), in which
 * d0 = q and d1 = (1 - d0) * 0.5.
 * @param p_compensator pointer to compensator filter
 */
void init_pwrc(PWRC_t *s, float *delay_buf, float *q_output_buf,
               float *phase_buf, int n, int lead_steps, float k, float q,
               Filter_t *p_compensator);

/**
 * calculation of PWRC
 * @param s pointer to PWRC_t struct
 * @param error input error
 * @param cur_phase current phase angle corresponding to input error
 * @param flag_actuation if controller is in actuation mode, e.g. this flag
 * should be set to 0 for at least 1 period (2 periods better) for phase angles
 * to be buffered and set to 1 after the inverter is connected to the grid.
 * @return output of PWRC
 */
float calc_pwrc(PWRC_t *s, float error, float cur_phase, int flag_actuation);

#ifdef __cplusplus
};
#endif

#endif
