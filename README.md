# SoalShiftSISOP20_modul3_B08

Soal Shift Modul 3 yang berfokus pada penggunaan thread, socket, fork, dan pipes.

## SOAL 1

Poke*ZONE adalah sebuah game berbasis text terminal mirip dengan Pokemon GO.
Ketentuan permainan sebagai berikut:
- Menggunakan IPC-shared memory, thread, fork-exec.
- Kalian bebas berkreasi dengan game ini asal tidak konflik dengan
requirements yang ada. (Contoh: memberi nama trainer, memberi notifikasi
kalau barang di shop sudah penuh, dan lain-lain).
- Terdapat 2 code yaitu soal2_traizone.c dan soal2_pokezone.c.
- soal2_traizone.c mengandung fitur:

i. Normal Mode (3 Menu)
1. Cari Pokemon
- Jika diaktifkan maka setiap 10 detik akan memiliki
60% chance untuk menemui pokemon bertipe normal,
rare, legendary dengan encounter rate sesuai pada
tabel di bawah (Gunakan Thread).
- Cari pokemon hanya mengatur dia menemukan
pokemon atau tidak. Untuk tipe pokemon dan pokemon
tersebut shiny atau tidak diatur oleh soal2_pokezone.c.
- Opsi “Cari Pokemon” akan berubah jadi “Berhenti
Mencari” ketika state mencari pokemon aktif.
- State mencari pokemon hanya bisa dihentikan ketika
pokemon sudah ditemukan atau trainer memilih untuk
berhenti pada menu.
- Jika menemui pokemon maka akan masuk ke Capture
Mode.
- Untuk mempermudah boleh menambah menu go to
capture mode untuk berpindah dari mode normal ke
mode capture setelah menemukan pokemon dari
thread Cari Pokemon.

2. Pokedex
- Melihat list pokemon beserta Affection Point (AP) yang
dimiliki.
- Maksimal 7 pokemon yang dimiliki.
- Jika menangkap lebih dari 7 maka pokemon yang baru
saja ditangkap akan langsung dilepas dan
mendapatkan pokedollar sesuai dengan tabel dibawah.
- Setiap pokemon yang dimiliki, mempunyai Affection
Point (AP) dengan initial value 100 dan akan terus
berkurang sebanyak -10 AP/10 detik dimulai dari
waktu ditangkap (Gunakan Thread).
- Jika AP bernilai 0, maka pokemon tersebut memiliki
90% chance untuk lepas tanpa memberikan pokedollar
ke trainer atau 10% chance untuk reset AP menjadi 50
AP.
- AP tidak akan berkurang jika dalam Capture Mode.
- Di Pokedex trainer juga bisa melepas pokemon yang
ditangkap dan mendapat pokedollar sesuai dengan
tabel dibawah.
- Bisa memberi berry ke semua pokemon yang dimiliki
untuk meningkatkan AP sebesar +10 (1 berry untuk
semua pokemon yang ada di pokedex).

3. Shop
- Membeli item dari soal2_pokezone.
- Maksimal masing-masing item yang dapat dibeli dan
dipunya oleh trainer adalah 99.

ii. Capture Mode (3 Menu)
1. Tangkap → Menangkap menggunakan pokeball. Berhasil
ditangkap maupun tidak, pokeball di inventory -1 setiap
digunakan.
2. Item → Menggunakan item sesuai dengan tabel item dibawah
(hanya lullaby powder).
3. Keluar → Keluar dari Capture Mode menuju Normal Mode.
- Pokemon tersebut memiliki peluang untuk lari dari trainer
sesuai dengan persentase escape rate pada tabel dibawah
(gunakan thread).

- soal2_pokezone.c mengandung fitur:
     - Shutdown game → Mematikan program soal2_pokezone dan
       soal2_traizone (Gunakan fork-exec).
     - Jual Item (Gunakan Thread).

1. Stock awal semua item adalah 100.
2. Masing-masing item akan bertambah +10 item/10 detik.
3. Maximum item yang dalam shop adalah 200.
4. List item ada pada tabel dibawah.
   - No 
   - Nama Item 
   - Effect 
   - Harga(Pokedollar)
   - Durasi(Detik)
   - CaptureMode
   - NormalMode

   1. Lullaby Powder
      - Meningkatkan chance untuk
        menangkap sebesar 20%
        (misal normal pokemon jadi
        90% capture ratenya)
      - Menurunkan escape rate jadi
        0% sehingga Pokemon tidak
        bisa lari
      - 60 10 Yes No
        
   2. Pokeball 
       - Menangkap pokemon 
       - 5 - Yes No
   3. Berry 
       - Meningkatkan AP semua pokemon yang ada di pokedex sebesar +10
       - 15 - No Yes

5. Gunakan thread untuk implementasi lullaby powder dibuatkan
masing-masing 1 thread.

iii. Menyediakan Random Pokemon (Gunakan Thread)
1. Setiap tipe pokemon memiliki peluang 1/8000 untuk jadi shiny
pokemon. (Random dulu antara normal, rare, legendary sesuai
rate mereka, baru setelah itu di random dengan peluang
1/8000 untuk tahu dia shiny atau tidak).
2. Shiny Pokemon meningkatkan escape rate sebesar +5%
(misal: tipe normal jadi 10%), capture rate berkurang menjadi
-20% (misal: tipe rare jadi 30%), dan pokedollar dari melepas
+5000 (misal: tipe legendary jadi 5200 pokedollar).
3. Setiap 1 detik thread ini akan mengkalkulasi random ulang lagi
untuk nantinya diberikan ke soal2_traizone.

| No-Pokemon | Type | Encounter-Rate | Escape-Rate | Capture-Rate | Pokedollar-dari-melepas |
List Nama Pokemon
(random) |

1. Normal 80% 5% setiap 20 detik 70% 80 
● Bulbasaur
● Charmander
● Squirtle
● Rattata
● Caterpie

2. Rare 15% 10% setiap 20 detik 50% 100 
● Pikachu
● Eevee
● Jigglypuff
● Snorlax
● Dragonite

3. Legendary 5% 20% setiap 20 detik 30% 200 
● Mew
● Mewtwo
● Moltres
● Zapdos
● Articuno

### Penyelesaian


## SOAL 2

TapTap Game adalah game online berbasis text console. Terdapat 2 program yaitu
tapserver.c dan tapplayer.c
Syarat :
- Menggunakan Socket, dan Thread
Hint :
- fwrite, fread
Spesifikasi Game :

CLIENT SIDE

Screen 1 :
1. Login
2. Register
Choices : {your input}
★ Pada screen 1 kalian dapat menginputkan “login”, setelah menekan enter
anda diminta untuk menginputkan username dan password seperti berikut
Screen 1 :
1. Login
2. Register
Choices : login
Username : { ex : qiqi }
Password : { ex : aku nggak marah!! }
- Jika login berhasil maka akan menampilkan pesan “login success”, jika gagal
akan menampilkan pesan “login failed” (pengecekan login hanya mengecek
username dan password, maka dapat multi autentikasi dengan username dan
password yang sama)
- Pada screen 1 kalian juga dapat menginputkan “register”, setelah menekan
enter anda diminta untuk menginputkan username dan password sama
halnya seperti login
- Pada register tidak ada pengecekan unique username, maka setelah register
akan langsung menampilkan pesan “register success” dan dapat terjadi
double account
- Setelah login berhasil maka anda berpindah ke screen 2 dimana
menampilkan 2 fitur seperti berikut.

Screen 2 :
1. Find Match
2. Logout
Choices : {your input}
- Pada screen 2 anda dapat menginputkan “logout” setelah logout anda akan
kembali ke screen 1
- Pada screen 2 anda dapat menginputkan “find”, setelah itu akan
menampilkan pesan “Waiting for player ...” print terus sampai menemukan
lawan
- Jika menemukan lawan maka akan menampilkan pesan “Game dimulai
silahkan tap tap secepat mungkin !!”
- Pada saat game dimulai diberikan variable health = 100,dan anda dapat
men-tap (menekan space pada keyboard tanpa harus menekan enter)
- Pada saat anda men-tap maka akan menampilkan pesan “hit !!”, dan pada
lawan healthnya akan berkurang sebanyak 10 kemudian pada lawan
menampilkan pesan status healthnya sekarang. (conclusion : anda tidak bisa
melihat status health lawan)
- Jika health anda <= 0 maka akan menampilkan pesan “Game berakhir kamu
kalah”, apabila lawan anda healthnya <= 0 maka akan menampilkan pesan
”Game berakhir kamu menang”
- Setelah menang atau kalah maka akan kembali ke screen 2

SERVER SIDE

- Pada saat program pertama kali dijalankan maka program akan membuat file
akun.txt jika file tersebut tidak ada. File tersebut digunakan untuk menyimpan
username dan password
- Pada saat user berhasil login maka akan menampilkan pesan “Auth success” jika
gagal “Auth Failed”
- Pada saat user sukses meregister maka akan menampilkan List account yang
terdaftar (username dan password harus terlihat)

### Penyelesaian
--- CLIENT SIDE ---
Berikut ini merupakan kode dari `tapplayer.c` untuk menjalankan client side.
```
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
pthread_t temp;
int health = 100;
int game = 0;
static struct termios oldt, newt;

void* tapdetect(void *arg) {
    temp = pthread_self();
    int sock = *(int *)arg;
    int c;   
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON);          
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);   // Merubah
    while(game == 1) {   
        c = getchar();
        // putchar(c);
        if(c == ' ') {
            send(sock, "hit", 3, 0);
            printf("hit !!\n");
        }  
    }             

    return NULL;
}

void* healthdetect(void *arg) {
    int sock = *(int *)arg;
    int valread;
    char msg[1024];
    while(1) {
        memset(msg, 0, 1024);
        valread = read( sock , msg, 1024);
        // printf("msg %s\n", msg);
        if(strcmp(msg, "minus") == 0) {
            health -= 10;
            printf("Health %d\n", health);
        }
        if(health == 0)
        {
            // printf("sock %d kirim sinyal kalah\n", sock);
            send(sock , "die", strlen("die"), 0 );
            game = 0;
            tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
            pthread_cancel(temp);
            pthread_cancel(pthread_self());
            break;
        }
        if(strcmp(msg, "stop") == 0) {
            // printf("masuk stop\n");
            game = 0;
            tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
            pthread_cancel(temp);
            pthread_cancel(pthread_self());
            break;
        }
    }
    return NULL;
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
                game = 1;
                pthread_create(&(tid[0]), NULL, tapdetect, &sock);
                pthread_create(&(tid[1]), NULL, healthdetect, &sock);
                pthread_join(tid[0], NULL);
                pthread_join(tid[1], NULL);

                send(sock , "hasil", strlen("hasil"), 0 );

                memset(buffer, 0, 1024);
                valread = read(sock , buffer, 1024);
                if(strcmp(buffer, "menang") == 0) {
                    printf("Game berakhir kamu menang\n");
                }
                if(strcmp(buffer, "kalah") == 0) {
                    printf("Game berakhir kamu kalah\n");
                }

                screen = 2;
                health = 100;
                // printf("screen %d health refresh %d\n", screen, health);
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
```
Berikut ini merupakan bagian kode untuk menjalan screen 1 pada client side dimana
client akan dimintai inputan untuk login atau register. Setiap login atau register
akan dimintai username dan password.
```
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
```
Sedangkan untuk screen 2, berikut merupakan bagian kode yang menampilkan
menu pilihan untuk find match atau logout. Jika client memilih find match maka
akan menunggu hingga mendapatkan pasangan match dan game akan dimulai jika sudah 
mendapatkan pasangan. Jika client memilih untuk logout, maka client akan diarahkan
kembali menuju screen 1.
```
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
      game = 1;
      pthread_create(&(tid[0]), NULL, tapdetect, &sock);
      pthread_create(&(tid[1]), NULL, healthdetect, &sock);
      pthread_join(tid[0], NULL);
      pthread_join(tid[1], NULL);

      send(sock , "hasil", strlen("hasil"), 0 );

      memset(buffer, 0, 1024);
      valread = read(sock , buffer, 1024);
      if(strcmp(buffer, "menang") == 0) {
          printf("Game berakhir kamu menang\n");
      }
      if(strcmp(buffer, "kalah") == 0) {
          printf("Game berakhir kamu kalah\n");
      }

      screen = 2;
      health = 100;
      // printf("screen %d health refresh %d\n", screen, health);
      memset(buffer, 0, 1024);
  }
  if(strcmp(commb, "logout") == 0) {
      memset(commb, 0, 10);
      screen = 1;
  }
}
```
Ketika game dimulai, pada client ini akan membuat 2 thread dimana thread pertama
akan menghandle inputan client yaitu spacebar, sedangkan thread kedua akan
menghandle penerimaan buffer dari server apabila lawan main menyerang dan akan mengurangi
health pemain. Setelah game berakhir, maka akan ditampilkan hasil dari game tersebut.


--- SERVER SIDE ---
Berikut ini merupakan kode dari `tapserver.c` untuk menjalankan server side.
```
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
int kalah;

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
            // printf("Pertama : %s\n", buffer);
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
            // printf("Kedua : %s\n", buffer);
            if(strcmp(buffer, "find") == 0) {
                user++;
                // printf("user ada %d\n", user);
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
                            send(id_sock[1], "stop", 4, 0);
                            kalah = id_sock[0];
                        }
                        if(new_socket == id_sock[1])
                        {
                            send(id_sock[0], "stop", 4, 0);
                            kalah = id_sock[1];
                        }
                        break;
                    }
                }

                memset(buffer, 0, 1024);
                valread = read( new_socket, buffer, 1024);
                if(strcmp(buffer, "hasil") == 0) {
                    if(kalah == id_sock[0])
                    {
                        send(id_sock[1], "menang", 6, 0);
                        send(id_sock[0], "kalah", 5, 0);
                    }
                    if(kalah == id_sock[1])
                    {
                        send(id_sock[0], "menang", 6, 0);
                        send(id_sock[1], "kalah", 5, 0);
                    }
                }
                
                screen = 2;
                user = 0;
            }
            if(strcmp(buffer, "logout") == 0) {
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
```
Setiap client yang connect akan dijalankan oleh satu thread sendiri agar bisa multiclient.
Fungsi tersebut diatur oleh bagian kode berikut. Socket dari masing - masing client akan
dipassing ke fungsi yang dijalankan masing - masing thread.
```
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
```
Berikut merupakan bagian kode yang akan menghandle apabila login success dan register success.
Pada server side akan menampilkan " Auth success" apabila login dari client success. Apabila
login gagal maka server akan menampilkan "Auth failed". Untuk register, maka server akan membuka
file penampung nama dan username yang sudah didaftarkan dan akan ditampilkan melalui server side.
```
if(screen == 1) {
  memset(buffer, 0, 1024);
  valread = read( new_socket, buffer, 1024);
  // printf("Pertama : %s\n", buffer);
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
```
Pada bagian kode berikut, server akan mengatur permainan dari kedua client yang melakukan find match.
Ketika game dimulai, apabila client 1 menyerang maka buffer yang dikirim dari client 1 akan dikirim 
ke client 2 dan sebaliknya. Server akan menunggu buffer dari salah satu client yang kalah dan akan mengirim
buffer yang berisi hasil pemenang dari game.
```
if(screen == 2) {
  memset(buffer, 0, 1024);
  valread = read( new_socket, buffer, 1024);
  // printf("Kedua : %s\n", buffer);
  if(strcmp(buffer, "find") == 0) {
      user++;
      // printf("user ada %d\n", user);
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
                  send(id_sock[1], "stop", 4, 0);
                  kalah = id_sock[0];
              }
              if(new_socket == id_sock[1])
              {
                  send(id_sock[0], "stop", 4, 0);
                  kalah = id_sock[1];
              }
              break;
          }
      }

      memset(buffer, 0, 1024);
      valread = read( new_socket, buffer, 1024);
      if(strcmp(buffer, "hasil") == 0) {
          if(kalah == id_sock[0])
          {
              send(id_sock[1], "menang", 6, 0);
              send(id_sock[0], "kalah", 5, 0);
          }
          if(kalah == id_sock[1])
          {
              send(id_sock[0], "menang", 6, 0);
              send(id_sock[1], "kalah", 5, 0);
          }
      }

      screen = 2;
      user = 0;
  }
  if(strcmp(buffer, "logout") == 0) {
      memset(buffer, 0, 1024);
      screen = 1;
  }
}
```

## SOAL 3

Buatlah sebuah program dari C untuk mengkategorikan file. Program ini akan
memindahkan file sesuai ekstensinya (tidak case sensitive. JPG dan jpg adalah
sama) ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working
directory ketika program kategori tersebut dijalankan.
- Semisal program dijalankan:
   ```
          # File kategori terletak di /home/izone/kategori
          $ ./kategori -f path/to/file1.jpg path/to/file2.c path/to/file3.zip
          
          #Hasilnya adalah sebagai berikut
          /home/izone
          |-jpg
          |--file1.jpg
          |-c
          |--file2.c
          |-zip
          |--file3.zip
   ```
- Pada opsi -f tersebut, user bisa menambahkan argumen file yang bisa
dikategorikan sebanyak yang user inginkan seperti contoh di atas.
Pada program kategori tersebut, folder jpg,c,zip tidak dibuat secara manual,
melainkan melalui program c. Semisal ada file yang tidak memiliki ekstensi,
maka dia akan disimpan dalam folder “Unknown”.
- Program kategori ini juga menerima perintah (*). Artinya mengkategori seluruh file yang ada di 
working directory ketika menjalankan program C tersebut. Hasilnya perintah di atas adalah mengkategorikan 
file di /path/to/directory dan hasilnya akan disimpan di working directory di mana program C tersebut
berjalan (hasil kategori filenya bukan di /path/to/directory).
- Program ini tidak rekursif. Semisal di directory yang mau dikategorikan, atau
menggunakan (*) terdapat folder yang berisi file, maka file dalam folder
tersebut tidak dihiraukan, cukup file pada 1 level saja.
- Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan
secara paralel sehingga proses kategori bisa berjalan lebih cepat. Dilarang
juga menggunakan fork-exec dan system.

### Penyelesaian
Berikut merupakan kode program dari `kategori.c` untuk mengkategorikan file dimana program ini akan memindahkan 
file sesuai ekstensinya (tidak case sensitive) ke dalam folder sesuai ekstensinya dan folder 
hasilnya akan terdapat di working directory ketika program kategori tersebut dijalankan.

```
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
```
Penjelasan :
```
int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}
```
Fungsi di atas ini merupakan fungsi untuk mengecek apakah sebuah file yang akan diakses merupakan 
sebuah file atau sebuah direktori karena pada soal ini yag diminta adalah mengkategorikan sebuah file bukan direktori.
```
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
```
Fungsi  di atas merupakan fungsi yang saya gunakan dalam thread untuk mengkategorikan sebuah file.
Fungsi ini digunakan ketika argumen opsi yang diberikan adalah `-f` atau `\*`. Fungsi ini dapat mendapatkan
ekstensi dari sebuah file, nama file, dan memindahkan file. Fungsi memindahkan file terdapat pada bagian berikut :
```
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
```
Dimana bagian ini akan membuka kedua path yang sudah kita dapatkan sebelumnya dimana file lama dibuka
dalam mode read dan file baru yang akan dibuat dalam mode write. Lalu kita akan memindahkan semua isi
konten yang ada pada file lama dengan menggunakan `fputc( )` . Setelah memindahkan isi file lama, maka
kita menghapus file lama dengan `remove( )`.
```
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
```
Fungsi di atas juga merupakan fungsi untuk memindahkan file tetapi fungsi ini akan menyimpan current working
directory dimana kode c bekerja. Lalu kita akan memindahkan semua file yang telah dikategorikan menuju
tempat file c bekerja. Fungsi ini digunakan pada argumen opsi `-d` .
```
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
``` 
Kode di atas ini merupakan fungsi main pada program c tersebut dimana setiap file yang diakses akan
dijalankan oleh masing - masing thread. Satu file dipegang oleh satu thread.

Untuk menghandle argumen yang diberikan salah dengan cara :
- `if(strcmp(argv[1], "-f") == 0) { ... }` untuk argumen dengan opsi `-f`
- `else if(strcmp(argv[1], "*") == 0 && argc == 2) { ... }` untuk argumen dengan opsi `\*`
- `else if(strcmp(argv[1], "-d") == 0 && argc == 3) { ... }` untuk argumen dengan opsi `-d`
- `else { printf("Option or arguments are not valid\n"); }` untuk argumen selain opsi yang diminta.

## SOAL 4

Norland adalah seorang penjelajah terkenal. Pada suatu malam Norland menyusuri
jalan setapak menuju ke sebuah gua dan mendapati tiga pilar yang pada setiap
pilarnya ada sebuah batu berkilau yang tertancap. Batu itu berkilau di kegelapan dan
setiap batunya memiliki warna yang berbeda.
Norland mendapati ada sebuah teka-teki yang tertulis di setiap pilar. Untuk dapat
mengambil batu mulia di suatu pilar, Ia harus memecahkan teka-teki yang ada di
pilar tersebut. Norland menghampiri setiap pilar secara bergantian.
- Batu mulia pertama. Emerald. Batu mulia yang berwarna hijau mengkilat. Pada
batu itu Ia menemukan sebuah kalimat petunjuk. Ada sebuah teka-teki yang berisi:
1. Buatlah program C dengan nama "4a.c", yang berisi program untuk
melakukan perkalian matriks. Ukuran matriks pertama adalah 4x2, dan
matriks kedua 2x5. Isi dari matriks didefinisikan di dalam kodingan. Matriks
nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka).
2. Tampilkan matriks hasil perkalian tadi ke layar.

- Batu kedua adalah Amethyst. Batu mulia berwarna ungu mengkilat. Teka-tekinya
adalah:

1. Buatlah program C kedua dengan nama "4b.c". Program ini akan
mengambil variabel hasil perkalian matriks dari program "4a.c" (program
sebelumnya), dan tampilkan hasil matriks tersebut ke layar.
(Catatan!: gunakan shared memory)
2. Setelah ditampilkan, berikutnya untuk setiap angka dari matriks
tersebut, carilah nilai faktorialnya, dan tampilkan hasilnya ke layar dengan
format seperti matriks.

Contoh: misal array [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], ...],

maka:

1 2 6 24
120 720 ... ...
...

(Catatan! : Harus menggunakan Thread dalam penghitungan
faktorial)
- Batu ketiga adalah Onyx. Batu mulia berwarna hitam mengkilat. Pecahkan
teka-teki berikut!

1. Buatlah program C ketiga dengan nama "4c.c". Program ini tidak
memiliki hubungan terhadap program yang lalu.
2. Pada program ini, Norland diminta mengetahui jumlah file dan
folder di direktori saat ini dengan command "ls | wc -l". Karena sudah belajar
IPC, Norland mengerjakannya dengan semangat.
(Catatan! : Harus menggunakan IPC Pipes)
Begitu batu terakhir berhasil didapatkan. Gemuruh yang semakin lama semakin
besar terdengar. Seluruh tempat berguncang dahsyat, tanah mulai merekah. Sebuah
batu yang di atasnya terdapat kotak kayu muncul ke atas dengan sendirinya.

Sementara batu tadi kembali ke posisinya. Tanah kembali menutup, seolah tidak
pernah ada lubang merekah di atasnya satu detik lalu.
Norland segera memasukkan tiga buah batu mulia Emerald, Amethys, Onyx pada
Peti Kayu. Maka terbukalah Peti Kayu tersebut. Di dalamnya terdapat sebuah harta
karun rahasia. Sampai saat ini banyak orang memburu harta karun tersebut.
Sebelum menghilang, dia menyisakan semua petunjuk tentang harta karun tersebut
melalui tulisan dalam buku catatannya yang tersebar di penjuru dunia. "One Piece
does exist".

### Penyelesaian

