#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;
//返回函数值，因为调用次数很多，这里写成inline提高效率
inline double f(double x) {
	return 4/(1+x*x);
}
 
int main(int argc, char *argv[]) 
{
	double pi, h, sum, x, startime, endtime;
	int size, myid;
	long long n;
	int i;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
 
	n=0;
	if(0 == myid) 
	{
		cout << "Please enter n" << endl;
		cin >> n;
		startime = MPI_Wtime();
	}
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);  //将n广播到所有进程中
	h = 1.0/(double)n;							   //每个矩形块的宽
	sum = 0.0;        
	for(i=myid+1; i<=n; i+=size) {             //4个进程
		x = h*((double)i - 0.5);                   //进程0:1,5,9,...  进程1:2,6,10,...
		sum = sum + f(x);                          //进程2:3,7,11,... 进程3:4,8,12,...
	}          
	sum = sum * h;								   //每个进程计算的矩形面积之和
	MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);  

	//利用归约操作(MPI_SUM)将所有进程的sum累加到root进程(0)的sum当中得到结果
	if(myid == 0) 
	{
		endtime = MPI_Wtime();
		printf("用时:%f\n", endtime-startime);
		printf("%0.15f\n", pi);
	}
	MPI_Finalize();
}
