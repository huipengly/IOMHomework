%order = a;
ordernum = BestOrder + (0:n:(n-1)*n);
orderM = zeros(n,n);
orderM(ordernum) = 1;%生成了一个工作的0-1矩阵。

AllTime = sum(sum(time .* orderM));%工作总时间