#include <stdio.h>
#include <assert.h>
#include <cuda_runtime_api.h>
#include <hwloc.h>
#include <hwloc/cudart.h>
/* link with -lhwloc -lcuda */

int main(void)
{
  hwloc_topology_t topology;
  cudaError_t cerr;
  int count, i;
  int err;

  cerr = cudaGetDeviceCount(&count);
  if (cerr) {
    printf("cudaGetDeviceCount failed %d\n", cerr);
    return 0;
  }
  printf("cudaGetDeviceCount found %d devices\n", count);

  hwloc_topology_init(&topology);
  hwloc_topology_set_flags(topology, HWLOC_TOPOLOGY_FLAG_IO_DEVICES);
  hwloc_topology_load(topology);

  /* first way: directly get the cpuset of the i-th cuda device,
   * and get the covering NUMA node.
   */
  for(i=0; i<count; i++) {

  }

  /* second way: get the OS device of the i-th cude device,
   * walk up to find the NUMA node parent, and display its number
   */
  for(i=0; i<count; i++) {

  }

  hwloc_topology_destroy(topology);

  return 0;
}

