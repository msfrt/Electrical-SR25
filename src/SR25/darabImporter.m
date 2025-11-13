% Load CSV
data = readtable('pow.csv');

% Convert to numeric arrays
time = data.xtime_s_;  % [s]
rpm = data.PM_motorSpeed_rpm_;
t = data.PM_torqueFeedback_Nm_;

imu_input = timeseries([rpm, t], time);