#ifndef _SCHED_H
#define _SCHED_H
#endif
#ifndef NULL
#define NULL ((void *) 0)
#endif

#define NR_TASKS 64
#define TASK_RUNNING 0
#define TASK_INTERRUPTIBLE 1
#define TASK_UNINTERRUPTIBLE 2
#define TASK_ZOMBIE 3
#define TASK_STOPPED 4

#endif

typedef int (*fn_ptr) ();

struct task_struct {
/*-- Hardcoded --*/
	long state;	/* -1 unrunnable, 0 runnable, >0 stopped */
	long counter;
	long priority;
	long signal;
	fn_ptr sig_restorer;
	fn_ptr sig_fn[32];
/*-- various fields --*/
	int exit_code;
	unsigned long end_code,end_data,brk,start_stack;
	long pid,father,pgrp,session,leader;
	unsigned short uid,euid,suid;
	unsigned short gid,egid,sgid;
	long alarm;
	long utime,stime,cutime,cstime,start_time;
	unsigned short used_math;
/*-- File System Info --*/
	int tty;
	unsigned short umask;
	struct m_inode * pwd;
	struct m_inode * root;
	unsigned long close_on_exec;
	struct file * filp[NR_OPEN];
	struct desc_struct ldt[3];
	struct tss_struct tss;
};	
