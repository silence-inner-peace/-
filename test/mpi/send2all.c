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
	int i;
	MPI_Status status;
	// send to all
	if (rank == 0) { // sender is root
		for (i=0; i<4; i++)
			buf[i] = i*i;
		for (i=0; i<size; i++) {
			MPI_Send(buf+i, 1, MPI_INT, i, 999, MPI_COMM_WORLD);
		}
		fprintf(stdout, "Proc %d sent: ", rank);
		for (i=0; i<4; i++)
			fprintf(stdout, "%d ", buf[i]);
		fprintf(stdout, "\n");
		fflush(stdout);
	} else {
		MPI_Recv(buf, 1, MPI_INT, 0, 999, MPI_COMM_WORLD, &status);
		fprintf(stdout, "Proc %d got %d\n", rank, buf[0]);
		fflush(stdout);
	}
		
	MPI_Finalize();
}
