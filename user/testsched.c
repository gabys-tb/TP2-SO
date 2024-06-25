#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

void spin() {
  volatile int i;
  for(i = 0; i < 1000000; i++); // Reduzido o número de iterações
}

int main(int argc, char *argv[]) {
  int pid;
  int iterations = 10; // Definir o número de iterações

  printf("fork and exec test\n");

  pid = fork();
  if (pid < 0) {
    printf("fork failed\n");
    exit(1);
  }
  if (pid == 0) {
    printf("I am the child process\n");
    for (int i = 0; i < iterations; i++) {
      spin();
      printf("Child 1 - Iteration %d\n", i+1);
    }
    exit(1);
  } else {
    printf("I am the parent process, child pid: %d\n", pid);
    wait(0);  // Espera o filho terminar
  }

  if (fork() == 0) {
    settickets(10);
    for (int i = 0; i < iterations; i++) {
      spin();
      printf("Child 2 - Iteration %d\n", i+1);
    }
    exit(1);
  }

  if (fork() == 0) {
    settickets(20);
    for (int i = 0; i < iterations; i++) {
      spin();
      printf("Child 3 - Iteration %d\n", i+1);
    }
    exit(1);
  }

  while (wait(0) > 0);  // Espera todos os filhos terminarem
  exit(1);
}
