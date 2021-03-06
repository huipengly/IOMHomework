%clc,clear;
n=5;
%time=randi(50,n);
[order_mu,cost_mu]=munkres(time);
cost_sa = zeros(1,100)*NaN;
tic
for i = 1:10
    [cost_sa(i),order_sa,count]=CostSAandTS(time);
end
toc
    cost_max = max(cost_sa);
    cost_min = min(cost_sa);
    cost_avg = mean(cost_sa(:));