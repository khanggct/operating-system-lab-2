#include "kernel/types.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

void
testmem()
{
  struct sysinfo info;
  uint64 m1, m2;

  if (sysinfo(&info) < 0) {
    printf("sysinfotest: sysinfo failed\n");
    exit(1);
  }
  m1 = info.freemem;

  // Allocate one page (4096 bytes)
  if((uint64)sbrk(4096) == 0xffffffffffffffffL){
    printf("sysinfotest: sbrk failed\n");
    exit(1);
  }

  sysinfo(&info);
  m2 = info.freemem;

  // The free memory should decrease by at least one page
  if (m1 - m2 < 4096) {
    printf("sysinfotest: error! Free memory did not decrease.\n");
    exit(1);
  }
}

void
testproc()
{
  struct sysinfo info;
  uint64 n1, n2;

  sysinfo(&info);
  n1 = info.nproc;

  if(fork() == 0){
    sleep(1);
    exit(0);
  } else {
    sysinfo(&info);
    n2 = info.nproc;
    if(n2 - n1 != 1){
      printf("sysinfotest: error! nproc did not increase.\n");
      exit(1);
    }
    wait(0);
  }
}

int
main(int argc, char *argv[])
{
  printf("sysinfotest: start\n");
  testmem();
  testproc();
  printf("sysinfotest: OK\n");
  exit(0);
}
