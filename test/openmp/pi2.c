#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static long num_steps = 100000000;
double step;
int main (int argc, char ** argv)
{
  int n = atoi(argv[1]); 
  int n2; // actuall num of threads allocated
  int i; double x, pi;
  double *sum = (double *)malloc(sizeof(double)*n);
  omp_set_num_threads(n);
  step = 1.0/(double) num_steps;
  double t = omp_get_wtime();
  #pragma omp parallel
  {
    int i, id, num;
    double x;
    id = omp_get_thread_num();
    num = omp_get_num_threads();
    if (id == 0) n2 = num;
    for (i=id, sum[id]=0.0;i< num_steps; i+=num){
      x = (i+0.5)*step;
      sum[id] += 4.0/(1.0+x*x);
    }
  }
  for (i=0, pi=0; i<n2; i++) pi += sum[i] * step;
  free(sum);
  t = omp_get_wtime() - t;
  printf("pi=%.10lf after %ld steps in %.3lf seconds\n", pi, num_steps, t);
}
