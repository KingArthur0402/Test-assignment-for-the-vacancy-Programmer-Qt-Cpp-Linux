#include "cpu_info.h"

#include <stdio.h>
#include <string.h>

int read_cpu(Cpu_info *Cpu, int *cpu_count) {
  int error = 0;
  FILE *f = NULL;
  f = fopen("/proc/stat", "r");
  if (!f) {
    error = 1;
  }
  int i = 0, exit_flag = 0, count = 0;
  while (!error && !exit_flag) {
    if (fscanf(f, "%7s %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu\n",
               (Cpu[i]).cpu_name, &((Cpu[i]).user), &((Cpu[i]).nice),
               &((Cpu[i]).system), &((Cpu[i]).idle), &((Cpu[i]).iowait),
               &((Cpu[i]).irq), &((Cpu[i]).softirq), &((Cpu[i]).steal),
               &((Cpu[i]).guest), &((Cpu[i]).guest_nice)) != 11) {
      error = 1;
    }
    if (strncmp((Cpu[i]).cpu_name, "cpu", 3)) {
      exit_flag = 1;
    }
    ++count;
    ++i;
  }
  count -= 2;
  if (!(*cpu_count))
    *cpu_count = count;
  else
    error = (*cpu_count != count);
  if (f) {
    fclose(f);
  }
  return error;
}

double calc_usage(Cpu_info const Cpu1, Cpu_info const Cpu2) {
  double delta_user = (Cpu2.user - Cpu1.user);
  double delta_nice = (Cpu2.nice - Cpu1.nice);
  double delta_system = (Cpu2.system - Cpu1.system);
  double delta_idle = (Cpu2.idle - Cpu1.idle);
  double delta_iowait = (Cpu2.iowait - Cpu1.iowait);
  double delta_irq = (Cpu2.irq - Cpu1.irq);
  double delta_softirq = (Cpu2.softirq - Cpu1.softirq);
  double delta_steal = (Cpu2.steal - Cpu1.steal);
  double delta_guest = (Cpu2.guest - Cpu1.guest);
  double delta_guest_nice = (Cpu2.guest_nice - Cpu1.guest_nice);
  double delta_total = delta_user + delta_nice + delta_system + delta_idle +
                       delta_iowait + delta_irq + delta_softirq + delta_steal +
                       delta_guest + delta_guest_nice;
  double delta_idle_iowait = delta_idle + delta_iowait;
  return (delta_total - delta_idle_iowait) / delta_total * 100.0;
}