#include <stdio.h>
#include <assert.h>
#include <infiniband/verbs.h>
#include <hwloc.h>
#include <hwloc/openfabrics-verbs.h>
/* link with -lhwloc -libverbs */

int main(void)
{
  hwloc_topology_t topology;
  struct ibv_device **dev_list;
  hwloc_obj_t osdev;
  int i, count, err;

  hwloc_topology_init(&topology);
  hwloc_topology_set_flags(topology, HWLOC_TOPOLOGY_FLAG_IO_DEVICES);
  hwloc_topology_load(topology);

  dev_list = ibv_get_device_list(&count);
  if (!dev_list) {
    fprintf(stderr, "ibv_get_device_list failed\n");
    return 0;
  }
  printf("ibv_get_device_list found %d devices\n", count);

  /* first way: directly get the cpuset of the ibv_device,
   * and get the covering NUMA node.
   */
  for(i=0; i<count; i++) {

  }

  /* second-way: iterate over Open-Fabrices OS devices */
  osdev = NULL;
  while ((osdev = hwloc_get_next_osdev(topology, osdev)) != NULL) {

  }

  hwloc_topology_destroy(topology);

  return 0;
}
