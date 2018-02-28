%% Simulation for LCL resonance
% By donghao lab_209
% 2017 2 18 
close all ;
clear all ;

%% Parameters :
L1 = 600e-6 ; % Inductor close to inverter, 600uH
L2 = 150e-6 ; % Inductor close to grid 150uH
C = 10e-6 ; % Capacitor 10 uF

r1 = 0 ; % line resistor of L1
r2 = 0 ; %line resistor of L2

Hi2 =  1 ; % feedback gain of grid current
V_tri = 3.05 ;
V_dc = 360 ;
Ginv =  V_dc / V_tri ; % average state model gain of inverter

f_sw = 10e3 ; % switch frequency : 10kHz

fr = 1/(2 * pi) * sqrt((L1 + L2)/(L1 * L2 * C)) ;

fo = 50 ; % fundmental frequency 50Hz 
Vg = 220 ; % rms value of grid voltage 

%% This is the design procedure for Pi controller and capacitor
%% current feedback coefficient.
figure('name', 'Acquired Hi1 and fc');
hold on ;
for fc = 200:1:5000
    for Hi1 = 0:0.001:1
    % Actually, kp is approximately proportional to fc(crossover frequency)
    Kp = 2 * pi * fc * (L1 + L2) / ( Hi2 * Ginv);
    Ig2 = 2 ; % Error of Ig ;
    T_fo = 20 * log10(Vg / ( 2 * pi * fo * (L1 + L2) * Ig2 ));
    Ki = 4 * pi^2 * fo * (L1 + L2)/(Hi2 * Ginv) * sqrt((10^(T_fo/20) * fo )^2 - fc^2);
    PM = atan( 2 * pi * L1 * ( fr^2 - fc^2 ) / (Hi1 * Ginv * fc) ) - atan(Ki/ (2 * pi * fc * Kp));
    GM = 20 * log10(Hi1 * Ginv/ (2 * pi * fc * L1));
    % Phase margin greater than 45 degree and Gain margin greater than 5 DB
    if (PM > 45 * pi / 180)   && ( GM > 3) && (T_fo > 52 ) && (Hi1 < 4 * V_tri * f_sw * L1 / V_dc)
        plot(fc, Hi1, 'ro');
    end
    end
end

hold off ;

Ig2 = 1.5 ;
T_fo = 20 * log10(Vg / ( 2 * pi * fo * (L1 + L2) * Ig2 ))
Hi1 = 0.1 ;
fc = 2000 ;

% PI parameter
Kp = 2 * pi * fc * (L1 + L2) / ( Hi2 * Ginv);
Ki = 4 * pi^2 * fo * (L1 + L2)/(Hi2 * Ginv) * sqrt((10^(T_fo/20) * fo )^2 - fc^2); 
Gi = tf([Kp, Ki], [1, 0]); 
Gi_z = c2d(Gi, 1/f_sw); % 10kHz discrete control frequency.


%% Transfer function : from inverter voltage to grid current. ideal.
LCL = tf(1, [L1 * L2 * C, (L1 * r2 + L2 * r1) * C, (L1 + L2 + r1 * r2 * C), r1 + r2])
figure('name', 'LCL bode plot.');
bode(LCL);

%% Transfer function : from grid voltage to grid current. ideal.
Ug_LCL = - tf([L1 * C, r1 * C, 1], [L1 * L2 * C, (L1 * r2 + L2 * r1) * C, (L1 + L2 + r1 * r2 * C), r1 + r2])
figure('name', 'Ug_LCL');
bode(Ug_LCL);

%% Loop gain :
Hi1 = 0.0 ;
T = tf( Hi2 * Ginv, [ L1 * L2 * C, L2 * C * Hi1 * Ginv, L1 + L2, 0 ]) * Gi ;
figure('name', 'Loop Gain and Phase');
bode(T);
hold on ;

Hi1 = 0.12 ;
T_damp1 = tf( Hi2 * Ginv, [ L1 * L2 * C, L2 * C * Hi1 * Ginv, L1 + L2, 0 ]) * Gi ;
Hi1 = 0.06 ;
T_damp2 = tf( Hi2 * Ginv, [ L1 * L2 * C, L2 * C * Hi1 * Ginv, L1 + L2, 0 ]) * Gi ;

bode(T_damp1, 'r');
hold on ;
bode(T_damp2, 'g')
hold off ;



