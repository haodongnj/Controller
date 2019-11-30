#ifndef FILTER_H_
#define FILTER_H_

/**
 * Determine the maximum order of filters: MAX_NUMBER_FILTER_COEFFS - 1
 * You can modify this macro definition as you wish 
**/
#define MAX_NUMBER_FILTER_COEFFS 4 
#define MAX_FILTER_ORDER (MAX_NUMBER_FILTER_COEFFS-1)

typedef struct filter_struct{
    float num_coeff[MAX_NUMBER_FILTER_COEFFS] ;
    float den_coeff[MAX_NUMBER_FILTER_COEFFS] ;
    float x_buffer[MAX_FILTER_ORDER];
    float y_buffer[MAX_FILTER_ORDER];
    int filter_order ;
    int number_filter_coeffs ;
} filter_s ;

float filter_calc(filter_s* fs, float input);
void filter_init(filter_s * fs, float * num_c, float * den_c,  int filter_order);

#endif
