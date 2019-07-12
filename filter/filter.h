#ifndef FILTER_H_
#define FILTER_H_

// determines the maximum order of filters: MAX_NUMBER_FILTER_COEFFS - 1
#define MAX_NUMBER_FILTER_COEFFS 4 
#define MAX_FILTER_ORDER (MAX_NUMBER_FILTER_COEFFS-1)

typedef struct filter_struct{
    double num_coeff[MAX_NUMBER_FILTER_COEFFS] ;
    double den_coeff[MAX_NUMBER_FILTER_COEFFS] ;
    double x_buffer[MAX_FILTER_ORDER];
    double y_buffer[MAX_FILTER_ORDER];
    int filter_order ;
    int number_filter_coeffs ;
} filter_s ;

double filter_calc(filter_s* fs, double input);
void filter_init(filter_s * fs, double * num_c, double * den_c,  int filter_order);

#endif
