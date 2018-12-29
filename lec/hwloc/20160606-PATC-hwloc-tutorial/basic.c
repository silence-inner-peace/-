#include <hwloc.h>

int main(int argc, char *argv[])
{
  hwloc_topology_t topo;
  int err;

  /* initialize a topology context */
  err = hwloc_topology_init(&topo);
  assert(!err);

  /* insert optional topology configuration here */

  /* build the topology created and configured above */
  err = hwloc_topology_load(topo);

  /* play with the topology here */

  /* terminate this topology context */
  hwloc_topology_destroy(topo);

  return 0;
}
