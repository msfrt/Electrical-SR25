%This script runs when the model is opened.  It will add the model path
%and the support directories to the path.

%To create a data dictionary...
%myDictionaryObj = Simulink.data.dictionary.create('myNewDictionary.sldd')

if isempty(bdroot) || strcmp(bdroot, 'simulink'), return; end

% This adds the current directory to the MATLAB path,
% along with directories for Images, CAN, and Simulink libraries.
% Add to this list as your project grows.
mdlPath = fileparts(which(bdroot));
addpath(mdlPath);
addpath(genpath([mdlPath filesep 'CAN']));
addpath(genpath([mdlPath filesep 'Images']));
addpath(genpath([mdlPath filesep 'Libraries']));
addpath(genpath([mdlPath filesep 'Functions']));

clear mdlPath;

sl_refresh_customizations;
