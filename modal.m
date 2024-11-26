%% test GNU Octave / matlab
isoctave = @exist('OCTAVE_VERSION','builtin')~=0;

if isoctave
pkg load control
pkg load signal
pkg load optim
end

%% Compile/link C code

if ismac
    %setenv("LDFLAGS","-framework Accelerate")
    %clear ceig; mex  -I/opt/homebrew/Cellar/octave/9.2.0_1/include/octave-9.2.0/octave/ -L/opt/homebrew/Cellar/octave//9.2.0_1/lib/octave/9.2.0/  -IMex/linag -LMex/linalg -llinalg Mex/ceig.c
elseif isunix
    % TODO Code to run on Linux platform
else
    disp('Platform not supported')
end

%% TESTBED

A = gallery("lehmer",4);

tic
[W, D, Wt] = eig(A);
toc
sum(diag(D))
disp('eig done')

tic
[D] = ceig(A);
toc
sum(diag(D))
disp('ceig done')

if exist('TODO', 'var')

addpath('matlab/');

%% test on room impulse response
path = 'data/';

[ir,fs] = audioread([path,'Piano.mf.C1.aiff']);

% preprocessing
% convert to mono
if (size(ir,2)) > 1
    ir = ir(:,1);
end

% truncate signal
duration = 4.0;
start = round(0.5*fs); %to remove noisy transient and silence in beginning
finish = round(duration*fs);
ir = ir(start:finish);
f0 = 32.7;

% option
room_flag = false;
opt_flag = 1;

[mode_params, irhat] = frequency_warped_modal(ir, fs, f0, opt_flag, room_flag);

end