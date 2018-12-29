#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// compile:
// gcc -fopenmp -Wall -o helloopenmp helloworld.c
//
int main(int argc, char** argv) {
  int n = atoi(argv[1]);
  omp_set_num_threads(n);
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    int num = omp_get_num_threads();
    printf("%d/%d says hello!%d\n", id, num, n);
  }
}
