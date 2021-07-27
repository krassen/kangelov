//--------------------------------------------
// NAME: Krassen Angelov
// CLASS: XIa
// NUMBER: 14
// PROBLEM: #3
// FILE NAME: star.craft.3.c
// FILE PURPOSE:
// This file serves to be created
// a prototype of StarCraft 3.
//---------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define NUM_MINERALS_MAP 5000
#define NUM_MAX_SOLDIERS 20
#define NUM_SCV_WORKERS 180
#define NUM_MAX_COMMAND_CS 20


pthread_mutex_t lock_mining; // lock mining
pthread_mutex_t lock_cc[NUM_MAX_COMMAND_CS]; // lock command center

int minerals_on_map = NUM_MINERALS_MAP;
int current_mineral_for_use = 0;
int number_of_command_cs;
int array_of_command_cs[NUM_MAX_COMMAND_CS];
int all_mined_minerals = 0;
int soldiers = 0;

int num_of_scv;
pthread_t scv_threads[NUM_SCV_WORKERS];

void original_minerals();
void remaining_minerals();
void mined_minerals();
void delivered_minerals();
void command_center_init();
void create_command_center();
void summon_soldier();

void *scv_all_work();
void scv_init();
void scv_terran_worker();
void *scv_working(void *);
void scv_mining_minerals(size_t *);
void scv_transporting_minerals(size_t *);
void scv_delivering_minerals(size_t *);
void *use_scanf();

//--------------------------------------------
// FUNCTION: original_minerals
// Displays the original number of all minerals on the map.
// PARAMETERS:
// None
//----------------------------------------------
void original_minerals(){
  printf("Number of original minerals on the map: %d\n", NUM_MINERALS_MAP);
}
//--------------------------------------------
// FUNCTION: remaining_minerals
// Displays the number of all remaining minerals on the map.
// PARAMETERS:
// None
//----------------------------------------------
void remaining_minerals(){
  printf("Remaining minerals: %d\n", minerals_on_map);
}

//--------------------------------------------
// FUNCTION: mined_minerals
// Displays the number of all mined minerals.
// PARAMETERS:
// None
//----------------------------------------------
void mined_minerals(){
  printf("Mined minerals: %d\n", all_mined_minerals);
}

//--------------------------------------------
// FUNCTION: delivered_minerals
// Displays the number of all delivered minerals in the Command center/Command centers.
// PARAMETERS:
// None
//----------------------------------------------
void delivered_minerals(){
  int i; // index
  int all_delivered_minerals = 0;
  for(i = 0; i < number_of_command_cs; i++){
    all_delivered_minerals += array_of_command_cs[i];
  }
  printf("All delivered minerals: %d\n", all_delivered_minerals);
}

//--------------------------------------------
// FUNCTION: command_center_init
// Serves to create the first Command center.
// PARAMETERS:
// None
//----------------------------------------------
void command_center_init(){
	number_of_command_cs = 1;
  array_of_command_cs[0] = 0;
  // printf("Number of Command centars: %d\n", number_of_command_cs);
}

//--------------------------------------------
// FUNCTION: create_command_center
// Serves to create a new Command center.
// PARAMETERS:
// None
//----------------------------------------------
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

//--------------------------------------------
// FUNCTION: summon_soldier
// Serves to summon(create) a new soldier.
// PARAMETERS:
// None
//----------------------------------------------
void summon_soldier(){
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
    original_minerals();
    remaining_minerals();
    mined_minerals();
    //delivered_minerals();
    exit(EXIT_SUCCESS);
  }
  // printf("Soldiers: %d\n", soldiers);
}

//--------------------------------------------
// FUNCTION: scv_all_work
// Used to perform all other functions that are necessary
// for implementation of the work of the all workers.
// PARAMETERS:
// None
//----------------------------------------------
void *scv_all_work(){
  int i; //index
  int error_mutex_init;
  for(i = 0; i < NUM_MAX_COMMAND_CS; i++){
    error_mutex_init = pthread_mutex_init(&lock_cc[i], NULL);
    if(error_mutex_init != 0){
      fprintf(stderr, "Error mutex init %d: error: %d\n", i+1, error_mutex_init);
      exit(EXIT_FAILURE);
    }
  }
  error_mutex_init = pthread_mutex_init(&lock_mining, NULL);
  if(error_mutex_init != 0){
    fprintf(stderr, "Error mutex init: lock mining!");
    exit(EXIT_FAILURE);
  }
  while(1){
    int i; //index
    for(i = 0; i < num_of_scv; i++)
    {
      int error_create = pthread_create(&scv_threads[i], NULL, scv_working, (void *)(i+1));
      if (error_create != 0) {
        fprintf(stderr, "Error creating thread %d: error: %d\n", i+1, error_create);
        exit(EXIT_FAILURE);
      }
    }
    for(i = 0; i < num_of_scv; i++)
      pthread_join(scv_threads[i], NULL);
  }
  for(i = 0; i < NUM_MAX_COMMAND_CS; i++)
  pthread_mutex_destroy(&lock_cc[i]);
  pthread_mutex_destroy(&lock_mining);
  return 0;
}

//--------------------------------------------
// FUNCTION: scv_init
// Serves to initialize 5 SCV workers.
// PARAMETERS:
// None
//----------------------------------------------
void scv_init(){
  num_of_scv = 5;
}

//--------------------------------------------
// FUNCTION: scv_terran_worker
// Serves to summon(create) a new scv worker.
// PARAMETERS:
// None
//----------------------------------------------
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

//--------------------------------------------
// FUNCTION: scv_working
// Shows in one function all job done by one worker.
// PARAMETERS:
// idx_thread
// - idx_thread: this is the worker's id number
//----------------------------------------------
void *scv_working(void *idx_thread){
  size_t index_thread;
  index_thread = (size_t)idx_thread;

  scv_mining_minerals(&index_thread);
  scv_transporting_minerals(&index_thread);
  scv_delivering_minerals(&index_thread);
  return 0;
}

//--------------------------------------------
// FUNCTION: scv_mining_minerals
// Serves to show that a worker is mining minerals.
// PARAMETERS:
// idx_thread
// - idx_thread: this is the worker's id number
//----------------------------------------------
void scv_mining_minerals(size_t *idx_scv){
	pthread_mutex_lock(&lock_mining);
    printf("SCV %d is mining\n", *idx_scv);
    minerals_on_map -= 8; // Mining 8 minerals
    all_mined_minerals += 8;
    //remaining_minerals();
    if(minerals_on_map == 0){
      scv_transporting_minerals(idx_scv);
      scv_delivering_minerals(idx_scv);
      sleep(3);
      printf("You lose the game! (You have not 20 soldiers)\n");
      original_minerals();
      remaining_minerals();
      mined_minerals();
      //delivered_minerals();
      exit(EXIT_SUCCESS);
    }
	pthread_mutex_unlock(&lock_mining);
}

//--------------------------------------------
// FUNCTION: scv_transporting_minerals
// Serves to show that a worker is transporting minerals.
// PARAMETERS:
// idx_thread
// - idx_thread: this is the worker's id number
//----------------------------------------------
void scv_transporting_minerals(size_t *idx_scv){
  // Transport minerals (use sleep(2);)
  printf("SCV %d is transporting minerals\n", *idx_scv);
  sleep(2);
}

//--------------------------------------------
// FUNCTION: scv_delivering_minerals
// Serves to show that а worker is delivering minerals.
// PARAMETERS:
// idx_thread
// - idx_thread: this is the worker's id number
//----------------------------------------------
void scv_delivering_minerals(size_t *idx_scv){
  // Delivering minerals to the first free Command center
  int i; // current Command center index
  int cheker = 0;
  while(1){
    for(i = 0; i < number_of_command_cs; i++){
      if(pthread_mutex_trylock(&lock_cc[i]) == 0){
        array_of_command_cs[i] += 8;
        current_mineral_for_use += 8;
        printf("SCV %d delivered minerals to Command center %d\n", *idx_scv, i+1);
        // printf("Minerals in Command center %d: %d\n",i+1 , array_of_command_cs[i]);
        // printf("Minerals in Current Minerals: %d\n", current_mineral_for_use);
        pthread_mutex_unlock(&lock_cc[i]);
        cheker = 1;
        break;
      }
    }
    if(cheker == 1)
    break;
    sleep(1);
  }
}

//--------------------------------------------
// FUNCTION: use_scanf
// Serves to take commands from the input,
// to create soldiers, workers and Command centers.
// PARAMETERS:
// None
//----------------------------------------------
void *use_scanf(){
	while(1){
    char input[256];
    scanf("%s" , input);
      // Summon Soldier
    if (strcmp(input, "m") == 0){
      summon_soldier();
      // Summon SCV worker
    } else if(strcmp(input, "s") == 0){
      scv_terran_worker();
      // Build Command center
    } else if(strcmp(input, "c") == 0){
      create_command_center();
    }
  }
  return 0;
}


int main(){

	command_center_init();
	scv_init();

	pthread_t scanf_thread;
	pthread_t scv_all_work_thread;

  int error_create1 = pthread_create(&scanf_thread, NULL, use_scanf, NULL);
  if (error_create1 != 0) {
    fprintf(stderr, "Error creating thread: scanf_thread!\n");
    exit(EXIT_FAILURE);
  }

	int error_create2 = pthread_create(&scv_all_work_thread, NULL, scv_all_work, NULL);
  if (error_create2 != 0) {
    fprintf(stderr, "Error creating thread: scv_all_work_thread!\n");
    exit(EXIT_FAILURE);
  }

	int error_join1 = pthread_join(scanf_thread, NULL);
  if (error_join1 != 0) {
    fprintf(stderr, "Error joining thread: scanf_thread!\n");
    exit(EXIT_FAILURE);
  }
	int error_join2 = pthread_join(scv_all_work_thread, NULL);
  if (error_join2 != 0) {
    fprintf(stderr, "Error joining thread: scv_all_work_thread!\n");
    exit(EXIT_FAILURE);
  }

  pthread_exit(NULL);
  return 0;
}
