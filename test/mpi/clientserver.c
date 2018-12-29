/** sendrecv.cc: basic send-receive program to illustrate point2point comm
 * and deadlock situations
 * Only works if np > 0 and np is an even number
 * Author: Yan Y. Liu <yanliu@illinois.edu>
 * Date: 06/18/2014
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	//fprintf(stdout, "I'm number %d of %d MPI processes\n", rank, size);
	//fflush(stdout);

	int buf[4];
	memset(buf, 0, sizeof(int) * 4);
	int i, v;
	MPI_Status status;
	// send to all
	if (rank > 0) { // sender is non-root
		v = rank * rank;
		MPI_Send(&v, 1, MPI_INT, 0, 900+rank, MPI_COMM_WORLD);
		fprintf(stdout, "Proc %d sent %d w/ tag %d\n", rank, v, 900+rank);
		fflush(stdout);
	} else {
		int source, tag;
		for (i=1; i<size; i++) {
			MPI_Recv(buf+i, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			source = status.MPI_SOURCE;
			tag = status.MPI_TAG;
			fprintf(stdout, "Proc %d got %d from p%d w/ tag %d\n", rank, buf[i], source, tag);
			fflush(stdout);
		}
	}
		
	MPI_Finalize();
}
