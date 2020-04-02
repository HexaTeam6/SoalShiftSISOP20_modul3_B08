#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#define PORT 8080

pthread_t tid[100];
int id_sock[2];
int user = 0;
int kalah = 0;

void* player(void *arg) {
    int new_socket = *(int *)arg;
    int valread;
    char buffer[1024] = {0};
    int screen = 1;
    char nama[100], pass[100];
    // printf("new_socket %d\n", new_socket);

    FILE *pf;
    pf = fopen("akun.txt", "a");
    if(pf == NULL)
    {
        printf("Create file failed\n");
        exit(EXIT_FAILURE);
    }
    fclose(pf);

    while(1) {
        if(screen == 1) {
            memset(buffer, 0, 1024);
            valread = read( new_socket, buffer, 1024);
            printf("Pertama : %s\n", buffer);
            if(strcmp(buffer, "register") == 0) {
                memset(buffer, 0, 1024);
                valread = read( new_socket, buffer, 1024);
                // printf("regis %s\n", buffer);
                pf = fopen("akun.txt", "a");
                fprintf(pf, "%s\n", buffer);
                memset(buffer, 0, 1024);
                fclose(pf);

                char line[100]={0};
                pf = fopen("akun.txt", "r");
                printf("--- List Account Terdaftar ---\n");
                while(fgets(line, sizeof(line), pf) != NULL){
                    sscanf(line, "%[^|]||%[^\n]s", nama, pass);
                    printf("Username : %s\n Password : %s\n", nama, pass);
                    memset(nama, 0, 100);
                    memset(pass, 0, 100);
                }
                fclose(pf);
                screen = 2;
            }
            if(strcmp(buffer, "login") == 0) {
                memset(buffer, 0, 1024);
                valread = read( new_socket, buffer, 1024);
                // printf("login %s\n", buffer);

                int catch = 0;
                char line[100]={0};
                pf = fopen("akun.txt", "r");
                while(fgets(line, sizeof(line), pf) != NULL){
                    if(strcmp(line, buffer) == 0) {
                        // printf("catch\n");
                        catch = 1;
                    }
                }
                fclose(pf);
                if(catch == 1) {
                    send(new_socket , "login_berhasil", 14 , 0 );
                    printf("Auth success\n");
                    screen = 2;
                }
                else {
                    send(new_socket , "login_gagal", 11 , 0 );
                    printf("Auth failed\n");
                    screen = 1;
                }
                memset(buffer, 0, 1024);
            }
        }

        if(screen == 2) {
            memset(buffer, 0, 1024);
            valread = read( new_socket, buffer, 1024);
            printf("Kedua : %s\n", buffer);
            if(strcmp(buffer, "find") == 0) {
                user++;
                while(user < 2) {
                    // printf("Send one  %d\n", user);
                    send(new_socket, "one", 3, 0);
                    sleep(1);
                }
                if(user >= 2) {
                    // printf("Send two %d\n", user);
                    send(new_socket, "two", 3, 0);
                }

                while(1) {
                    memset(buffer, 0, 1024);
                    valread = read( new_socket, buffer, 1024);
                    if (strcmp(buffer, "hit") == 0)
                    {
                        if(new_socket == id_sock[0])
                        {
                            send(id_sock[1], "minus", 5, 0);
                        }
                        if(new_socket == id_sock[1])
                        {
                            send(id_sock[0], "minus", 5, 0);
                        }
                    }
                    if (strcmp(buffer, "die") == 0)
                    {
                        if(new_socket == id_sock[0])
                        {
                            send(id_sock[1], "menang", 6, 0);
                            send(id_sock[0], "kalah", 5, 0);
                        }
                        if(new_socket == id_sock[1])
                        {
                            send(id_sock[0], "menang", 6, 0);
                            send(id_sock[1], "kalah", 5, 0);
                        }
                        break;
                    }
                }
                screen = 2;
                user--;
            }
            if(strcmp(buffer, "logout") == 0) {
                user--;
                memset(buffer, 0, 1024);
                screen = 1;
            }
        }
    }
}

int main(int argc, char const *argv[]) {

    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        id_sock[i] = new_socket;
        pthread_create(&(tid[i]), NULL, player, &new_socket);
        i++;
    }

    return 0;
}
