#ifndef _PSO_H_
#define _PSO_H_

class Particle
{
protected:
    int n;          //维数
    //TODO:试试用智能指针写
    double *x;      //粒子位置
    double *v;      //粒子速度
    double *bestx;  //记录最优一次位置
    double bestvalue;    //记录最优值
    double xmin;
    double xmax;
    double vmax;
    double vmin;
public:
    Particle(int size, double min, double max);//size为维数
    ~Particle();
    void print();
    void move();            //粒子移动
    double UpdateValue();   //更新粒子值
};

// class _PSO_H_
// {
// protected:
    
// public:

// };

#endif
