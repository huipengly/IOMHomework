n=4;
order = randperm(n);%����һ��1-n���������
ordernum1 = order + (0:n:(n-1)*n);
orderM1 = zeros(n,n);
orderM1(ordernum1') = 1;%������һ��������0-1����