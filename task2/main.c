#include <pthread.h>

#include "../task1/cpu_info.h"
#include "udp_client.h"

int main() {
  pthread_t tid;
  pthread_create(&tid, NULL, udp_sender, NULL);
  pthread_join(tid, NULL);
  return 0;
}