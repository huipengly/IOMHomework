#include <rand>

double TotalScore;
double *aa;
aa = new double[size];
double score[];

//构造轮盘
for (int i = 0; i < size; i++)
{
	if (i == 0)
	{
		aa[i] = score[i] / TotalScore;
	}
	else
	{
		aa[i] = score[i] / TotalScore + aa[i - 1];
	}
}

//产生
srand(time(0));
double rand[2];
rand[0] = rand();
rand[1] = rand();//TODO:验证两个rand一样不
int parent[2];
for (int i = 0; i < 2; i++)
{
	for (int j = 0; j < size; j++)
	{
		if (j == 0)
		{
			if (rand[j] < aa[j])
			{
				parent[i] = j;
				break;
			}
		}
		else
		{
			if ((rand[j] < aa[i]) && (rand[j] > aa[i - 1]))
			{
				parent[i] = j;
				break;
			}
		}
	}
}