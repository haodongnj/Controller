#ifndef FILTER_H
#define FILTER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Filter {
    float *num;
    float *den;
    float *x_buffer;
    float *y_buffer;
    int order;
} Filter_t;

float filter_calc(Filter_t *f, float input);

void filter_init(Filter_t *f, int order, float *num, float *den, float *x_buffer, float *y_buffer);

#ifdef __cplusplus
}
#endif

#endif
