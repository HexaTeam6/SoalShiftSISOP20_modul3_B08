#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <termios.h>
#define PORT 8080

pthread_t tid[2];

int health = 100;

void* tapdetect(void *arg) {
    int sock = *(int *)arg;
    int c;   
    static struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON);          
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);   // Merubah
    while((c=getchar())!= 'e' || health > 0) {
        putchar(c);
        if(c == ' ') {
            send(sock, "hit", 3, 0);
            printf("hit !!\n");
        }  
    }             
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);   // Mengembalikan
}

void* healthdetect(void *arg) {
    int sock = *(int *)arg;
    int valread;
    char msg[1024];
    while(1) {
        memset(msg, 0, 1024);
        valread = read( sock , msg, 1024);
        if(strcmp(msg, "minus") == 0) {
            health -= 10;
            printf("Health %d\n", health);
        }
        if(health == 0)
        {
            send(sock , "die", strlen("die"), 0 );
            break;
        }   
    }
}

int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    int screen = 1; // Buat screen
    char comma[10], commb[10], nama[100], pass[100], data[100], spc;

    while(1) {
        if(screen == 1) {
            printf("1. Login\n2. Register\nChoices : ");
            scanf("%s", comma);
            scanf("%c", &spc);
            send(sock , comma, strlen(comma), 0 );
            if(strcmp(comma, "register") == 0) {
                printf("Username : ");
                scanf("%[^\n]s", nama);
                scanf("%c", &spc);
                printf("Password : ");
                scanf("%[^\n]s", pass);
                scanf("%c", &spc);
                strcpy(data, nama);
                strcat(data, "||");
                strcat(data, pass);
                // printf("data register %s\n", data);
                send(sock , data, strlen(data), 0 );
                printf("Register success\n");

                memset(data, 0, 100);
                memset(nama, 0, 100);
                memset(pass, 0, 100);
                memset(buffer, 0, 1024);
                screen = 2;
            }
            if(strcmp(comma, "login") == 0) {
                printf("Username : ");
                scanf("%[^\n]s", nama);
                scanf("%c", &spc);
                printf("Password : ");
                scanf("%[^\n]s", pass);
                scanf("%c", &spc);
                strcpy(data, nama);
                strcat(data, "||");
                strcat(data, pass);
                strcat(data, "\n");
                // printf("data login %s\n", data);
                send(sock , data, strlen(data), 0 );

                memset(buffer, 0, 1024);
                valread = read( sock , buffer, 1024);
                if(strcmp(buffer, "login_berhasil") == 0) {
                    printf("Login success\n");
                    screen = 2;
                }
                if(strcmp(buffer, "login_gagal") == 0) {
                    printf("Login failed\n");
                    screen = 1;
                }

                memset(data, 0, 100);
                memset(nama, 0, 100);
                memset(pass, 0, 100);
                memset(buffer, 0, 1024);
            }
        }

        if(screen == 2) {
            printf("1. Find Match\n2. Logout\nChoices : ");
            scanf("%s", commb);
            send(sock , commb, strlen(commb), 0 );
            if(strcmp(commb, "find") == 0) {
                while(1) {
                    memset(buffer, 0, 1024);
                    valread = read(sock , buffer, 1024);

                    if(strcmp(buffer, "one") == 0) {
                        printf("Waiting for player ...\n");
                    }
                    if(strcmp(buffer, "two") == 0) {
                        break;
                    }
                    sleep(1);
                }
                printf("Game started, silahkan tap tap secepat mungkin\n");
                
                pthread_create(&(tid[0]), NULL, tapdetect, &sock);
                pthread_create(&(tid[1]), NULL, healthdetect, &sock);

                memset(buffer, 0, 1024);
                valread = read(sock , buffer, 1024);
                if(strcmp(buffer, "menang") == 0) {
                    printf("Game berakhir kamu menang\n");
                }
                if(strcmp(buffer, "kalah") == 0) {
                    printf("Game berakhir kamu kalah\n");
                }
                screen = 2;
                int health = 100;
                memset(buffer, 0, 1024);
            }
            if(strcmp(commb, "logout") == 0) {
                memset(commb, 0, 10);
                screen = 1;
            }
        }

    }

    return 0;
}
