clear; 
close all ;

data = load('test_forc_output.txt') ;
plot(data(:,1), data(:,2));
hold on;
plot(data(:,1), data(:,3));
legend('error', 'FORC output');
