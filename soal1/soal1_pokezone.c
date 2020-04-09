#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int *shm_id_pokemon;
int *shm_powder;
int *shm_pokeball;
int *shm_berry;

pthread_t restockthread;
pthread_t randomthread;
void *frestockhread(){
    while (1){
        sleep(10);
        *shm_powder += 10;
        if (*shm_powder > 200) *shm_powder = 200;
        *shm_pokeball += 10;
        if (*shm_pokeball > 200) *shm_pokeball = 200;
        *shm_berry += 10;
        if (*shm_berry > 200) *shm_berry = 200;
    }
}
void *fpokerandomthread(){
    while (1){
        int poke;
        int r = rand() % 100;
        if (r < 5) poke = (rand() % 5) + 10;
        else if (r < 15) poke = (rand() % 5) + 5;
        else poke = (rand() % 5);

        if (rand() % 8000 == 0) poke += 15;
        *shm_id_pokemon = poke;
        sleep(1);
    }
}

int main(){
    srand(time(NULL));
    key_t key1 = 1000;
    key_t key2 = 1001;
    key_t key3 = 1002;
    key_t key4 = 1003;

    int shmidp = shmget(key1, sizeof(int), IPC_CREAT | 0666);
    int shmp = shmget(key2, sizeof(int), IPC_CREAT | 0666);
    int shmpb = shmget(key3, sizeof(int), IPC_CREAT | 0666);
    int shmb = shmget(key4, sizeof(int), IPC_CREAT | 0666);

    shm_id_pokemon = shmat(shmidp, NULL, 0);
    shm_powder = shmat(shmp, NULL, 0);
    shm_pokeball = shmat(shmpb, NULL, 0);
    shm_berry = shmat(shmb, NULL, 0);
    
    *shm_id_pokemon = 100;
    *shm_powder = 100;
    *shm_pokeball = 100;
    *shm_berry = 100;
    
    pthread_create(&restockthread, NULL, frestockhread, NULL);
    pthread_create(&randomthread, NULL, fpokerandomthread, NULL);
    
    printf("1. Quit game\nInput: ");
    int x;
    scanf("%d", &x);
    if (x == 1){
        DIR *dir = opendir("/proc");
        struct dirent *ent;
        char *endptr;
        while ((ent = readdir(dir)) != NULL){
            long lpid = strtol(ent->d_name, &endptr, 10);
            if (*endptr != '\0') continue;
            char buf[512];
            snprintf(buf, sizeof(buf), "/proc/%ld/cmdline", lpid);
            FILE *fp = fopen(buf, "r");
            if (fp && fgets(buf, sizeof(buf), fp) != NULL) {
                char *first = strtok(buf, " ");
                if (strcmp(first, "./soal1_traizone") == 0){
                    pid_t child = fork();
                    if (child == 0){
                        char cmd[500];
                        sprintf(cmd, "kill -INT %ld", lpid);
                        execl("/bin/sh", "sh", "-c", cmd, NULL);
                    }
                }
                fclose(fp);
            }
        }
        closedir(dir);
        int status;
        while (wait(&status) > 0);

        shmdt(shm_id_pokemon);
        shmdt(shm_pokeball);
        shmdt(shm_powder);
        shmdt(shm_berry);
        shmctl(shmidp, IPC_RMID, NULL);
        shmctl(shmp, IPC_RMID, NULL);
        shmctl(shmpb, IPC_RMID, NULL);
        shmctl(shmb, IPC_RMID, NULL);
        exit(EXIT_SUCCESS);
    }
}