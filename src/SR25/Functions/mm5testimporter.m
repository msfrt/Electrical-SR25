% Load CSV
data = readtable('mm5test4.csv');

% Convert to numeric arrays
time = data.xtime_s_;  % [s]
ax = data.MM5_ax_g_;   % [g]
ay = data.MM5_ay_g_;
az = data.MM5_az_g_;
rollRate = data.MM5_rollRate___s_;   % [deg/s]
yawRate  = data.MM5_yawRate___s_;    % [deg/s]

imu_input = timeseries([ax ay az rollRate yawRate], time);