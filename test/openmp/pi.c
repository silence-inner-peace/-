#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static long num_steps = 100000000;
double step;
int main ()
{ 
  int i; double x, pi, sum = 0.0;
  step = 1.0/(double) num_steps;
  double t = omp_get_wtime();
  for (i=0;i< num_steps; i++){
    x = (i+0.5)*step;
    sum = sum + 4.0/(1.0+x*x);
  }
  pi = step * sum;
  t = omp_get_wtime() - t;
  printf("pi=%.10lf after %ld steps in %.3lf seconds\n", pi, num_steps, t);
}
