#include <time.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
pthread_t tid[3];

void* randomPokemon(void *arg){
    sleep(5);
    arg++;
}

int main() {
    key_t key = 1234;
    int *pokemonId;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    pokemonId = shmat(shmid, NULL, 0);

    *pokemonId = 13;

    // pthread_create(&(tid[0]),NULL,randomPokemon,pokemonId);

    // srand(time(NULL));

    // int fitur;
    // while (1){
    //     printf("[1]Shutdown game\n");
    //     printf("[2]Jual Item\n");
    //     scanf("%d", &fitur);

    //     if(fitur==1){
            
    //     }
    //     else if (fitur==2){
            
    //     }
    //     else if (fitur==3){
            
    //     }
        
    // }

	return 0; 
}