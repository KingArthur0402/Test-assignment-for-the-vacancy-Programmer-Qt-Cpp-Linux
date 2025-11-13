#ifndef CPU_INFO_H
#define CPU_INFO_H

#define CPU_NAME_LEN_MAX 8

typedef struct {
  char cpu_name[CPU_NAME_LEN_MAX];
  unsigned long long user, nice, system, idle, iowait, irq, softirq, steal,
      guest, guest_nice;
} Cpu_info;

int read_cpu(Cpu_info *Cpu, int *cpu_count);
double calc_usage(Cpu_info const Cpu1, Cpu_info const Cpu2);

#endif