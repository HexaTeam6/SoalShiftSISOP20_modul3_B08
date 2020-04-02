#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
// #include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 8080

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
      
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

    // Buat akun.txt
    FILE *pf;
    pf = fopen("akun.txt", "a");
    if(pf == NULL)
    {
        printf("Create file failed\n");
        exit(EXIT_FAILURE);
    }
    fclose(pf);

    pid_t c_pid;
    int screen = 1, player = 0;
    char nama[100], pass[100];

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        printf("Connection accepted from %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

        c_pid = fork();
        if(c_pid == 0) {
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
                        player++;
                        while(player < 2) {
                            printf("Send one  %d\n", player);
                            send(new_socket, "one", 3, 0);
                            sleep(1);
                        }
                        if(player >= 2) {
                            printf("Send two %d\n", player);
                            send(new_socket, "two", 3, 0);
                        }


                        // if(menang) == 0) {
                        //     send(new_socket, "menang", 6, 0);
                        // }
                        // if(kalah) == 0) {
                        //     send(new_socket, "kalah", 5, 0);
                        // }
                        screen = 2;
                    }
                    if(strcmp(buffer, "logout") == 0) {
                        memset(buffer, 0, 1024);
                        screen = 1;
                    }
                }
            }
        }
    }

    // send(new_socket , hello , strlen(hello) , 0 );
    // printf("Hello message sent\n");

    return 0;
}