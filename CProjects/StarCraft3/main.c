#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define NUM_MINERALS_MAP 5000
#define NUM_MAX_SOLDIERS 20
#define NUM_SCV_WORKERS 180
#define NUM_MAX_COMMAND_CS 20

// Ostana mi samo da dobavq obshtata promenliva za resursa s kojto razpolagame v momenta
// Da dobavq #define za nqkoi, kato 500, 20 i chisla, koito mnogo izpolzvam.

pthread_mutex_t lock_mining;
pthread_mutex_t lock_cc[NUM_MAX_COMMAND_CS]; // lock_command_center

int minerals_on_map = NUM_MINERALS_MAP; // Минерали на картата
int current_mineral_for_use = 0; // Минералите, които сме добили и не сме използвали
int number_of_command_cs; // Брой на командните центрове
int array_of_command_cs[NUM_MAX_COMMAND_CS]; // Масив на всички командни центрове
int mined_minerals = 0; // Отчита добитите минерали в играта
int soldiers = 0; // Показва броя на създадените войници (макс 20 войника)

int num_of_scv;
pthread_t scv_threads[NUM_SCV_WORKERS];

// Отбелязваме че има такива функции
void remaining_minerals(); // Покава колко минерала остават на картата
void command_center_init(); // Създава първия команден център
void create_command_center(); // Създаване на команден център
void summon_soldier(); // Служи за създаване на войник

void *scv();
void scv_init(); // Служи за направата на 5 работника
void scv_terran_worker(); //  Служи за направата на работник
void *scv_working(void *); // Показва чрез една функция работата, която върши работника
void scv_mining_minerals(size_t *); // Служи да покаже, че работник копае
void scv_transporting_minerals(size_t *); // Служи да покаче че работник транспортира минерали
void scv_delivering_minerals(size_t *); // Служи да покаче, че работник доставя минерали
//void print(SCVs *);
void *use_scanf(); // Служи за използването на scanf в нишка само за него

// Показва минералите оставащи на картата
void remaining_minerals(){ // Ramaining Мinerals
  printf("Ramaining minerals: %d\n", minerals_on_map);
}

// Създава първия команден център
void command_center_init(){
	number_of_command_cs = 1;
	//int *array_of_command_cs = (int*)malloc(sizeof(int) * number_of_command_cs);
  array_of_command_cs[0] = 0;
  printf("Number of Command centars: %d\n", number_of_command_cs);
}

// Служи за направата на команден център
void create_command_center(){
  if(current_mineral_for_use >= 400){
  current_mineral_for_use -= 400;
  number_of_command_cs += 1;
  array_of_command_cs[number_of_command_cs-1] = 0;
  sleep(2);
  printf("Command center %d created.\n", number_of_command_cs);
  }
  else{
    printf("Not enough minerals.\n");
  }
}

// Служи за създаване на войник
void summon_soldier(){ // Summon a Soldier!
  if (current_mineral_for_use >= 50 && soldiers < NUM_MAX_SOLDIERS-1){
    sleep(1);
    current_mineral_for_use -= 50;
    soldiers += 1;
    printf("You wanna piece of me, boy?\n");
  }
  else if(current_mineral_for_use < 50){
    printf("Not enough minerals.\n");
  }
  else if(soldiers == NUM_MAX_SOLDIERS-1){
    sleep(1);
    current_mineral_for_use -= 50;
    soldiers += 1;
    printf("You wanna piece of me, boy?\n");
    printf("You win the game! (You have 20 soldiers)\n");
    exit(0);
  }
  printf("Soldiers: %d\n", soldiers);
}


void *scv(){
  int i; //index
  for(i = 0; i < NUM_MAX_COMMAND_CS; i++)
  pthread_mutex_init(&lock_cc[i], NULL);
  pthread_mutex_init(&lock_mining, NULL);
  while(1){
    int i; //index
    for(i = 0; i < num_of_scv; i++)
    {
      int error = pthread_create(&scv_threads[i], NULL, scv_working, (void *)(i+1)); //Default Attributes
      if (error != 0) {
        fprintf(stderr, "Error creating thread %d: error: %d\n", i, error);
      }
    }
    for(i = 0; i < num_of_scv; i++){
      pthread_join(scv_threads[i], NULL);
    }
  }
  for(i = 0; i < NUM_MAX_COMMAND_CS; i++)
  pthread_mutex_destroy(&lock_cc[i]); // nz dali trqbva da e tuk
  pthread_mutex_destroy(&lock_mining); // nz dali trqbva da e tuk
  return 0;
}

// Служи за направата на 5 работника
void scv_init(){ // Initialize 5 SCV workers
  num_of_scv = 5;
  // scv_threads = (pthread_t *)malloc(num_of_scv * sizeof(pthread_t ));
}

// Служи за направата на работник
void scv_terran_worker(){
  if(current_mineral_for_use >= 50){
    num_of_scv += 1;
    current_mineral_for_use -= 50;
    sleep(1);
		printf("SCV good to go, sir.\n");
  }
  else{
    printf("Not enough minerals.\n");
  }
}

// Показва чрез една функция работата, която върши работника
void *scv_working(void *idx_thread){
  size_t index_thread;
  index_thread = (size_t)idx_thread;

  scv_mining_minerals(&index_thread);
  scv_transporting_minerals(&index_thread);
  scv_delivering_minerals(&index_thread);
  return 0;
}

// Служи да покаже, че работник копае минерали
void scv_mining_minerals(size_t *idx_scv){
  // Take minerals from the mount - (8 minerals)
	pthread_mutex_lock(&lock_mining); // ne trqbva da gi ima po uslovie
    printf("SCV %d is mining\n", *idx_scv);
    minerals_on_map -= 8; // Mining 8 minerals
    printf("%d minerals\n", minerals_on_map);
    if(minerals_on_map == 0){
      scv_transporting_minerals(idx_scv);
      scv_delivering_minerals(idx_scv);
      sleep(3);
      printf("You lose the game! (You have not 20 soldiers)\n");
      exit(0);
    }
	pthread_mutex_unlock(&lock_mining);
}

// Служи да покаче, че работник транспортира минерали
void scv_transporting_minerals(size_t *idx_scv){
  // Transport minerals (use sleep();)
  printf("SCV %d is transporting minerals\n", *idx_scv);
  sleep(2);
}

// Служи да покаче, че работник доставя минерали
void scv_delivering_minerals(size_t *idx_scv){
  // Delivering minerals to first free
  // no (sleep();) here - when we chose Command Center...
  //printf("Kak sme tuka??? yey: %zd\n", number_of_command_cs);
  //pthread_mutex_lock(&lock_scv);
  int i; // current command center index
  int cheker = 0;
  while(1){
    for(i = 0; i < number_of_command_cs; i++){
      if(pthread_mutex_trylock(&lock_cc[i]) == 0){
        array_of_command_cs[i] += 8;
        mined_minerals += 8;
        current_mineral_for_use += 8;
        printf("SCV %d delivered minerals to Command center %d\n", *idx_scv, i+1);
        //printf("Minerals in Command center %zd: %d\n", number_of_command_cs, array_of_command_cs[0]);
        printf("Minerals in Command center %d: %d\n",i+1 , array_of_command_cs[i]);
        printf("Minerals in Current Minerals: %d\n", current_mineral_for_use);
        pthread_mutex_unlock(&lock_cc[i]);
        cheker = 1;
        break;
      }
    }
    if(cheker == 1)
    break;
    sleep(1);
  }
  // da se dobavi i che trqbva da se izchaka sled kato vsichki komandni centrove sa zaeti
  // i da se proveri pak sleep(1);
}



// ISKAM DA NAPTAVQ SCANF V DRUGA NISHKA ZA DA MOJE TQ DA SI RABOTI BEZ DA ZASQGA MAIN NISHKATA
void *use_scanf(){
	while(1){
    char input[256];
    scanf("%s" , input);
      // Summon Soldier
    if (strcmp(input, "m") == 0){
      summon_soldier();
      // Summon SCV workers
    } else if(strcmp(input, "s") == 0){
      scv_terran_worker();
      // Build Command center
    } else if(strcmp(input, "c") == 0){
      create_command_center();
    }
  }
}


int main(){

	command_center_init();
	scv_init();


	pthread_t scanf_thread;
	pthread_t scv_thread;

  int error1 = pthread_create(&scanf_thread, NULL, use_scanf, NULL); //Default Attributes
  if (error1 != 0) {
    fprintf(stderr, "Error creating thread: scanf_thread!");
  }

	int error2 = pthread_create(&scv_thread, NULL, scv, NULL); //Default Attributes
  if (error2 != 0) {
    fprintf(stderr, "Error creating thread: scv_thread!");
  }

	pthread_join(scanf_thread, NULL);
	pthread_join(scv_thread, NULL);


  // Remaining Minerals
  // remaining_minerals();

  // Mined Minerals
  printf("Mined minerals: %d\n", mined_minerals);

  // Command centers
  // command_center_init();

  return 0;
}
