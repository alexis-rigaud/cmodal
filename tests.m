% test.m
% (c) Alexis Rigaud, 2024
% test script for matlab / c comparison

disp("** test eigen values **");

A = gallery("lehmer", 50);

tic
[D] = eig(A);
toc
D
sum(D)
disp('eig() done')

tic
[DD] = ceig(A);
toc
DD
sum(DD)
disp('ceig() done')
