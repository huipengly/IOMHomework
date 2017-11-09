#ifndef _PSO_H_
#define _PSO_H_

class Particle
{
protected:
    int d;          //维数
    //TODO:试试用智能指针写
    double *x;      //粒子位置
    double *v;      //粒子速度
    double *bestx;  //记录最优一次位置
    double value;
    double bestvalue;    //记录最优值
    double xmin;
    double xmax;
    double vmax;
    double vmin;
    double c1;
    double c2;
    double omega;
public:
    Particle();
    ~Particle();
    void print();
    void init(int dsize, double min, double max);//初始化粒子，dsize是维数
    void move();            //粒子移动
    double UpdateValue();   //更新粒子值
    void UpdateSpeed(double *bestpx);
    double *getx();
};

class PSO
{
protected:
    int n;          //粒子数
    Particle *p;    //粒子群
    double *bestpx; //最优粒子
    double bestpvalue;
    int gen;

    int dsize;      //粒子维数
    int min;        //粒子最小、最大取值范围
    int max;

public:
    PSO(int nsize, int dsize, int min, int max, int gen);
    ~PSO();
    void print(int i);
    void findbest();
    void SwarmMove();
    void SwarmUpdateSpeed();
    void run();

};

#endif
