function [cost,order,count] = CostSA(costMat)
n = size(costMat,1);
order = randperm(n);%生成一个1-n的随机排列
cost = 0;
count = 1;
T0 = 60 + 10*n^2;
Tf = 60;
deltaT = 2;
nTk = 3 + 1;
ordernum = order + (0:n:(n-1)*n);
ordernum = ordernum';
orderM = zeros(n,n);
orderM(ordernum) = 1;%生成了一个工作的0-1矩阵。
AllTime = sum(sum(costMat .* orderM));%工作总时间

BestOrder = order;
BestTime = AllTime;

for Tk=T0:-deltaT:Tf
    for j=1:nTk
        %随机交换其中2个,生成新的矩阵
        randA = randperm(n);
        ran1 = randA(1);
        ran2 = randA(2);
        neworder = order;
        temp = neworder(1,ran1);
        neworder(1,ran1) = neworder(1,ran2);
        neworder(1,ran2) = temp;
        ordernum = neworder + (0:n:(n-1)*n);
        ordernum = ordernum';
        orderM = zeros(n,n);
        orderM(ordernum) = 1;%生成了一个工作的0-1矩阵。
        NewAllTime = sum(sum(costMat .* orderM));%工作总时间
        deltaf = NewAllTime - AllTime;
        if deltaf < 0    %时间更短无条件转移,并记录最优。
            order = neworder;
            AllTime = NewAllTime;
            if AllTime < BestTime %记录最优解
                BestOrder = order;
                BestTime = AllTime;
            end
        else
            zeta = rand;
            if exp(-deltaf/Tk) > zeta %有条件转移
                order = neworder;
                AllTime = NewAllTime;
            end
        end
        count = count + 1;
    end
end

cost = BestTime;
order = BestOrder;