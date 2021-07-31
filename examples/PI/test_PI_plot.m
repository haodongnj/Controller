clear all ;
close all ;

% for octave : 
pkg load control;

% load data calculated by C code
data = load('pi_results.txt') ;
plot( data(:,1), data(:, 2), '--r');

% ki = 10
g_s_i = tf([10], [1, 0]);
g_z_i = c2d(g_s_i, 1e-4);

% kp = 1
g_pi = 1 + g_z_i;

% input signal, you can replace by yours and do not forget modify in C code
t = data(:, 1) ;
err = 1 - sin(2 * 3.141592654 * 50 * t) ;

hold on ;
lsim(g_pi, err, '--g');
legend( 'C program', 'OCTAVE');

title( 'Comparison of PI output results of C program and OCTAVE');

hold off ;