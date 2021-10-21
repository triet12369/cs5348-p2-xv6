#include "types.h" //
#include "x86.h"
#include "defs.h"
#include "param.h" //
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"

//#include "pstat.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
// The following code is added by Triet Cao - TXC200031
// set number of tickets to a process
// If the number of tickets is less than 1 then we throw error
int
sys_settickets(void)
{
  int numtickets;
  int ret = 0;
  argint(0, &numtickets);
  // cprintf("settickets: Process name %s\n", proc->name);
  // cprintf("settickets: proc tickets before %d\n", proc->num_tickets);
  if (numtickets < 1) ret = -1;
  else {
    proc->num_tickets = numtickets;
  }
  // cprintf("settickets: proc tickets after %d\n", proc->num_tickets);
  return ret;
}

int 
sys_getpinfo(void){
  struct pstat* obj;
  if(argptr(0,(void*)&obj,sizeof(obj))<0) return -1;
  return getpinfo(obj);
}
