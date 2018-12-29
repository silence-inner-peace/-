#include <stdio.h>
#include <stdlib.h>

extern double getpi(int numsteps);

int main(int argc, char **argv) 
{
	int nsteps=atoi(argv[1]);
	double pi=getpi(nsteps); 
	printf("pi=%lf\n", pi);
}
