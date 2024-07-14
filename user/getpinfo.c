#include "kernel/types.h"
#include "kernel/pstat.h"
#include "kernel/param.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc > 1){
    fprintf(2, "Usage: getpinfo\n");
    return 0;
  }

  
  struct pstat *ps = {0};
  if(getpinfo(ps) < 0)
  {
    fprintf(2, "getpinfo failed\n");
    exit(1);
  }

  fprintf(2, "PID\tTICKETS\tTICKS\n");
  for(int i = 0; i < NPROC; i++){
    if(ps->inuse[i])
    {
        fprintf(2, "%d\t%d\t%d\n", ps->pid[i], ps->tickets[i], ps->ticks[i]);
    }
  }

  exit(0);
}
