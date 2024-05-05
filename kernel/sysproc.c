#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  char exit_msg[32];
  argint(0, &n);
  argstr(1, exit_msg, EXIT_MSG_LEN); // tzur copy a second argument from user space to kernel space
  exit(n, exit_msg); // tzur
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  // tzur prev func: uint64 p; argaddr(0, &p); return wait(p);
  // modified func:
  uint64 p, exit_message_addr;
  argaddr(0, &p);
  argaddr(1, &exit_message_addr);
  return wait(p, exit_message_addr);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// os as1 task2
uint64
sys_memsize(void)
{
  // from here we can call other function in the kernel from proc.c or trap.c and many others places
    return myproc()->sz;
}

// os as1 task5
uint64
sys_set_ps_priority(void)
{
  int priority;
  argint(0, &priority);
  set_ps_priority(priority);
  return 0;
}

// os as1 task6
uint64
sys_set_cfs_priority(void)
{
  int priority;
  argint(0, &priority);
  set_cfs_priority(priority);
  return 0;
}

// os as1 task6
uint64
sys_get_cfs_stats(void)
{
  int procId;
  uint64 addr;
  argint(0, &procId);
  argaddr(1, &addr);
  get_cfs_stats(procId, addr);
  return 0;
}

// os as1 task7
uint64
sys_set_policy(void)
{
  // from here we can call other function in the kernel from proc.c or trap.c and many others places
  int policy;
  argint(0, &policy);
  set_policy(policy);
  return 0;
}
