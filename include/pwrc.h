#ifndef PWRC_H
#define PWRC_H

#include <filter.h>

#ifdef __cplusplus
extern "C" {
#endif

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

void init_pwrc(PWRC_t *s, float *delay_buf, float *q_output_buf,
               float *phase_buf, int n, int lead_steps, float k, float q,
               Filter_t *p_compensator);
float calc_pwrc(PWRC_t *s, float error, float cur_phase, int flag_actuation);
#ifdef __cplusplus
};
#endif

#endif
