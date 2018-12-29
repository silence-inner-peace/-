#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv) {
	double pi;
	int np;
	int num_steps = 10000;
	int nthreads;
	if(argc>2)
	{
		num_steps = atoi(argv[1]);
		np = atoi(argv[2]);
	}
	double step = 1.0/(double) num_steps;

	omp_set_num_threads(np);
  	double t = omp_get_wtime();

	#pragma omp parallel
	{
		nthreads=omp_get_num_threads();
		int i,id;
		double x,sum;
		id=omp_get_thread_num();
		for(i=id,sum=0.0;i<num_steps;i+=nthreads)
		{
			x=(i+0.5)*step;
			sum+=4.0/(1.0+x*x);
		}
		#pragma omp critical
		{
			pi+=sum*step;
		}
	}
 	t = omp_get_wtime() - t;
	
	printf("pi=%lf after %lf second\n", pi,t);	
}
