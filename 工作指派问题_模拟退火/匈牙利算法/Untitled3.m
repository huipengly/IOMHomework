%order = a;
ordernum = BestOrder + (0:n:(n-1)*n);
orderM = zeros(n,n);
orderM(ordernum) = 1;%������һ��������0-1����

AllTime = sum(sum(time .* orderM));%������ʱ��