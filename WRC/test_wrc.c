#include "wrc.h"
#include "stdio.h"

extern wrc_struct * wrc_s ;

int main(void){
    FILE* fp = fopen("freq_and_error.txt", "r");
    FILE* fp_out = fopen("test_wrc_results.txt", "w");
    double freq, error, result ;

    wrc_init_simulink(0.35, 9) ;
    for(int i = 0 ; i < 400; i ++){
        fscanf(fp, "%lf,%lf\n", &freq, &error);
        //printf("Freq:%lf\tError:%lf\n", freq, error);
        result = wrc_update_simulink(freq, error);
        fprintf(fp_out, "%lf\r\n", result);
    }

    fclose(fp);
    fclose(fp_out);
    return 0 ;
}