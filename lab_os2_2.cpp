#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <cstdio>
#include <pthread.h>

typedef struct {
	int flag;
	char symb;
}targs;

pthread_mutex_t mp = PTHREAD_MUTEX_INITIALIZER;

void* process1(void *arg){
	printf("\nthread1 started working\n");
	targs *args = (targs*) arg;
	while(args->flag == 0){
		pthread_mutex_lock(&mp);
		for (int i = 0; i < 10; i++){
			printf("1");
			fflush(stdout);
			sleep(1);
		}	
		pthread_mutex_unlock(&mp);
		sleep(1);
	}
	printf("thread1 ended working\n");
	pthread_exit((void*)1);
	return NULL;
}

void* process2(void *arg){
	printf("\nthread2 started working\n");
	targs *args = (targs*) arg;
	while(args->flag == 0){
		pthread_mutex_lock(&mp);
		for (int i = 0; i < 10; i++){
			printf("2");
			fflush(stdout);
			sleep(1);
		}
		pthread_mutex_unlock(&mp);
		sleep(1);
	}
	printf("\nthread2 ended working\n");
	pthread_exit((void*)2);
	return NULL;
}

int main() {
	printf("programm started working\n");
	
	// init mutex
	pthread_mutex_init(&mp, NULL);
	printf("mutex was initialized\n");
	
	targs arg1; targs arg2;
	arg1.flag = 0; arg2.flag = 0;
	arg1.symb = '1'; arg2.symb = '2';
	
	pthread_t id1;
	pthread_t id2;
	
 	pthread_create(&id1, NULL, process1, &arg1);
 	pthread_create(&id2, NULL, process2, &arg2);
 	printf("\nprogramm waits for keystroke\n");
 	getchar();
 	arg1.flag = 1; arg2.flag = 1;
 	
 	int* exictode1, exitcode2;
 	
 	pthread_join(id1, (void**)&exictode1);
 	pthread_join(id2, (void**)&exitcode2);
 	
 	pthread_mutex_destroy(&mp);
 	printf("mutex was destroyed\n");
	printf("programm ended working\n");
	return 0;
}
