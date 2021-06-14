#include <filter.h>

#ifdef __cplusplus
extern "C" {
#endif

float filter_calc(Filter_t *f, float input) {
    int i;
    float temp = 0.0f;
    for (i = 1; i < f->order + 1; i++) {
        temp += f->num[i] * f->x_buffer[i - 1] - f->den[i] * f->y_buffer[i - 1];
    }

    temp += f->num[0] * input;
    temp /= f->den[0];

    for (i = f->order - 1; i > 0; i--) {
        f->x_buffer[i] = f->x_buffer[i - 1];
        f->y_buffer[i] = f->y_buffer[i - 1];
    }
    f->x_buffer[0] = input;
    f->y_buffer[0] = temp;

    return temp;
}

void filter_init(Filter_t *f, int order, float *num, float *den, float *x_buffer, float *y_buffer) {
    int i = 0;
    f->order = order;

    /// Coefficients initialization.
    f->den= den;
    f->num= num;

    f->x_buffer = x_buffer;
    f->y_buffer = y_buffer;

    // Buffer initialization.
    for (i = 0; i < f->order; i++) {
        f->x_buffer[i] = 0.0f;
        f->y_buffer[i] = 0.0f;
    }
}

#ifdef __cplusplus
}
#endif
