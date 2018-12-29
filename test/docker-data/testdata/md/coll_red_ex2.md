# Reductions - exercise 2

In the last exercise we have been computing a reduction on one process. In this one, we will use the `MPI_Allreduce` operator to compute a reduction on all processes and use the given result.

Consider the following problem. We have a list of $`N`$ points in three dimensions (so with three coordinates). We want to compute the distance of each point to the barycentre of the set. For this, we will use $`M`$ processes in parallel having $`\frac{N}{M}`$ points each. The algorithm will have to proceed in four steps :

* Each process will compute the sum of all of its own points (sum avery coordinate 
* The program will then call the reduction to get the sum of all the points on all processes.
* Then, the barycentre position is given by dividing this sum by the number of points
* Finally, every process will compute the distance of each point to the barycentre, and print the result on stdout.

## `MPI_Allreduce`

As stated in the lesson, `MPI_Allreduce` computes a reduction just like `MPI_Reduce` but instead of storing the result on only one process, the result will be sent back to every process. The prototype is the following :

```cpp
int MPI_Allreduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
```

As you can see, the prototype is the same as for `MPI_Reduce` except we don't need to specify a root on which the result will be stored.

## Euclidian distance

The distance that you are asked to compute is the Euclidian distance. For those of you who don't remember this distance, here is the formula :

```math
D = \sqrt{(x-b_x)^2 + (y-b_y)^2 + (z-b_z)^2}
```

Where $`(x, y, z)`$ are the coordinates of the current point and $`(b_x, b_y, b_z)`$ are the coordinates of the barycentre.

You have all you need to do the exercise. Good luck.

@[Barycentre]({"stubs": ["coll_red_ex2/barycentre.cpp"], "command": "bash coll_red_ex2/barycentre.sh", "layout": "aside"})
