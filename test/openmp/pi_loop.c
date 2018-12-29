#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static long num_steps = 100000000;
double step;
int main (int argc, char ** argv)
{
  int n = atoi(argv[1]); 
  int n2; // actuall num of threads allocated
  int i; double x, pi, sum=10.0;
  omp_set_num_threads(n);
  step = 1.0/(double) num_steps;
  double t = omp_get_wtime();
  #pragma omp parallel
  {
    int i, id, num;
    id = omp_get_thread_num();
    num = omp_get_num_threads();
    if (id == 0) n2 = num;
    double x;
    #pragma omp for reduction(+:sum)
    for (i=0;i< num_steps; i++){
      x = (i+0.5)*step;
      sum += 4.0/(1.0+x*x);
    }
  }
  pi += sum * step;
  t = omp_get_wtime() - t;
  printf("pi=%.10lf after %ld steps in %.3lf seconds\n", pi, num_steps, t);
}
