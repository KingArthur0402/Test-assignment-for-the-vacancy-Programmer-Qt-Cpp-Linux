#include "udp_client.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../task1/cpu_info.h"

#define MAX_LEN 1024
#define MAX_CPU 128

void *udp_sender() {
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(1234);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  int error = 0;
  while (!error) {
    Cpu_info Cpu1[MAX_CPU];
    Cpu_info Cpu2[MAX_CPU];
    int cpu_count = 0;
    error = read_cpu(Cpu1, &cpu_count);
    sleep(1);
    if (!error) error = read_cpu(Cpu2, &cpu_count);
    if (!error) {
      char buffer[MAX_LEN] = "";
      for (int i = 0; i != cpu_count + 1; ++i) {
        char line[64];
        sprintf(line, i == cpu_count ? "%.2lf" : "%.2lf,",
                calc_usage(Cpu1[i], Cpu2[i]));
        strcat(buffer, line);
      }
      strcat(buffer, "\n");
      sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr,
             sizeof(server_addr));
    }
  }
  close(sockfd);
  printf("ERROR");
  return NULL;
}