%This script enables MATLAB enumerations to interact with the Raptor 
%calibration interface

function RaptorEnum = enum2Raptor(enum)
    [m,s] = enumeration(enum);
    datatype = 'int32';
    nums = cast(m,datatype);
    % RaptorEnum = struct('Name',s,'Value',num2cell(nums));
    RaptorEnum = struct('Name',transpose(s),'Value',transpose(nums));
    % RaptorEnum = struct('Name',s,'Value',nums);
end

% struct('Name', {'No Error', 'Out of Range High', 'Out of Range Low', 'Plausibility Error'}, 'Value', [-1, 10, 11, 12])