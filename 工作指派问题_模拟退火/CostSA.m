function [cost,order,count] = CostSA(costMat)
n = size(costMat,1);
order = randperm(n);%����һ��1-n���������
cost = 0;
count = 1;
T0 = 60 + 10*n^2;
Tf = 60;
deltaT = 2;
nTk = 3 + 1;
ordernum = order + (0:n:(n-1)*n);
ordernum = ordernum';
orderM = zeros(n,n);
orderM(ordernum) = 1;%������һ��������0-1����
AllTime = sum(sum(costMat .* orderM));%������ʱ��

BestOrder = order;
BestTime = AllTime;

for Tk=T0:-deltaT:Tf
    for j=1:nTk
        %�����������2��,�����µľ���
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
        orderM(ordernum) = 1;%������һ��������0-1����
        NewAllTime = sum(sum(costMat .* orderM));%������ʱ��
        deltaf = NewAllTime - AllTime;
        if deltaf < 0    %ʱ�����������ת��,����¼���š�
            order = neworder;
            AllTime = NewAllTime;
            if AllTime < BestTime %��¼���Ž�
                BestOrder = order;
                BestTime = AllTime;
            end
        else
            zeta = rand;
            if exp(-deltaf/Tk) > zeta %������ת��
                order = neworder;
                AllTime = NewAllTime;
            end
        end
        count = count + 1;
    end
end

cost = BestTime;
order = BestOrder;