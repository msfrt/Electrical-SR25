%This script enables MATLAB enumerations to interact with the Raptor 
%calibration interface

function RaptorEnum = enum2Raptor(enum)
[m,s] = enumeration(enum);
datatype = 'int16';
nums = cast(m,datatype);
% RaptorEnum = struct('Name',s,'Value',num2cell(nums));
RaptorEnum = struct('Name',s,'Value',nums);
end