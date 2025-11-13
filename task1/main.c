#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "cpu_info.h"

#define MAX_CPU 128

int main() {
  int error = 0, cpu_count = 0;
  Cpu_info Cpu1[MAX_CPU];
  Cpu_info Cpu2[MAX_CPU];
  while (!error) {
    error = read_cpu(Cpu1, &cpu_count);
    sleep(1);
    if (!error) error = read_cpu(Cpu2, &cpu_count);
    if (!error) printf("Detected %d CPU cores\n", cpu_count);
    for (int i = 0; !error && i != cpu_count + 1; ++i) {
      printf("%s: %.2lf%%\n", (Cpu1[i]).cpu_name, calc_usage(Cpu1[i], Cpu2[i]));
    }
    if (!error) printf("-------------------\n");
  }
  printf("ERROR");
  return 0;
}