/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ASM_TOPOLOGY_H
#define __ASM_TOPOLOGY_H

#include <linux/cpumask.h>

struct cpu_topology {
	int thread_id;
	int core_id;
	int cluster_id;
	int package_id;
	int llc_id;
	cpumask_t thread_sibling;
	cpumask_t core_sibling;
	cpumask_t core_possible_sibling;
	cpumask_t llc_sibling;
};

extern struct cpu_topology cpu_topology[NR_CPUS];

#define topology_physical_package_id(cpu)	(cpu_topology[cpu].package_id)
#define topology_cluster_id(cpu)	(cpu_topology[cpu].cluster_id)
#define topology_core_id(cpu)		(cpu_topology[cpu].core_id)
#define topology_core_cpumask(cpu)	(&cpu_topology[cpu].core_sibling)
#define topology_sibling_cpumask(cpu)	(&cpu_topology[cpu].thread_sibling)
#define topology_llc_cpumask(cpu)	(&cpu_topology[cpu].llc_sibling)
#define topology_possible_sibling_cpumask(cpu)		\
				(&cpu_topology[cpu].core_possible_sibling)

void init_cpu_topology(void);
void store_cpu_topology(unsigned int cpuid);
void remove_cpu_topology(unsigned int cpuid);
const struct cpumask *cpu_coregroup_mask(int cpu);

#ifdef CONFIG_NUMA

struct pci_bus;
int pcibus_to_node(struct pci_bus *bus);
#define cpumask_of_pcibus(bus)	(pcibus_to_node(bus) == -1 ?		\
				 cpu_all_mask :				\
				 cpumask_of_node(pcibus_to_node(bus)))

#endif /* CONFIG_NUMA */

#include <linux/arch_topology.h>

/* Replace task scheduler's default frequency-invariant accounting */
#define arch_scale_freq_capacity topology_get_freq_scale

/* Replace task scheduler's default max-frequency-invariant accounting */
#define arch_scale_max_freq_capacity topology_get_max_freq_scale

/* Replace task scheduler's default min-frequency-invariant accounting */
#define arch_scale_min_freq_capacity topology_get_min_freq_scale

/* Replace task scheduler's default cpu-invariant accounting */
#define arch_scale_cpu_capacity topology_get_cpu_scale

/* Enable topology flag updates */
#define arch_update_cpu_topology topology_update_cpu_topology

/* Replace task scheduler's default thermal pressure retrieve API */
#define arch_scale_thermal_pressure topology_get_thermal_pressure

#include <asm-generic/topology.h>

#endif /* _ASM_ARM_TOPOLOGY_H */
