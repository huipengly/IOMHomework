clear;clc;

test = zeros(1,10000) * NaN;
count = 1;

n = 1000;%������
T0 = 600;
Tf = 60;
deltaT = 2;
nTk = 3;
order = randperm(n);%����һ��1-n���������
load('time.mat');
%time = ones(n,n);
%time = randi(10,n);%�������һ��1-10֮���n*n���󣬴�����ʱ�䡣

ordernum = order + (0:n:(n-1)*n);
orderM = zeros(n,n);
orderM(ordernum) = 1;%������һ��������0-1����

AllTime = sum(sum(time .* orderM));%������ʱ��

BestOrder = order;
BestTime = AllTime;

for Tk=T0:-deltaT:Tf
    for j=1:3
        %�����������2��,�����µľ���
        ran1 = randi(n,1);
        ran2 = randi(n,1);
        temp = order(1,ran1);
        neworder = order;
        neworder(1,ran1) = order(1,ran2);
        neworder(1,ran2) = temp;
        ordernum = neworder + (0:n:(n-1)*n);
        orderM = zeros(n,n);
        orderM(ordernum) = 1;%������һ��������0-1����
        NewAllTime = sum(sum(time .* orderM));%������ʱ��
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
                if AllTime < BestTime %��¼���Ž�
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