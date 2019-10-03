[percenterror W_1 W_2] = ANNRun(12, 0.0015,1000);
%load downloaded jpg/jpeg picture
%load 'assign3v6.mat'

% a = img;
% a = uint8(a);
% a = rgb2gray(a(:,:,:));
% 
% a = 255-a;
% flag = 0;
% num = 130;
% for m = 1: size(a,1)
%     for n = 1 : size(a,2)
%         if a(m,n)>=num
%             a(m,n) = 255;
%         end
%         if a(m,n)<num
%             a(m,n) = 0;
%         end
%         
%     end
% end
% for i = 1:size(a,1)
%     for j = 1:size(a,2)
%         if a(i,j)>num
%             flag = 1;
%             break
%         end
%     end
%     if flag == 1,
%         break;
%     end
% end
% i1 = i;
% 
% %bottom
% flag = 0;
% for i = size(a,1):-1:1,
%     for j = 1:size(a,2)
%         if a(i,j)>num,
%             flag = 1;
%             break
%         end
%     end
%     if flag == 1,
%         break;
%     end
% end
% i2 = i;
% %left
% flag = 0;
% for j = 1:size(a,2)
%     for i = 1:size(a,1),
% 
%         if a(i,j)>num,
%             flag = 1;
%             break
%         end
%     end
%     if flag == 1,
%         break;
%     end
% end
% j1 = j;
% flag = 0;
% for j = size(a,2):-1:1
%     for i = 1:size(a,1),
% 
%         if a(i,j)>num,
%             flag = 1;
%             break
%         end
%     end
%     if flag == 1,
%         break;
%     end
% end
% j2 = j;
% a = a(i1:i2,j1:j2);
% min_size = size(a);
% if min_size(1) > min_size(2)
%     a = a(1:min_size(2),1:min_size(2));
% end
% if min_size(2) > min_size(1)
%     a = a(1:min_size(1),1:min_size(1));
% end
% 
% a = imresize(a,[16 16]);
% 
% 
% 
% 
% l = a;


imshow(img);
h = imrect;
position = wait(h);
croppedImage = imcrop(img, position);
figure;
imshow(croppedImage);

grayimg=rgb2gray(croppedImage);
imshow(grayimg);

[m,n]=size(grayimg);
inputy=zeros(m,n);
for i=1:m
  for j=1:n
     if(grayimg(i,j)>140)
       inputy(i,j)=0;
     else
       inputy(i,j)=1;
      end
    end
end
imshow(inputy);


resizedimage = imresize(inputy, [16 16]);

[m,n]=size(resizedimage);
inputz=zeros(m,n);
for i=1:m
  for j=1:n
     if(abs(resizedimage(i,j))<0.05)
       inputz(i,j)=0;
     else
       inputz(i,j)=1;
      end
    end
end



a =[1 2 3 4 5 6 7 8 9 0];
b =y_final;
bar(a,b);


a=inputz;
a = a';
imshow(a);
%a = double(a)/255;
a = a(:);
a = a';

a = [1 a];


%load digits from data set

%a = testdata(2000,:);

h = a*W_1;
h_sig = 1./(1+exp(-h));
h_sig = [1 h_sig];

y = h_sig*W_2;
o_exp = exp(y);
y_final = o_exp/sum(o_exp);

sum(y_final);

[a b] = max(y_final)
a =[1 2 3 4 5 6 7 8 9 0];
b =y_final;
bar(a,b);
