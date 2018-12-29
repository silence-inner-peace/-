#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int num_steps = 10000;
int np;
double step;
double pi;
int main(int argc, char** argv) {
	if(argc>2)
	{
		num_steps = atoi(argv[1]);
		np = atoi(argv[2]);
	}
	omp_set_num_threads(np);
	double *sum=(double*)malloc(np*sizeof(double));
	step = 1.0/(double) num_steps;
	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		int i;
		double x;
		sum[id]=0.0;
		for(i=id;i<num_steps;i+=np)
		{
	    	x = (i+0.5)*step;
	    	sum[id] = sum[id] + 4.0/(1.0+x*x);
		}
	}
	double dsum=0;
	int j;
	for(j=0;j<np;j++)
	{
		dsum+=sum[j];
	}
	pi=step*dsum;
	printf("pi=%lf \n", pi);


}
