#include "pr.h"

/**
 * @brief Initialize the prStruct for a PR controller 
 * 
 * @param s The pointer to prStruct
 * @param kp_set Value of kp to be set 
 * @param kr_set Value of kr to be set, which is the gain for fundamental signal 
 * @param wi_set Vaule of wi to be set, which determines the bandwidth at fundamental frequency, in radians per second
 * @param ts Value of sampling period to be set, in seconds
 */
void pr_init(prStruct * s, float kp_set, float kr_set, float wi_set, float ts){
    s->kp = kp_set ;
    s->kr = kr_set ;
    s->wi = wi_set ;
    s->ts = ts ;
    s->output_of_feedback = 0.0f ;
    s->output_of_backward_integrator = 0.0f ;
    s->output_of_forward_integrator = 0.0f ;
    s->reference = 0.0f ;
}

/**
 * @brief Update reference signal of PR controller
 * 
 * @param s The pointer to prStruct
 * @param ref The reference to be set
 */
void pr_update_ref(prStruct * s, float ref){
    s->reference = ref ;
}

/**
 * @brief Second Order Generalized Integratior(SOGI) implementation for frequency adaptive resonance controller
 * 
 * @param s The pointer to prStruct
 * @param feedback Feedback signal  
 * @param wg Fundamental angular frequency, in radians per second.
 * @return float The output of PR controller
 */
float pr_calc(prStruct * s, float feedback, float wg){
    float error = s->reference - feedback ;

    float input_of_forward_integrator = 2 * s->wi * s->kr * error - s->output_of_feedback;
    // Forward integrator :
    s->output_of_forward_integrator += s->ts *  input_of_forward_integrator;

    // Backward integrator:
    s->output_of_backward_integrator += s->ts * s->output_of_forward_integrator * wg * wg ;

    s->output_of_feedback = s->output_of_backward_integrator + 2 * s->wi * s->output_of_forward_integrator ;

    return s->output_of_forward_integrator + s->kp * error;
}
