% test.m
% (c) Alexis Rigaud, 2024
% test script for matlab / c comparison

disp("** test eigen values **");

A = gallery("lehmer", 50);
% TODO : look for another example matrix, more general

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


disp("** test matrix mult. **");

%A = rand(2, 3);
%B = rand(3, 4);

A = [1.0, 2.0 ; 3.0, 4.0 ; 5.0, 6.0]
B = [1.0, 1.0, 1.0 ; 0.0 , 1.0, 1.0]


tic
D = A*B
toc
size(D)
disp('mtimes() done')

tic
U = cmtimes(A,B)
toc
size(U)
disp('cmtimes() done')


