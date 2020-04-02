#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
 
pthread_t tid[100];

char tempwd[1024];

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

void* move(void *arg) {
    char *path;
    char ext[100], dirname[100], dom[100], cut[100], fn[100];
    path = (char *) arg;
    strcpy(dom, arg);
    strcpy(cut, arg);
    char *split, *arr[5], *splitn, *arrn[5];
    int n = 0;
    split = strtok(path, ".");
    while(split != NULL) {
        arr[n] = split;
        n++;
        split = strtok(NULL, ".");
    }
    if(n == 1) {
        strcpy(ext, "Unknown");
    }
    else {
        int a;
        for(a = 0; a < strlen(arr[n-1]); a++) {
            ext[a] = tolower(arr[n-1][a]);
        }
    }

    n = 0;
    splitn = strtok(cut, "/");
    while(splitn != NULL) {
        arrn[n] = splitn;
        n++;
        splitn = strtok(NULL, "/");
    }
    strcpy(fn, arrn[n-1]);

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    strcpy(dirname, cwd);
    strcat(dirname, "/");
    strcat(dirname, ext);
    memset(ext, 0, 100);
    mkdir(dirname, 0777);

    FILE *pf1, *pf2;
    pf1 = fopen(dom, "r");
    strcat(dirname, "/");
    strcat(dirname, fn);
    pf2 = fopen(dirname, "w");
    if(!pf1) {
        printf("Unable to open source file to read\n");
    }
    if(!pf2) {
        printf("Unable to open target file to write\n");
    }

    int ch;
    while ((ch = fgetc(pf1)) != EOF) {
        fputc(ch, pf2);
    }
    fclose(pf1);
    fclose(pf2);
    remove(dom);

    return NULL;
}

void* movetemp(void *arg) {
    char *path;
    char ext[100], dirname[100], dom[100], cut[100], fn[100];
    path = (char *) arg;
    strcpy(dom, arg);
    strcpy(cut, arg);
    char *split, *arr[5], *splitn, *arrn[5];
    int n = 0;
    split = strtok(path, ".");
    while(split != NULL) {
        arr[n] = split;
        n++;
        split = strtok(NULL, ".");
    }
    if(n == 1) {
        strcpy(ext, "Unknown");
    }
    else {
        int a;
        for(a = 0; a < strlen(arr[n-1]); a++) {
            ext[a] = tolower(arr[n-1][a]);
        }
    }

    n = 0;
    splitn = strtok(cut, "/");
    while(splitn != NULL) {
        arrn[n] = splitn;
        n++;
        splitn = strtok(NULL, "/");
    }
    strcpy(fn, arrn[n-1]);

    strcpy(dirname, tempwd);
    strcat(dirname, "/");
    strcat(dirname, ext);
    memset(ext, 0, 100);
    mkdir(dirname, 0777);

    FILE *pf1, *pf2;
    pf1 = fopen(dom, "r");
    strcat(dirname, "/");
    strcat(dirname, fn);
    pf2 = fopen(dirname, "w");
    if(!pf1) {
        printf("Unable to open source file to read\n");
    }
    if(!pf2) {
        printf("Unable to open target file to write\n");
    }

    int ch;
    while ((ch = fgetc(pf1)) != EOF) {
        fputc(ch, pf2);
    }
    fclose(pf1);
    fclose(pf2);
    remove(dom);

    return NULL;
}

int main(int argc, char *argv[]) {

    getcwd(tempwd, sizeof(tempwd));

    int i;
    if(strcmp(argv[1], "-f") == 0) {
        for(i = 2; i < argc; i++) {
            if(is_regular_file(argv[i])) {
                pthread_create(&(tid[i-2]), NULL, move, (void *)argv[i]);
            }
        }
        for(i = 0; i < argc - 2; i++) {
            pthread_join(tid[i], NULL);
        }
    }
    else if(strcmp(argv[1], "*") == 0 && argc == 2) {
        DIR *dr;
        struct dirent *de;
        dr = opendir(".");

        if (dr == NULL) { 
            printf("Could not open current directory" );  
        }
        else {
            i = 0;
            char wd[1024], pathn[1024];
            getcwd(wd, sizeof(wd));
            while((de = readdir(dr)) != NULL){
                if(is_regular_file(de->d_name)) {
                    strcpy(pathn, wd);
                    strcat(pathn, "/");
                    strcat(pathn, de->d_name);
                    pthread_create(&(tid[i]), NULL, move, (void *)pathn);
                    pthread_join(tid[i], NULL);
                    i++;
                }
            }
            closedir(dr);
        }
    }
    else if(strcmp(argv[1], "-d") == 0 && argc == 3) {
        chdir(argv[2]);
        DIR *dr;
        struct dirent *de;
        dr = opendir(".");

        if (dr == NULL) { 
            printf("Could not open current directory" );  
        }
        else {
            i = 0;
            char wd[1024], pathn[1024];
            getcwd(wd, sizeof(wd));
            while((de = readdir(dr)) != NULL){
                if(is_regular_file(de->d_name)) {
                    strcpy(pathn, wd);
                    strcat(pathn, "/");
                    strcat(pathn, de->d_name);
                    pthread_create(&(tid[i]), NULL, movetemp, (void *)pathn);
                    pthread_join(tid[i], NULL);
                    i++;
                }
            }
            closedir(dr);
        }
    }
    else {
        printf("Option or arguments are not valid\n");
    }
    
    return 0;
}