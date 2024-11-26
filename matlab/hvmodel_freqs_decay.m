function [fmhat, a1mhat, S, nm] = hvmodel_freqs_decay(ir, nh, p, fs, kappa)
%%
% Hankel-Vandermonde modal estimation
% Inputs:
% ir - impulse response
% nh - hankel matrix dimensions
% p - offset (in samples)
% fs - sampling frequency
% kappa - threshold (in dB) beyond which singular values are ignored.
% Outputs:
% fmhat - vector of estimated mode frequencies
% a1mhat - vector of estimated mode amplitudes
% S - singular value matrix (diagonal)
% nm - number of estimated modes
%%

if nargin < 5
    kappa = -80;
end


% form offset Hankel matricies
H = hankel(ir(1:nh), ir(nh+(0:nh-1)));
K = hankel(ir(p+(1:nh)), ir(p+nh+(0:nh-1)));

% generate Hankel matrix pseudoinverse

tic
%% octave+M1 : 51s
[U, S, Ut] = svd(H);
toc
disp('svd done')

nm = sum(diag(S) > 10^(kappa/20)*S(1,1));
Hinv = Ut(:,1:nm)*diag(1./diag(S(1:nm,1:nm)))*U(:,1:nm)';


% find offset Hankel matrix generalized eigenstructure
A = K*Hinv;
tic
%% octave+M1 : 5s
[W, D, Wt] = eig(A);
toc
sum(diag(D))
disp('eig done')


%tic
%[D] = ceig(A);
%toc
%sum(diag(D))
%disp('ceig done')

% compute mode parameters, impulse response
nmode = sum(abs(diag(D)) > 10^(kappa/20)*abs(D(1,1)));
[~,knee_point] = knee_pt(20*log10(diag(S)/S(1,1)));
nmode = min(knee_point, nmode);

lambda = diag(D(1:nmode,1:nmode));
[fmhat, order] = sort(angle(lambda)*fs/(2*pi*p));
a1mhat = abs(lambda(order)).^(1/p);

end

