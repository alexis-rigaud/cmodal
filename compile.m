% compile.m
% (c) Alexis Rigaud, 2024

%% test GNU Octave / matlab
isoctave = @exist('OCTAVE_VERSION','builtin')~=0;

if isoctave
    pkg load control
    pkg load signal
    pkg load optim
end

%% Compile/link C code

if ismac && isoctave % for macos+homebrew+octave dev.
    setenv("LDFLAGS",["-framework Accelerate"])
    setenv("LDFLAGS", [getenv("LDFLAGS") " -L/opt/homebrew/Cellar/octave/9.2.0_1/lib/octave/9.2.0/"])
    setenv("CFLAGS",  [getenv("CFLAGS")  " -I/opt/homebrew/Cellar/octave/9.2.0_1/include/octave-9.2.0/octave/"])
end

if isunix
    system("cd lib/linalg; rm -fr build; mkdir build; cd build; cmake ..; make");
    clear ceig;    mex -Ilib -Llib/linalg/build -llinalg src/ceig.c;
    clear cmtimes; mex -Ilib -Llib/linalg/build -llinalg src/cmtimes.c;
else
    disp('Platform not supported');
end


