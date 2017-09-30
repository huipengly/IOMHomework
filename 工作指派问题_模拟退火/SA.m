clear;clc;

test = zeros(1,10000) * NaN;
count = 1;

n = 1000;%工人数
T0 = 600;
Tf = 60;
deltaT = 2;
nTk = 3;
order = randperm(n);%生成一个1-n的随机排列
load('time.mat');
%time = ones(n,n);
%time = randi(10,n);%随机生成一个1-10之间的n*n矩阵，代表工作时间。

ordernum = order + (0:n:(n-1)*n);
orderM = zeros(n,n);
orderM(ordernum) = 1;%生成了一个工作的0-1矩阵。

AllTime = sum(sum(time .* orderM));%工作总时间

BestOrder = order;
BestTime = AllTime;

for Tk=T0:-deltaT:Tf
    for j=1:3
        %随机交换其中2个,生成新的矩阵
        ran1 = randi(n,1);
        ran2 = randi(n,1);
        temp = order(1,ran1);
        neworder = order;
        neworder(1,ran1) = order(1,ran2);
        neworder(1,ran2) = temp;
        ordernum = neworder + (0:n:(n-1)*n);
        orderM = zeros(n,n);
        orderM(ordernum) = 1;%生成了一个工作的0-1矩阵。
        NewAllTime = sum(sum(time .* orderM));%工作总时间
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
                if AllTime < BestTime %记录最优解
                    BestOrder = order;
                    BestTime = AllTime;
                end
            end
        end
        test(1,count) = AllTime;
        count = count + 1;
    end
end
BestTime