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

void* OS04_08_T1(void* arg) {
	pid_t pid = getpid();
	pid_t tid = syscall(SYS_gettid);
	for (int i = 0; i < 75; i++) {
		sleep(1);
		printf("OS04_08_T1 PID, TID: %d, %d - #%d\n",getpid(), tid, i);
		
		if(i == 50) {
			printf("\n-------OS04_08_T1 sleep\n");
			sleep(10);
		}
	}
	
	pthread_exit("Child thread");
}

int main() {
	pthread_t a_thread;
	pid_t tid = gettid();
	void* thread_result;
	printf("main: PID: %d\n", getpid());
	int res = pthread_create(&a_thread, NULL, OS04_08_T1, NULL);
	for(int i = 1; i < 100; i++) {
		sleep(1);
		printf("PID, TID: %d, %d - #%d\n",getpid(), tid, i);
			
		if(i == 30) {
			printf("\n-------Main thread sleep\n");
			sleep(15);
		}
	}
	
	int status = pthread_join(a_thread, (void**)&thread_result);
	exit(0);
}