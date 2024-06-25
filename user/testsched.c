#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/syscall.h"
#include "kernel/memlayout.h"
#include "kernel/riscv.h"


int
main(void)
{
  int pid;
  //struct proc *p = myproc();

  settickets(42);  // Configurar o atributo no processo pai

  if ((pid = fork()) == 0) {
    // Código do processo filho
    exit(0);
  } else {
    // Código do processo pai
    wait(0);
  }

  exit(0);
}

