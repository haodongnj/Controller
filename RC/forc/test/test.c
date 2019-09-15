#include "fir_rc.h"
#include "stdio.h"
#include "stdlib.h" 

extern fir_rc_struct * p_fir_rc_s ;

int main(void){
    float error, freq, rc_output ;
    FILE * fp = fopen("error_freq_for_test.txt", "r") ;
    if(fp == NULL){
        printf("Error openning file\r\n");
        exit(0) ;
    }
    FILE * fp_out = fopen("text_output.txt", "w") ;
    if(fp_out == NULL){ 
        printf("Error creating file\r\n") ;
        exit(0) ;
    }

    printf("Initialization...\r\n");
    init_fir_rc_debug() ;
    printf("Initialization completed!\r\n");

    for( int i = 0 ; i < 10e4 ; i ++){
        printf("%f\n", p_fir_rc_s->w_dr) ;
        fscanf(fp, "%f,%f\r\n", &error, &freq) ;
        rc_output = calc_fir_rc_debug(freq, error) ;
        fprintf(fp_out, "%f\r\n", rc_output) ;
    }

    fclose(fp) ;
    fclose(fp_out) ;
    return 0 ;
}