#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

static long num_steps = 100000000;
int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Status status;
  double step= 1.0/(double) num_steps;
  double pi;
  double sum=0.0;
  int i;
  double x,part_sum=0.0;
  int part_num,part_startIdx;
  int *startIdx=(int*)malloc(sizeof(int)*size);
  int *num=(int*)malloc(sizeof(int)*size);
  if (rank == 0) 
  { // sender is root
    num[0]=0;
    startIdx[0]=0;
    for(i=1;i<size;i++)
    {
      if(i<=num_steps%(size-1))
      {
        num[i]=num_steps/(size-1)+1;
      }
      else
      {
        num[i]=num_steps/(size-1);
      }
    }
    for(i=1;i<size;i++)
    {
      startIdx[i]=startIdx[i-1]+num[i-1];
    }

    for (i=1; i<size; i++) 
    {
      MPI_Send(startIdx+i,1,MPI_INT,i,1,MPI_COMM_WORLD);
      MPI_Send(num+i,1,MPI_INT,i,2,MPI_COMM_WORLD);
    }
    //MPI_Recv(&pi,1,MPI_INT,MPI_ANY_SOURCE,3,MPI_COMM_WORLD,&status);

  } 
  else 
  {
    MPI_Recv(&part_startIdx,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
    MPI_Recv(&part_num,1,MPI_INT,0,2,MPI_COMM_WORLD,&status);
    for(i=0;i<part_num;i++,part_startIdx++)
    {
      x = (part_startIdx+0.5)*step;
      part_sum+= 4.0/(1.0+x*x);
    }
    part_sum=part_sum*step;
    printf("part_sum %.16f\n",part_sum);
    MPI_Send(&part_sum,1,MPI_DOUBLE,0,3,MPI_COMM_WORLD);

  }
  MPI_Reduce(&part_sum,&sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
  if(rank==0)
  {
    printf("pi %.16f\n",sum);
  }
  MPI_Finalize();
}
