#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
typedef unsigned long long ULL;

int main() { 
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int[5][5]), IPC_CREAT | 0666);
    ULL (*res)[5] = shmat(shmid, NULL, 0);

	int i, j, k, jumlah; 
	int mat1[4][2] ={{1, 2}, 
					{3, 4},
                    {1, 2},
                    {3, 5}}; 

	int mat2[2][5] ={{5, 6, 5, 8, 2}, 
					{3, 2, 4, 5, 3}}; 

    for(i = 0; i < 4; i++){
      for(j = 0; j < 5; j++){
        for(k = 0; k < 2; k++){
          jumlah += mat1[i][k] * mat2[k][j];
        }
        res[i][j] = jumlah;
        jumlah = 0;
      }
    }

    printf("Hasil perkalian matriks: \n");
    for(i = 0; i < 4; i++){
        for(j = 0; j < 5; j++){
            printf("%llu\t", res[i][j]);
        }
        printf("\n");
    }

    // shmdt(res);
    // shmctl(shmid, IPC_RMID, NULL);

	return 0; 
} 