function [percenterror W_1 W_2] = ANNRun(N_hidden,learningrate,iter)

load 'assign3v6.mat';
N_hidden = 12;
learningrate =0.0015;
iter = 300;

%Randomizing and normalizing weights between inputs and hidden neurons, 
%as well as weights between hidden neurons and outputs
rand('twister',5489)

W_1 = 0.01*rand(size(traindata,2)+1,N_hidden); 
W_2 = 0.01*rand(N_hidden+1,size(traintargets,2));

%number of iterations set to 300
for x=1:iter,
[neg_loglike(x),output_y, dE_dw1, dE_dw2] = function_e(traindata, traintargets, size(W_1,2), W_1, W_2);
W_1 = W_1 - learningrate*dE_dw1;
W_2 = W_2 - learningrate*dE_dw2;
end

%calculates error based on new weights
[percenterror] = PercentClassify(testdata, testtargets,N_hidden,W_1, W_2)*100;
