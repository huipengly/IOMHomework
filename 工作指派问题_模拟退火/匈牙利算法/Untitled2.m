n=4;
order = randperm(n);%生成一个1-n的随机排列
ordernum1 = order + (0:n:(n-1)*n);
orderM1 = zeros(n,n);
orderM1(ordernum1') = 1;%生成了一个工作的0-1矩阵。