#include "wdvrc.h"
#include "stdio.h"
#include "stdlib.h" 

extern dvrc_struct * p_dvrc_s ;

int main(void){
    double error, phase, steps_to_see;
    FILE * fp = fopen("test_error_phase.txt", "r") ;
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
    init_wdvrc_simulink() ;
    printf("Initialization completed!\r\n");

    for( int i = 0 ; i < 1e6 ; i ++){
        printf("%lf\t", p_dvrc_s->weight_dm) ;
        fscanf(fp, "%lf,%lf\r\n", &error, &phase) ;
        steps_to_see = calc_wdvrc_simulink(phase, error, 1) ;
        fprintf(fp_out, "%lf\r\n", steps_to_see) ;
    }

    fclose(fp) ;
    fclose(fp_out) ;
    return 0 ;
}