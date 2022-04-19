%Matlab script utilizing convex optimization techniques to optimize a
%resistor value in a built circuit for optimal sensing range and error. 
%Takes data from a field test (data04.csv) and re optimizes the tuning
%resistor value (from a I2C controlled potentiometer) to fit a more desired
%range of data. This circuit utilizes a 16-bit ADC to gather the signal
%data, many of the values here constrain to a range of a 5V 16 bit
%represented signal to a 3.3V representation (true system voltage)


clear 
clc

Raw = readtable('data04.csv');
Raw_Data = Raw.ADS1115;

n = length(Raw_Data);


EC = 100;  %Targeted Electrical Conductivity Reading
tuning = 10000; %Tuning variable

intercept = 2538; %Sensor reading when DI water is present (no EC)

leniency_constraint = 200; %How lenient can the data be in error


%Setup up variables and matrices for optimization
Int_V = ones(n,1)*intercept;
tuning_vector = ones(n,1)*tuning;

RD = diag(Raw_Data);
Resistor = ones(n,1);

%Utilize the cvx library for optimization algorithms
%This optimization is based on the MSE algorithm, using the 2-norm to
%simulate the euclidean distance between the graphed out sensor values from
%a trial field run (data04.csv) and the wanted range of values.
cvx_begin
    variable Resistor(n)
    variable leniency
    minimize ( power (2,norm(RD*Resistor - (tuning_vector),2) ) + power(2,norm(leniency,2)))
    subject to
        (RD*Resistor - tuning_vector) == 0
        sum(Resistor)/n*max(Raw_Data) <= tuning+leniency
        sum(Resistor)/n*min(Raw_Data) >= tuning-leniency
        leniency_constraint >= leniency >= 0

cvx_end

%Reconstructing Model and Data with the fixed Resistor
m = round(length(Raw_Data)/2);

base_resistors = ((Raw_Data-intercept).*100000)./(128*4.3*power(EC,0.5743));
used_resistor = sum(base_resistors)/length(base_resistors);



SXR = (Raw_Data - 2538)./(4.3*power(EC,0.5743));

new_resistors = used_resistor*Resistor;
median_resistors = used_resistor*ones(length(Resistor),1)*sum(Resistor)/length(Resistor);

fixed_data_calculated = 4.3*power(EC,0.5743)*((new_resistors*128)/100000) + intercept;

fixed_median_calc = 4.3*power(EC,0.5743)*((median_resistors*128)/100000) + intercept;

figure(1)
plot(Raw_Data);
hold on
plot(fixed_data_calculated);
plot(fixed_median_calc);
hold off
legend('Raw Data', 'Fixed Data', 'Median');
title('Optimized Resistors');

