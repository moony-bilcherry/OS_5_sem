#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <signal.h>


int main() {
	pid_t tid = gettid();
	for(int i = 1; i < 1000; i++) {
		sleep(2);
		printf("OS04_06_T1 PID, TID: %d, %d - #%d\n",getpid(), tid, i);		
	}

	exit(0);
}