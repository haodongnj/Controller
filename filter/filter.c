#include "filter.h"

double filter_calc(filter_s* fs, double input){
    int i = 0 ;
    double temp = 0.0f ;
    for(i = 1 ; i <  fs->number_filter_coeffs ; i ++ ){
        temp += fs->num_coeff[i] * fs->x_buffer[i-1] - fs->den_coeff[i] * fs->y_buffer[i-1] ;
    }

    temp += fs->num_coeff[0] * input ;
    temp /= fs->den_coeff[0] ;

    for(i = fs->filter_order - 1 ; i > 0 ; i -- ){
        fs->x_buffer[i] = fs->x_buffer[i - 1] ;
        fs->y_buffer[i] = fs->y_buffer[i - 1] ;
    }
    fs->x_buffer[0] = input ;
    fs->y_buffer[0] = temp ;

    return temp ;
}

void filter_init(filter_s * fs, double * num_c, double * den_c,  int filter_order){
    int i = 0 ;
    fs->filter_order = filter_order ;
    fs->number_filter_coeffs = filter_order + 1 ;

    // Buffer init
    for(i = 0 ; i < fs->filter_order; i ++){
        fs->x_buffer[i] = 0.0f ;
        fs->y_buffer[i] = 0.0f ;
    }
    // Coeff init
    for(i = 0 ; i < fs->number_filter_coeffs; i ++){
        fs->den_coeff[i] = den_c[i] ;
        fs->num_coeff[i] = num_c[i] ;
    }
}
