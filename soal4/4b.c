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
#define MAX 500 

// ULL factorial(int n){
//     ULL prod = 1;
//     int k = 0;
//     while (k != n){
//         k++;
//         prod = (prod * k) % MOD;
//     }

//     return prod;
// }

ULL factorialPlus(int n){
    ULL prod = 1;
    int k = 0;
    while (k != n){
        k++;
        prod += k;
    }

    return prod;
}

// int multiply(int x, int res[], int res_size) { 
// 	int carry = 0;

// 	for (int i=0; i<res_size; i++) { 
// 		int prod = res[i] * x + carry; 
        
//         res[i] = prod % 10; 
        
//         carry = prod/10;	 
// 	} 

// 	while (carry) { 
// 		res[res_size] = carry%10; 
// 		carry = carry/10; 
// 		res_size++; 
// 	} 
// 	return res_size; 
// }

// void factorial(int n) { 
// 	int res[MAX]; 

// 	res[0] = 1; 
// 	int res_size = 1; 

// 	for (int x=2; x<=n; x++) 
// 		res_size = multiply(x, res, res_size); 

// 	for (int i=res_size-1; i>=0; i--) 
// 		printf("%d", res[i]);
// }  

pthread_t tid[3];
pid_t child;

void* factOut(void *arg){
	pthread_t id=pthread_self();
	int i, j;
    ULL (*res)[5] = arg;
	if(pthread_equal(id,tid[0])){

        for(i = 0; i < 2; i++){
            for(j = 0; j < 5; j++){
                res[i][j] = factorialPlus(res[i][j]);
                // factorial(res[i][j]);
                // printf("\t");
            }
            // printf("\n");
        }
	}
	else if(pthread_equal(id,tid[1])){

        for(i = 2; i < 4; i++){
            for(j = 0; j < 5; j++){
                res[i][j] = factorialPlus(res[i][j]);
                // factorial(res[i][j]);
                // printf("\t");
            }
            // printf("\n");
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
		err=pthread_create(&(tid[i]),NULL,factOut,res);
		if(err!=0){
			// printf("\n can't create thread : [%s]",strerror(err));
		}
		else{
			// printf("\n create thread success\n");
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