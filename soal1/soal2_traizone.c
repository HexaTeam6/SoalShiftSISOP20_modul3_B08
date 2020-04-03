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

int isCaptMode = 0;
int Upokeball=10, Uberry=10, Upowder=10;

struct Node { 
	int id;
    char nama[10];
    char type[15];
    int AP;
	struct Node* next; 
}; 

void push(struct Node** head_ref, int id, char nama[], char type[]) { 
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
  
    new_node->id = id;
    strcpy(new_node->nama, nama);
    strcpy(new_node->type, type);
    new_node->AP = 10;

    new_node->next = (*head_ref); 
  
    (*head_ref) = new_node; 
} 

void printList(struct Node* n) { 
	while (n->next != NULL) { 
		printf("%d \t %s \t %s \t %d\n", n->id, n->nama, n->type, n->AP); 
		n = n->next; 
	} 
} 

int getCount(struct Node* head)  {  
    int count = 0;   
    struct Node* current = head;   
    while (current->next != NULL)  {  
        count++;  
        current = current->next;  
    }  
    return count;  
} 

// pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
// int play = 0;
pthread_mutex_t isGet;
int capturedPokemon, usingPowder, getPokemon, fitur=1;
pthread_t tid[3];
int *pokemonId;

void* escPokemon() {
    int escRate = (capturedPokemon % 15) / 5;
    //normal esc
    if (escRate == 0) escRate = 5;
    //rare esc
    else if (escRate == 1) escRate = 10;
    //legendary esc
    else if (escRate == 2) escRate = 20;
    //shiny pokemon
    if (capturedPokemon >= 15) escRate += 5;
    while (1) {
        sleep(20);
        if (usingPowder) continue;
        if (rand() % 100 < escRate) {
            printf("Pokemon telah escape.\n");
            pthread_mutex_lock(&isGet);
            capturedPokemon = -1;
            pthread_mutex_unlock(&isGet);
            pthread_exit(0);
        }
    }
}

void* CariPokemon(void *arg){
    pthread_t id=pthread_self();
    if(!pthread_equal(id,tid[0])) return NULL;

    sleep(10);
    while (isCaptMode){
        // printf("capt!!!\n");
        if (rand()%10<6){
            // printf("get!!!\n");
            isCaptMode=0;
            getPokemon=1;
            fitur=2;
            pthread_mutex_lock(&isGet);
            //get pokemon id
            capturedPokemon = *pokemonId;
            pthread_mutex_unlock(&isGet);
            pthread_create(&tid[1], NULL, escPokemon,NULL);
            // pthread_cancel(inputthread);
            pthread_exit(0);
        }
        
    }
    
}

void Pokedex(struct Node* pokedex){
    printList(pokedex);
    printf("%d", getCount(pokedex));
}

int main() { 
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    pokemonId = shmat(shmid, NULL, 0);

    struct Node* pokedex = NULL; 
	pokedex = (struct Node*)malloc(sizeof(struct Node)); 
    push(&pokedex, 1, "Pikachu", "Rare");
    push(&pokedex, 2, "Pikachu", "Rare");
    push(&pokedex, 3, "Pikachu", "Rare");
    push(&pokedex, 4, "Pikachu", "Rare");

    srand(time(NULL));

    int nMenu;
    while (1){
        if (getPokemon) continue;
        
        if(fitur==1){
            printf(isCaptMode? "[1]Berhenti mencari\n" : "[1]Cari Pokemon\n");
            printf("[2]Pokedex\n");
            printf("[3]Shop\n");
            scanf("%d", &nMenu);

            if (nMenu==1 && isCaptMode==0){
                isCaptMode=1;
                pthread_create(&(tid[0]),NULL,CariPokemon,NULL);
            }
            else if (nMenu==2){
                Pokedex(pokedex);
            }
            else if (nMenu==3){
                
            }
        }
        else if (fitur==2){
            printf("[1]Tangkap\n");
            printf("[2]Item\n");
            printf("[3]Keluar\n");
        }
        
    }

	return 0; 
}