#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long ULL; 
#define MOD 1000000007

ULL factorial(int n){
    ULL prod = 1;
    int k = 0;
    while (k != n){
        k++;
        prod = (prod * k) % MOD;
    }

    return prod;
}


pthread_t tid[3];
pid_t child;

void* playandcount(void *arg){
	pthread_t id=pthread_self();
	int i, j;
    ULL (*res)[5] = arg;
	if(pthread_equal(id,tid[0])){

        for(i = 0; i < 2; i++){
            for(j = 0; j < 5; j++){
                res[i][j] = factorial(res[i][j]);
            }
        }
	}
	else if(pthread_equal(id,tid[1])){

        for(i = 2; i < 4; i++){
            for(j = 0; j < 5; j++){
                res[i][j] = factorial(res[i][j]);
            }
        }
	}
	else if(pthread_equal(id,tid[2])){
        for(i = 0; i < 4; i++){
            for(j = 0; j < 5; j++){
                printf("%llu\t", res[i][j]);
            }
            printf("\n");
        }
	}

	return NULL;
}

int main(void){
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int[5][5]), IPC_CREAT | 0666);
    ULL (*res)[5] = shmat(shmid, NULL, 0);

    int i=0;
	int err;
	while(i<3){
		err=pthread_create(&(tid[i]),NULL,playandcount,res);
		if(err!=0){
			printf("\n can't create thread : [%s]",strerror(err));
		}
		else{
			printf("\n create thread success\n");
		}
		i++;
	}

	pthread_join(tid[1],NULL);
	pthread_join(tid[2],NULL);

    shmdt(res);
    shmctl(shmid, IPC_RMID, NULL);

    exit(0);
	return 0;
}