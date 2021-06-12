clear all ;
close all ;

% for octave : 
pkg load control;

% load data calculated by C code
data = load('filter_results.txt') ;
plot( data(:,1), data(:, 2), '--r')

% filter 
lp_filter_tf = tf([0, 0.00726436941467171, 0.00668055316076471], [1, -1.76382275659635, 0.777767679171789], 1e-4)

% input signal, you can replace by yours and do not forget modify in C code
t = data(:, 1) ;
sin_input = sin(2 * 3.141592654 * 50 * t) ;

hold on ;
lsim(lp_filter_tf, sin_input, '--g')
legend( 'C program','OCTAVE/MATLAB')

hold off ;