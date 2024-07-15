#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/syscall.h"
#include "kernel/memlayout.h"
#include "kernel/riscv.h"
#include "kernel/pstat.h"

#define NPROC 64

void print_stats(void){
  struct pstat ps;

  if(getpinfo(&ps) < 0)
  {
    fprintf(2, "getpinfo failed\n");
    exit(1);
  }

  fprintf(2, "PID\tTICKETS\tTICKS\n");
  for(int i = 0; i < NPROC; i++){
    if(ps.inuse[i])
    {
        fprintf(2, "%d\t%d\t%d\n", ps.pid[i], ps.tickets[i], ps.ticks[i]);
    }
  }
}

void busy_wait(int ticks) {
  int start_ticks = uptime();
  while (uptime() - start_ticks < ticks) {
    // Busy wait
  }
}

int main(void)
{
  int pid1, pid2, pid3;

  // Processo pai
  print_stats();

  if ((pid1 = fork()) == 0) {
    // Primeiro processo filho
    settickets(100); // Atribui 10 tickets
    while(1) {
      //busy_wait(100);
      //sleep(100); // Mantém o processo ocupado
    }
  }

  if ((pid2 = fork()) == 0) {
    // Segundo processo filho
    settickets(200); // Atribui 20 tickets
    while(1) {
      //busy_wait(100); // Mantém o processo ocupado
    }
  }

  if ((pid3 = fork()) == 0) {
    // Terceiro processo filho
    settickets(300); // Atribui 30 tickets
    while(1) {
      //busy_wait(100); // Mantém o processo ocupado
    }
  }

  // Processo pai continua a imprimir estatísticas periodicamente
  for (int i = 0; i < 50; i++) { // Ajuste o número de iterações conforme necessário
    print_stats();
    sleep(100); // Aguarda um pouco antes de coletar estatísticas novamente
  }

  // Código para finalizar os filhos (não deve ser alcançado neste exemplo de teste)
  kill(pid1);
  kill(pid2);
  kill(pid3);

  wait(0);
  wait(0);
  wait(0);

  exit(0);
}