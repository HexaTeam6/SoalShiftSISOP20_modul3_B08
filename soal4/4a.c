#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
typedef unsigned long long ULL;

int i, j, k, jumlah; 
int mat1[4][2] ={ {1, 2}, 
					        {3, 4},
                  {1, 2},
                  {3, 5}}; 

int mat2[2][5] ={ {5, 6, 5, 8, 2}, 
					        {3, 2, 4, 5, 3}}; 

pthread_t tid[5];

void* playandcount(void *arg){
	pthread_t id=pthread_self();
	int x, y;
  ULL (*res)[5] = arg;
	if(pthread_equal(id,tid[0])) //thread untuk ngitung
	{

        for(x = 0; x < 4; x++){
            res[x][0] = mat1[x][0]*mat2[0][0] + mat1[x][1]*mat2[1][0];
        }
	}
	else if(pthread_equal(id,tid[1])) //thread untuk ngitung
	{

        for(x = 0; x < 4; x++){
            res[x][1] = mat1[x][0]*mat2[0][1] + mat1[x][1]*mat2[1][1];
        }
	}
  else if(pthread_equal(id,tid[2])) //thread untuk ngitung
	{

        for(x = 0; x < 4; x++){
            res[x][2] = mat1[x][0]*mat2[0][2] + mat1[x][1]*mat2[1][2];
        }
	}
  else if(pthread_equal(id,tid[3])) //thread untuk ngitung
	{

        for(x = 0; x < 4; x++){
            res[x][3] = mat1[x][0]*mat2[0][3] + mat1[x][1]*mat2[1][3];
        }
	}
	else if(pthread_equal(id,tid[4])) // thread menampilkan matrix hasil
	{
        for(x = 0; x < 4; x++){
            res[x][4] = mat1[x][0]*mat2[0][4] + mat1[x][1]*mat2[1][4];
        }

        printf("Hasil perkalian matriks: \n");
        for(i = 0; i < 4; i++){
            for(j = 0; j < 5; j++){
                printf("%llu\t", res[i][j]);
            }
            printf("\n");
        }
        
	}

	return NULL;
}

int main() { 
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int[5][5]), IPC_CREAT | 0666);
    ULL (*res)[5] = shmat(shmid, NULL, 0);

    int i=0;
    int err;
    while(i<5){
      err=pthread_create(&(tid[i]),NULL,&playandcount,res); //membuat thread
      if(err!=0) printf("\n can't create thread : [%s]",strerror(err));
      else printf("\n create thread success\n");
      i++;
    }

    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    pthread_join(tid[3],NULL);
    pthread_join(tid[4],NULL);

	return 0; 
} 