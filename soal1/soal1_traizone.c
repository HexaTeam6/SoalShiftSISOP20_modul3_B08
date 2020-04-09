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
#include <signal.h>

char* pokemonList[30] = {
    "Bulbasaur",
    "Charmander",
    "Squirtle",
    "Rattata",
    "Caterpie",
    "Pikachu",
    "Eevee",
    "Jigglypuff",
    "Snorlax",
    "Dragonite",
    "Mew",
    "Mewtwo",
    "Moltres",
    "Zapdos",
    "Articuno",
    "Shiny Bulbasaur",
    "Shiny Charmander",
    "Shiny Squirtle",
    "Shiny Rattata",
    "Shiny Caterpie",
    "Shiny Pikachu",
    "Shiny Eevee",
    "Shiny Jigglypuff",
    "Shiny Snorlax",
    "Shiny Dragonite",
    "Shiny Mew",
    "Shiny Mewtwo",
    "Shiny Moltres",
    "Shiny Zapdos",
    "Shiny Articuno"
};
int pokemon[7];
int pokemonAP[7];
int powder=0;
int pokeball=0;
int berry=0;
int pokedollar=500; // money money money !
int pokeslot=-1;

int mencari=0; //status saat mencari
int mode=0; //status normal atau capture
int id_pokemon=-1; //id pokemon yang didapat
int menu=-1; //pilih menu
int m_powder=0; //menggunakan powder

pthread_t threadcari; //thread mencari pokemon
pthread_t threadcapture; //thread mencari pokemon
pthread_t powderthread; //thread menggunakan powder
pthread_t pokemonthread[7]; //set pokemon when AP is low

pthread_mutex_t pokemoncapturewrite;
pthread_mutex_t pokeslotwrite;
pthread_mutex_t pokemonwrite;

int shmidp;
int shmp;
int shmpb; 
int shmb;

int *shm_id_pokemon;
int *shm_powder;
int *shm_pokeball;
int *shm_berry;

void pokedex();
void shop();
void tangkap();
void useitem();
void cleanup();

void *fthreadcapture(){
    int thres = (id_pokemon % 15) / 5;
    if (thres == 0) thres = 5; //normal
    else if (thres == 1) thres = 10; //rare
    else if (thres == 2) thres = 20; //legendary
    if (id_pokemon >= 15) thres += 5; //shiny
    while (1){
        sleep(20);
        if (m_powder) continue;
        if (rand() % 100 < thres) {
            printf("Pokemon telah escape dari pencarian pokemon.\n");
            pthread_mutex_lock(&pokemoncapturewrite);
            id_pokemon = -1;
            pthread_mutex_unlock(&pokemoncapturewrite);
            pthread_exit(0);
        }
    }
}

void *fthreadcari(){
    while (1){
        sleep(10);
        if (rand() % 100 < 60){ //60% get pokemon
            // printf("get\n");
            mencari = 0;
            pthread_mutex_lock(&pokemoncapturewrite);
            id_pokemon = *shm_id_pokemon;
            pthread_mutex_unlock(&pokemoncapturewrite);
            pthread_create(&threadcapture, NULL, fthreadcapture, NULL);
            mencari = 0;
            mode = 1;
            menu = -1;
            // pthread_cancel(inputthread);
            pthread_exit(0);
        }
    }
}

void *fpokemonthread(){
    int slot = pokeslot;
    pthread_mutex_unlock(&pokeslotwrite);
    while (1){
        sleep(10);
        if (mode == 1) continue;
        pthread_mutex_lock(&pokemonwrite);
        pokemonAP[slot] -= 10;
        if (pokemonAP[slot] == 0){
            if (rand() % 100 < 90){
                printf("Ada pokemon yang terlepas.\n");
                pokemon[slot] = -1;
                pokemonAP[slot] = -1;
                pthread_exit(0);
            }
            else pokemonAP[slot] = 50;
        }
        pthread_mutex_unlock(&pokemonwrite);
    }
}

void *fpowderthread(){
    while (1) sleep(10);
    m_powder = 0;
    printf("Efek lullaby powder habis.\n");
    pthread_exit(0);
}

int main() { 
    srand(time(NULL));
    signal(SIGINT, cleanup);
    key_t key1 = 1000;
    key_t key2 = 1001;
    key_t key3 = 1002;
    key_t key4 = 1003;

    shmidp = shmget(key1, sizeof(int), IPC_CREAT | 0666);
    shmp = shmget(key2, sizeof(int), IPC_CREAT | 0666);
    shmpb = shmget(key3, sizeof(int), IPC_CREAT | 0666);
    shmb = shmget(key4, sizeof(int), IPC_CREAT | 0666);

    shm_id_pokemon = shmat(shmidp, NULL, 0);
    shm_powder = shmat(shmp, NULL, 0);
    shm_pokeball = shmat(shmpb, NULL, 0);
    shm_berry = shmat(shmb, NULL, 0);

    id_pokemon = -1;
    memset(pokemon, -1, sizeof(pokemon));
    memset(pokemonAP, -1, sizeof(pokemonAP));
    memset(pokemonthread, 0, sizeof(pokemonthread));

    pthread_mutex_init(&pokemonwrite, NULL);
    pthread_mutex_init(&pokemoncapturewrite, NULL);
    pthread_mutex_init(&pokeslotwrite, NULL);
    
    while (1) {
        printf("\n");
        if (mode == 0){
            if (mencari)
                printf("----Normal Mode----\n[1]. Berhenti Mencari\n[2]. Pokedex\n[3]. Shop\n[4]. Go to capture mode\n");
            else
                printf("----Normal Mode----\n[1]. Cari Pokemon\n[2]. Pokedex\n[3]. Shop\n");
        }
        else if (mode == 1)
        {
            if (id_pokemon == -1)
                printf("----Capture Mode----\n1. Tangkap\n2. Item\n3. Keluar\nInput: ");
            else
                printf("----Capture Mode----\nMenemukan pokemon: %s\n1. Tangkap\n2. Item\n3. Keluar\nInput: ", pokemonList[id_pokemon]);
        }
        scanf("%d", &menu);
        if (menu == -1) {
            printf("\n");
            continue;
        }
        if (mode == 0) {
            if (menu == 1) {
                mencari = !mencari;
                if (mencari) pthread_create(&threadcari, NULL, fthreadcari, NULL);
                else pthread_cancel(threadcari);
            } 
            else if (menu == 2) {
                pokedex();
            } 
            else if (menu == 3) {
                shop();
            } 
            else if (menu == 4) {
                mode = 1;
            }
        } else if (mode == 1) {
            if (menu == 1) {
                tangkap();
            } 
            else if (menu == 2) {
                useitem();
            } 
            else if (menu == 3) {
                mode = 0;
            }
        }
    }

	return 0; 
}

//menu pokedex
void pokedex(){
    printf("Slot Pokemon Affection Points\n");
    for (int i = 0; i < 7; i++){
        printf("%d", i + 1);
        if (pokemon[i] == -1){
            printf("--\n");
        }
        else{
            printf("%-18s%d\n", pokemonList[pokemon[i]], pokemonAP[i]);
        }
    }
    printf("1. Lepas\n2. Beri semua pokemon Berry\n3. Keluar\nInput: ");
    int x;
    scanf("%d", &x);
    if (x == 1){
        printf("Pilih pokemon (1-7): ");
        int poke = -1;
        while (poke == -1){
            scanf("%d", &poke);
            if (poke >= 1 && poke <= 7 && pokemon[poke - 1] != -1){
                pthread_mutex_lock(&pokemonwrite);
                pthread_cancel(pokemonthread[poke - 1]);
                if (pokemon[poke - 1] >= 15)
                {
                    pokedollar += 5000;
                    pokemon[poke - 1] -= 15;
                }
                if (pokemon[poke - 1] < 5)
                {
                    pokedollar += 80;
                }
                else if (pokemon[poke - 1] < 10)
                {
                    pokedollar += 100;
                }
                else if (pokemon[poke - 1] < 15)
                {
                    pokedollar += 200;
                }
                pokemon[poke - 1] = -1;
                pokemonAP[poke - 1] = 0;
                pthread_mutex_unlock(&pokemonwrite);
                break;
            }
            printf("Input invalid.\n");
        }
    }
    else if (x == 2)
    {
        pthread_mutex_lock(&pokemonwrite);
        for (int i = 0; i < 7; i++)
        {
            if (pokemonAP[i] != -1)
            {
                pokemonAP[i] += 10;
            }
        }
        pthread_mutex_unlock(&pokemonwrite);
        printf("Berhasil memberi berry.\n");
    }
    else if (x == 3)
    {
        return;
    }
}

//menu shop
void shop(){
    printf("Pokedollar: %d\n", pokedollar);
    printf("No\tNama\tPunya\tStok\tHarga\n");
    printf("1\tLullaby Powder\t%-3d\t%-3d\t60\n", powder, *shm_powder);
    printf("2\tPokeball\t%-3d\t%-3d\t5\n", pokeball, *shm_pokeball);
    printf("3\tBerry\t%-3d\t%-3d\t15\n", berry, *shm_berry);
    printf("4 Keluar\n");
    printf("Beli atau keluar: ");
    int x;
    scanf("%d", &x);
    if (x == 4) return;
    printf("Jumlah: ");

    int jml;

    scanf("%d", &jml);
    if (jml > 99){
        printf("Gagal membeli.\n");
        return;
    }
    if (x == 1){
        if (jml <= *shm_powder && powder + jml <= 99 && pokedollar >= jml * 60){
            *shm_powder -= jml;
            pokedollar -= jml * 60;
            powder += jml;
            printf("Berhasil membeli %d Lullaby Powder.\n", jml);
            return;
        }
    }
    else if (x == 2){
        if (jml <= *shm_pokeball && pokeball + jml <= 99 && pokedollar >= jml * 5){
            *shm_pokeball -= jml;
            pokedollar -= jml * 5;
            pokeball += jml;
            printf("Berhasil membeli %d Pokeball.\n", jml);
            return;
        }
    }
    else if (x == 3){
        if (jml <= *shm_berry && berry + jml <= 99 && pokedollar >= jml * 15){
            *shm_berry -= jml;
            pokedollar -= jml * 15;
            berry += jml;
            printf("Berhasil membeli %d Berry.\n", jml);
            return;
        }
    }
    printf("Gagal membeli.\n");
}

//menu tangkap
void tangkap(){
    if (id_pokemon == -1){
        printf("Tidak ada pokemon.\n");
        return;
    }
    if (pokeball == 0){
        printf("Tidak ada pokeball.\n");
        return;
    }
    pokeball--;
    int thres = (id_pokemon % 15) / 5;
    if (thres == 0) thres = 70;
    else if (thres == 1) thres = 50;
    else if (thres == 2) thres = 30;
    if (id_pokemon >= 15) thres -= 20;
    if (m_powder) thres += 20;
    if (rand() % 100 < thres){
        printf("Berhasil menangkap %s!\n", pokemonList[id_pokemon]);
        int slot = -1;
        for (int i = 0; i < 7; i++){
            if (pokemon[i] == -1){
                slot = i;
                break;
            }
        }
        if (slot == -1){
            int money = (id_pokemon % 15) / 5;
            if (money == 0) money = 80;
            else if (money == 1) money = 100;
            else if (money == 2) money = 200;
            if (id_pokemon >= 15) money += 5000;
            pokedollar += money;
            printf("Slot pokemon penuh! Anda mendapatkan %d.\n", money);
        }
        else{
            pthread_mutex_lock(&pokemonwrite);
            pokemon[slot] = id_pokemon;
            pokemonAP[slot] = 100;
            pthread_mutex_unlock(&pokemonwrite);
            pthread_mutex_lock(&pokeslotwrite);
            pokeslot = slot;
            pthread_create(&pokemonthread[slot], NULL, fpokemonthread, NULL);
            pthread_cancel(threadcapture);
            pthread_mutex_lock(&pokemoncapturewrite);
            id_pokemon = -1;
            pthread_mutex_unlock(&pokemoncapturewrite);
        }
    }
    else
    {
        printf("Tidak berhasil menangkap %s.\n", pokemonList[id_pokemon]);
    }
}

// menu use item
void useitem(){
    if (powder <= 0){
        printf("Lullaby Powder tidak cukup.\n");
        return;
    }
    if (m_powder){
        printf("Efek lullaby powder masih ada.\n");
        return;
    }
    printf("Gunakan lullaby powder?\n1. Ya\n2. Tidak\nInput: ");
    int x;
    scanf("%d", &x);
    if (x == 1){
        powder--;
        m_powder = 1;
        pthread_create(&powderthread, NULL, fpowderthread, NULL);
    }
}

//clean up shared memory
void cleanup(){
    shmdt(shm_id_pokemon);
    shmdt(shm_pokeball);
    shmdt(shm_powder);
    shmdt(shm_berry);
    shmctl(shmidp, IPC_RMID, NULL);
    shmctl(shmp, IPC_RMID, NULL);
    shmctl(shmpb, IPC_RMID, NULL);
    shmctl(shmb, IPC_RMID, NULL);
    pthread_mutex_destroy(&pokemonwrite);
    pthread_mutex_destroy(&pokemoncapturewrite);
    pthread_mutex_destroy(&pokeslotwrite);
    exit(EXIT_SUCCESS);
}