#include <forc.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Move forward index of an array.
 * @param cur_idx current index
 * @param steps_forward number of steps to move forward
 * @param n upper bound of index(open)
 * @return result index
 */
static int idx_forward(int cur_idx, int steps_forward, int n) {
    int idx = cur_idx + steps_forward;

    while (idx >= n) {
        idx -= n;
    }

    /// Necessary to check here.
    while (idx < 0) {
        idx += n;
    }

    return idx;
}

void
init_forc(FORC_t *s, float q, float *buffer, int n, int lead_steps, float k, Filter_t *p_compensator, float f_control) {

    int i;
    for (i = 0; i < n; ++i) {
        buffer[i] = 0;
    }

    s->q_num[0] = (1 - q) * 0.5;
    s->q_num[1] = q;
    s->q_num[2] = s->q_num[0];
    s->q_den[0] = 1;
    s->q_den[1] = 0;
    s->q_den[2] = 0;
    filter_init(&(s->q_filter), 2, s->q_num, s->q_den, s->q_x_buffer, s->q_y_buffer);

    s->f_num[0] = 0.5;
    s->f_num[1] = 0.5;
    s->f_den[0] = 1.0;
    s->f_den[1] = 0.0;
    filter_init(&(s->fractional_filter), 1, s->f_num, s->f_den, s->f_x_buffer, s->f_y_buffer);

    s->delay_buf = buffer + lead_steps;
    s->q_output_buf = buffer;

    s->idx_delay = 0;
    s->idx_q_output = 0;

    s->max_steps_each_period = n;

    s->f_control = f_control;

    s->lead_steps = lead_steps;
    s->p_compensator = p_compensator;
    s->k = k;
}

float calc_forc(FORC_t *s, float error, float f) {
    int n, n_ceil, idx;
    float result = 0.0f, n_float = 0.0f;
    float w_left = 0.0f, w_right = 0.0f;

    /// update buffer before the delay
    s->delay_buf[s->idx_delay] = error + s->q_output_buf[s->idx_q_output];

    n_float = s->f_control / f;
    n = (int) n_float;
    n_ceil = n + 1;

    idx = idx_forward(s->idx_delay, -n + s->lead_steps + 1, s->max_steps_each_period - s->lead_steps);

    w_left = n_float - (float) n;
    w_right = (float) n_ceil - n_float;

    s->f_num[0] = w_right;
    s->f_num[1] = w_left;

    result = filter_calc(&(s->fractional_filter), s->delay_buf[idx]);
    result = filter_calc(&(s->q_filter), result);
    s->q_output_buf[s->idx_q_output] = result;

    /// compensator: low-pass filter
    result = filter_calc(s->p_compensator, result);

    // update index:
    s->idx_delay = idx_forward(s->idx_delay, 1, s->max_steps_each_period - s->lead_steps);
    s->idx_q_output = idx_forward(s->idx_q_output, 1, s->lead_steps);

    return result * s->k;
}

#ifdef __cplusplus
}
#endif
