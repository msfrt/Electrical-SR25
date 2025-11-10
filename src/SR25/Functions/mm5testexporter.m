% Combine time and data into a table
imu_table = array2table([simout.Time simout.Data], ...
    'VariableNames', {'Time_s', 'Ax_g', 'Ay_g', 'Az_g', 'RollRate_deg_s', 'YawRate_deg_s'});

% Write the table to a CSV file
writetable(imu_table, 'imu_input.csv');