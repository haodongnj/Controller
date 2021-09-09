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

/**
 * @brief filter calculation
 * 
 * @param f pointer to Filter_t struct
 * @param input input signal of filter
 * @return float output signal of filter
 */
float filter_calc(Filter_t *f, float input);

/**
 * @brief 
 * 
 * @param f filter initialization
 * @param order order of filter
 * @param num numerator coefficient of filter
 * @param den denumerator coefficient of filter
 * @param x_buffer buffer for input signal
 * @param y_buffer buffer for output signal
 */
void filter_init(Filter_t *f, int order, float *num, float *den, float *x_buffer, float *y_buffer);

#ifdef __cplusplus
}
#endif

#endif
