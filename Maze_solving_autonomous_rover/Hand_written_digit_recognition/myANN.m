load 'file'

N_hidden = 12;
learningrate = 0.0015;
iter = 300;

A = imread('image.jpg');
row =
col = 
A = A(row,col,:);
imshow(A);
A = rgb2gray(A);
A = resize(A, [16 16]);
A = double(abs(A-255)/255);
A = A';
A = reshape(A, [1 256]);

[percenterror W_1 W_2] = ANNRun(N_hidden,learningrate,iter);

[neg_loglike,output_y] = function_e(A, traintargets(1,:), N_hidden, W_1, W_2)

output_y