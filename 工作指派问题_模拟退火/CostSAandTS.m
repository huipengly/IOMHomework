function [cost,order,count] = CostSAandTS(costMat)
n = size(costMat,1);
order = randperm(n);%生成一个1-n的随机排列
cost = 0;
count = 1;
T0 = 60 + 10*n;
Tf = 60;
deltaT = 2;
nTk = 3 + 1;
ordernum = order + (0:n:(n-1)*n);
ordernum = ordernum';
orderM = zeros(n,n);
orderM(ordernum) = 1;%生成了一个工作的0-1矩阵。
AllTime = sum(sum(costMat .* orderM));%工作总时间

tabutable = zeros(n,n);
randA = zeros(10,n);

BestOrder = order;
BestTime = AllTime;

for Tk=T0:-deltaT:Tf
    for j=1:nTk
        %随机交换其中2个,生成新的矩阵
        for i=1:10
            randA(i,:) = randperm(n);
        end
        NewAllTime = n*n;
        NewOrder = zeros(1,n).*NaN;
        for i=1:10
            ran1 = randA(i,1);
            ran2 = randA(i,2);
            if tabutable(max(ran1,ran2),min(ran1,ran2))==1%判断是否在禁忌表
                i=i+1;
                break;
            end
            neworder = order;
            temp = neworder(1,ran1);
            neworder(1,ran1) = neworder(1,ran2);
            neworder(1,ran2) = temp;
            ordernum = neworder + (0:n:(n-1)*n);
            ordernum = ordernum';
            orderM = zeros(n,n);
            orderM(ordernum) = 1;%生成了一个工作的0-1矩阵。
            tubeTime = sum(sum(costMat .* orderM));%工作总时间
            if tubeTime < NewAllTime
                NewAllTime = tubeTime;
                NewOrder = neworder;
            end
        end
        deltaf = NewAllTime - AllTime;
        if deltaf < 0    %时间更短无条件转移,并记录最优。
            order = neworder;
            AllTime = NewAllTime;
            if AllTime < BestTime %记录最优解
                BestOrder = order;
                BestTime = AllTime;
            end
            
            %加入禁忌表
            [x,y]=find(tabutable==10);
            tabutable(x,y) = 0;tabutable(y,x)=0;
            for i=1:9
                tabutable(x,y) = tabutable(x,y) + 1;
            end
            tabutable(max(ran1,ran2),min(ran1,ran2)) = 1;
            tabutable(min(ran1,ran2),max(ran1,ran2)) = 1;
            
        else
            zeta = rand;
            if exp(-deltaf/Tk) > zeta %有条件转移
                order = neworder;
                AllTime = NewAllTime;
            end
            
            
            %加入禁忌表
            [x,y]=find(tabutable==10);
            tabutable(x,y) = 0;tabutable(y,x)=0;
            for i=1:9
                tabutable(x,y) = tabutable(x,y) + 1;
            end
            tabutable(max(ran1,ran2),min(ran1,ran2)) = 1;
            tabutable(min(ran1,ran2),max(ran1,ran2)) = 1;
            
        end
        count = count + 1;
    end
end

cost = BestTime;
order = BestOrder;