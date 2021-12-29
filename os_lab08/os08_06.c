#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int main() {
	int count = 0;
	struct timespec start, end, proc;
	clock_gettime(CLOCK_REALTIME, &start);
	
	for(;;) {
		count++;
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &proc);
		if(proc.tv_sec == 2) {
			printf("# of iterations: %d\n", count);
			printf("CLOCK_PROCESS_CPUTIME_ID: %ld sec, %ld nsec\n", proc.tv_sec, proc.tv_nsec);
			break;
		}
	}
	
	clock_gettime(CLOCK_REALTIME, &end);	
	printf("elapsed time (CLOCK_REALTIME): %ld sec, %ld nsec\n", end.tv_sec - start.tv_sec, end.tv_nsec - start.tv_nsec);
	
	exit(0);
}
