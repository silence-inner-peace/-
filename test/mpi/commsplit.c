// this example is extended from http://mpitutorial.com/tutorials/introduction-to-groups-and-communicators/

#include "mpi.h"
#include <stdio.h>
int main( int argc, char **argv )
{
    MPI_Init( &argc, &argv );
	// Get the rank and size in the original communicator
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int color = rank %2; // Determine color based on row

	// Split the communicator based on the color and use the
	// original rank for ordering
	MPI_Comm row_comm;
	MPI_Comm_split(MPI_COMM_WORLD, color, rank, &row_comm);

	int row_rank, row_size;
	MPI_Comm_rank(row_comm, &row_rank);
	MPI_Comm_size(row_comm, &row_size);

	printf("WORLD RANK/SIZE: %d/%d \t ROW RANK/SIZE: %d/%d\n",
			rank, size, row_rank, row_size);

	MPI_Comm_free(&row_comm);
	
	MPI_Finalize();
}
