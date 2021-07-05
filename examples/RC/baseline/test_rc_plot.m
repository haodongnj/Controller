close all;
clear ;
data = load('test_rc_output.txt') ;

% Octave transfer function
pkg load control
z = tf([1, 0], [1], 1e-4);
q = 0.9;
g_rc = z^(-200)/(1 - q * z ^(-200));
input = sin(2 * pi * 50 * data(:,1));
output1 = lsim(g_rc, input);
close all;


figure;
plot(data(:, 1), output1, '--g');
hold on;

% C API results
plot(data(:, 1), data(:, 2), '--r') ;
hold off; 

legend('Ocatve', 'C API');
title('RC validation')

figure();
hold on;
plot(data(:, 1), input) ;
plot(data(:, 1), data(:, 2)) ;
plot(data(:, 1), data(:, 3)) ;
plot(data(:, 1), data(:, 4)) ;
legend('error', 'RC1', 'RC2', 'RC3');
title('Comparison of different RCs');
xlim([0, 0.2]);
