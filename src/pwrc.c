#include <pwrc.h>

#ifdef __cplusplus
extern "C"{
#endif

#define PWRC_PHASE_LOW_MARK_POSITION 3.1415926f
#define PWRC_PHASE_HIGH_MARK_POSITION (3.1415926f+0.016f)

static int idx_forward(int cur_idx, int step, int n_wrap){
  int result_idx = cur_idx + step;
  while(result_idx >= n_wrap){
    result_idx -= n_wrap;
  }
  while(result_idx < 0){
    result_idx += n_wrap;
  }

  return result_idx;
}

static int is_in_interval(float phase, float lower_bound, float higher_bound){
  if(phase < lower_bound || phase > higher_bound){
    return 0;
  }else{
    return 1;
  }
}

static int is_in_phase_interval(float phase, float lower_phase, float higher_phase){
  if(lower_phase < higher_phase){
    return (phase >= lower_phase) && (phase < higher_phase);
  }else{
    return (phase >= lower_phase) || (phase < higher_phase);
  }
}

void init_pwrc(PWRC_t * s, float *delay_buf, float *q_output_buf, float *phase_buf, int n, int lead_steps, float k, float q, Filter_t *p_compensator){
  int i = 0;
  float d0 = 0.0f;
  float d1 = 0.0f;

  s->delay_buf = delay_buf;
  s->q_output_buf = q_output_buf;
  s->phase_buf = phase_buf;

  for(i = 0; i < n; ++i){
    s->delay_buf[i] = 0.0f;
    s->phase_buf[i] = 0.0f;
    s->q_output_buf[i] = 0.0f;
  }

  s->n = n;
  s->lead_steps = lead_steps;

  s->cur_idx = 0;
  s->last_period_phase_idx = 0;
  s->cnt_phase_pass_mark_position = 0;
  s->cnt_avoid_twice_marking = 0;

  s->k = k;
  s->d0 = q;
  s->d1 = (1 - q) * 0.5f;

  s->_cur_idx_q_input = 0;
  s->_q_input_buffer[0] = 0.0f;
  s->_q_input_buffer[1] = 0.0f;
  s->_q_input_buffer[2] = 0.0f;

  s->p_compensator = p_compensator;
}

float calc_pwrc(PWRC_t *s, float error, float cur_phase, int flag_actuation){
  int tmp_idx = 0;
  float last_period_phase = 0.0f;
  float last_period_upper_phase = 0.0f;
  float w1 = 0.0f, w2 = 0.0f;
  float phase_step = 0.0f;
  int N_alpha_k = 0;
  int i = 0, idx_last_q_input = 0;
  float u_rc_k = 0.0f;
  float c_k = 0.0f, c_k_minus_1 = 0.0f, c_weighted = 0.0f;
  float g_k = 0.0f;
  float phase_diff = 0.0f;

  s->phase_buf[s->cur_idx] = cur_phase;

  if(s->cnt_avoid_twice_marking > 0){
    s->cnt_avoid_twice_marking -= 1;
  }

  if(s->cnt_phase_pass_mark_position < 2){
    if(is_in_interval(cur_phase, PWRC_PHASE_LOW_MARK_POSITION, PWRC_PHASE_HIGH_MARK_POSITION)) {
      if (s->cnt_avoid_twice_marking == 0) {
        s->cnt_phase_pass_mark_position += 1;
        s->cnt_avoid_twice_marking = 5;

        if (s->cnt_phase_pass_mark_position == 1) {
          s->last_period_phase_idx = s->cur_idx;
        } else if (s->cnt_phase_pass_mark_position == 2) {
          // try fixing some corner case
          last_period_phase = s->phase_buf[s->last_period_phase_idx];
          if (last_period_phase <= cur_phase) {
            // nothing to do
          } else {
            s->last_period_phase_idx = idx_forward(s->last_period_phase_idx, -1, s->n);
            if(s->phase_buf[s->last_period_phase_idx] < cur_phase){
              s->last_period_phase_idx = idx_forward(s->last_period_phase_idx, -1, s->n);
            }else{
              // 2 step is reasonable to exceed cur_phase
            }
          }
        }
      }else {
        s->cnt_avoid_twice_marking = 0;
      }
    }else{
      // nothing to do
    }
  }else{
    // here, the buffered phases in phase_buf reach almost a period
    // which is about 2 pi
    last_period_phase = s->phase_buf[s->last_period_phase_idx];
    last_period_upper_phase = s->phase_buf[idx_forward(s->last_period_phase_idx, 1, s->n)];
    while(!is_in_phase_interval(cur_phase, last_period_phase, last_period_upper_phase)){
      s->last_period_phase_idx = idx_forward(s->last_period_phase_idx, 1, s->n);
      last_period_phase = s->phase_buf[s->last_period_phase_idx];
      last_period_upper_phase = s->phase_buf[idx_forward(s->last_period_phase_idx, 1, s->n)];
    }

    phase_diff = cur_phase - last_period_phase;
    if(phase_diff < 0.0f){
      phase_diff += PWRC_DOUBLE_PI;
    }

    phase_step = last_period_upper_phase - last_period_phase;
    if(phase_step <= 0.0f ){
      phase_step += PWRC_DOUBLE_PI;
    }

    w1 = phase_diff / phase_step;
    w2 = 1.0f - w1;
  }

  if(flag_actuation){
    tmp_idx = idx_forward(s->cur_idx, -s->lead_steps, s->n);
    s->delay_buf[s->cur_idx] = error * s->k + s->q_output_buf[tmp_idx];

    N_alpha_k = s->cur_idx - s->last_period_phase_idx;
    if(N_alpha_k < 0){
      N_alpha_k += s->n;
    }

    tmp_idx = idx_forward(s->cur_idx, -N_alpha_k+s->lead_steps+1, s->n);
    c_k = s->delay_buf[tmp_idx];
    tmp_idx = idx_forward(tmp_idx, -1, s->n);
    c_k_minus_1 = s->delay_buf[tmp_idx];

    c_weighted = c_k * w1 + c_k_minus_1 * w2;

    idx_last_q_input = s->_cur_idx_q_input - 1;
    if(idx_last_q_input < 0){
      idx_last_q_input += 3;
    }

    for(i = 0; i < 3; ++i){
      if(i == s->_cur_idx_q_input){
        s->_q_input_buffer[i] = c_weighted;
      }
      // One-step lag is added for consideration about physical implementation.
      if(i == idx_last_q_input){
        g_k += s->_q_input_buffer[i] * s->d0;
      }else{
        g_k += s->_q_input_buffer[i] * s->d1;
      }
    }

    s->_cur_idx_q_input += 1;
    if(s->_cur_idx_q_input >= 3){
      s->_cur_idx_q_input = 0;
    }

    s->q_output_buf[s->cur_idx] = g_k;

    u_rc_k = filter_calc(s->p_compensator, g_k);

  }else{
    // nothing to do here
  }

  s->cur_idx = idx_forward(s->cur_idx, 1, s->n);
  return u_rc_k;
}


#ifdef __cplusplus
};
#endif
