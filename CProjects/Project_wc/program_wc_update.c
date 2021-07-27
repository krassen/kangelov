//--------------------------------------------
// NAME: Krassen Angelov
// CLASS: XIa
// NUMBER: 14
// PROBLEM: #1
// FILE NAME: program_wc_update.c 
// FILE PURPOSE: 
// The purpose of the program is to be realized
// the standart UNIX comand wc.
//---------------------------------------------

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define SIZE_ARR 6

//--------------------------------------------
// FUNCTION: read_and_count_rws 
// This function serves to read file and count the rows, words and symbols.
// PARAMETERS:
// *count_arr - the place where are saved the counted rows, words and symbols
// input - the point at which we start to read from the standard input or file
// var - we used it to chose  
//----------------------------------------------

int read_and_count_rws(int *count_arr, int output) {
	char buff[200];
	int status_read = 1;
	while(status_read > 0){
	status_read = read(output, buff, 200);		
		if (status_read < 0) {
			perror("read");
			return 1;
		}
		count_rws(count_arr, status_read, buff);
	}	
	return 0;
}

//--------------------------------------------
// FUNCTION: count_rws 
// This function serves to count the rows, words and symbols.
// PARAMETERS:
// *count_arr - the place where are saved the counted rows, words and symbols
// status_read - status_read = read(...);
// *buff - the place from where the symbols will be taken 
//----------------------------------------------

int count_rws(int *count_arr, int status_read, char *buff){
	int wbool = 0; // true - 1 or false - 0. If we have 1 we are on word!
	int wk = 0; // Again for words count. We use it to know if we are on first letter of word!
	int i;
	for(i = 0; i < status_read; i++){	
		// ---------------------- rows counter ----------------------------
		if (buff[i] == '\n'){
			count_arr[0]++;	//rows counter + 1;
		}
		// ---------------------- words counter ---------------------------
		if(buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\n'){
			wbool = 1;
		}
		else {
			wbool = 0;
			wk = 0;
		}
		if(wbool == 1 && wk == 0){
			count_arr[1]++;	//words counter + 1;
			wk++;
		}			
		// ---------------------- symbols counter -------------------------
		count_arr[2]++;	//symbols counter + 1;	
	}
}

//--------------------------------------------
// FUNCTION: add_new_counters_to_total
// This function adds new counted rows, words and symbols 
// from standard input or file into the Total.
// PARAMETERS:
// списък с параметрите на функцията
// *count_arr - the place where are saved the Total counted rows, words and symbols
// size_arr - the size of the array
//----------------------------------------------

void add_new_counters_to_total(int *count_arr, int size_arr) 	{
	int i;
	for(i = 3; i < SIZE_ARR; i++){
		count_arr[i] += count_arr[i-3]; // all rows count += row count; 
										// all words count += words count; 
										// all symbols count += symbols count;
	}
	return;
}

//--------------------------------------------
// FUNCTION: print_counters_without_fileName_and_total
// This function serves to print the number of the rows, words and symbols 
// from the standard input or file without the file name.
// PARAMETERS:
// *count_arr - the place from where we print the number of all counted rows, words and symbols 
//  saved from the standard input or file
// *length_arr - the lenght of the number of rows, words and symbols  
//		Example: rows - 9 -> length rows = 1,
// 	 			 words - 97 -> length words = 2,
//               symbols - 400 -> length = 3; 
// *helper_str - string which helps us to determine the length of the rows, words and symbols 
//  from the standard input and file
// size_arr - the size of the array
// cal - we use it to arrange the number of rows, words and symbols in three different columns   
//----------------------------------------------

void print_counters_without_fileName_and_total(int *count_arr, int *length_arr, 
									char *helper_str, int size_arr, int cal) {
	int i;
	for(i = 0; i < size_arr/2; i++){
				
		sprintf(helper_str,"%d",count_arr[i]);  
		length_arr[i] = strlen(helper_str);
		length_arr[i] = cal - length_arr[i]; // Determine the number of empty spaces 
											 // in front of every number of rows, words and symbols 
											 // from the standard input or file.  
		while(length_arr[i] > 0) {
			printf(" ");
			length_arr[i] -= 1;
		}	
		printf("%d ", count_arr[i]);
	}	
	return;
}

//--------------------------------------------
// FUNCTION: print_counters_without_total 
// This function serves to print the number of the rows, words and symbols 
// from the standard input or file.
// PARAMETERS:
// *argv_arr - the place where are the arguments from the main function 
// *count_arr - the place from where we print the number of all counted rows, words and symbols 
//  saved from the standard input or file
// *length_arr - the lenght of the number of rows, words and symbols  
//		Example: rows - 9 -> length rows = 1,
// 	 			 words - 97 -> length words = 2,
//               symbols - 400 -> length = 3; 
// *helper_str - string which helps us to determine the length of the rows, words and symbols 
// from the standard input and file
// size_arr - the size of the array
// cal - we use it to arrange the number of rows, words and symbols in three different columns
//
//----------------------------------------------

void print_counters_without_total(char *argv_arr, int *count_arr, int *length_arr, 
									char *helper_str, int size_arr, int cal) {
										
	print_counters_without_fileName_and_total(count_arr, length_arr, 
									helper_str, size_arr, cal);
	printf("\t");
	printf("%s\n", argv_arr); // print the file name
	
	return;
}

//--------------------------------------------
// FUNCTION: print_total 
// This function serves to print Total.
// PARAMETERS:
// *count_arr - the place from where we take all the rows, words and symbols 
// *length_arr - the lenght of the Total number of rows, words and symbols 
//			Example: rows - 9 -> length rows = 1,
// 	 			     words - 97 -> length words = 2,
//                   symbols - 400 -> length = 3;   
// *helper_str - string which helps us to determine the length of the Total rows, words and symbols 
//  size_arr - the size of the array
//  cal - we use it to arrange the number of rows, words and symbols in three different columns
//----------------------------------------------

void print_total(int *count_arr, int *length_arr, char *helper_str, int size_arr, int cal) {
	int i;
	for (i = 3; i < size_arr; i++) {
		sprintf(helper_str,"%d",count_arr[i]);
		length_arr[i] = strlen(helper_str); 
		length_arr[i] = cal - length_arr[i]; // Determine the number of empty spaces 
											 // in front of number of rows, words and symbols 
											 // of Total.  
		while(length_arr[i] > 0) {
			printf(" ");
			length_arr[i] -= 1;
		}	
		printf("%d ", count_arr[i]);
	} 
	printf("\t");
	printf("total\n");
	return; 
}

//--------------------------------------------
// FUNCTION: zeroing_counters_without_total
// This function serves to zeroing the counted rows, words and symbols 
// from the standard input or file.
// PARAMETERS:
// *count_arr - the place which we reset the number of rows, words and symbols 
//  from the standart input or file  
//  size_arr - the size of the array
//----------------------------------------------

void zeroing_counters_without_total(int *count_arr, int size_arr) {
	int i;	
	for(i = 0; i < size_arr/2; i++) {
		count_arr[i] = 0;  
	}
	return;
}

int main(int argc, char *argv[]) {
	
	int argument; // We use it to know in which argumemt from main we are located.
	
	int count[SIZE_ARR] = {0, 0, 0, 0, 0, 0}; // six elements
	// And they are:
/*	{
		[0]-> rows counter,
		[1]-> words counter,
		[2]-> symbols counter,
		[3]-> count All ROWS in programs,
		[4]-> count All WORDS in programs,
		[5]-> count All SYMBOLS in programs
	};
*/ 
	int length[SIZE_ARR] = {0, 0, 0, 0, 0, 0}; // six elements
	// And they are:
/*	{
		[0]-> length of "rows counter",
		[1]-> length of "words counter", 
		[2]-> length of "symbols counter", 
		[3]-> length of "count All ROWS in programs", 
		[4]-> length of "count All WARDS in programs", 
		[5]-> length of "count All SYMBOLS in programs"	
	};	
*/

	int caliber = 8; // calliber - eigth it is the most suitable    
					 // We use it to arrange the number of rows, 
					 // words and symbols in three different columns.
					   
	char helper[100]; // Derves to be determined the length of the number of
					  // rows, words and symbols.  
					 
	char file_name[100];
	
	for (argument = 1; argument < argc; argument++){
		if(strcmp(argv[argument], "-") == 0) { 
		// We check if the argument in we are located is a "-" (dash).
		// We write in the standard input and we count the number of 
		// rows, words and symbols of the written.	
			
			read_and_count_rws(count, STDIN_FILENO);
			
			add_new_counters_to_total(count, SIZE_ARR);
			
			print_counters_without_total(argv[argument], count, length,
							helper, SIZE_ARR, caliber);
							
			zeroing_counters_without_total(count, SIZE_ARR);
			
		}
		else {
			
			int fd;
					
			fd = open(argv[argument], O_RDONLY); // Open a file
		
			//----------------Errors--------------------	
			strcpy(file_name, "wc: "); // In the void string - file_name we add "wc: ",
			strcat(file_name, argv[argument]); // after that we add the name of the file. 
			
			if (fd == -1) { // Errors
				perror(file_name);
				
				// return -1; // Deleted, because it stops the process of execution of wc
				// and don't and so does not allow switching to other files processing.
				continue;
			}
			//------------------------------------------
			
			 read_and_count_rws(count, fd);
		
			if (close(fd) == -1) { 
				perror("close");
				return -1;
			}
			// It closes the file in which we are.
			// Cheking the file for errors during the processs of closing. 
			// Return 0 - if the file is ok and -1 - if there is an error. 
		
			add_new_counters_to_total(count, SIZE_ARR);
		
			print_counters_without_total(argv[argument], count, length,
							helper, SIZE_ARR, caliber);
						
			zeroing_counters_without_total(count, SIZE_ARR);
			
		}
	}
	
	if (strcmp(argv[0], "./wc") == 0 && argc == 1) {
		// Handing over the first argument  == "./wc". 
		// We write in the standard input and we count the rows, words and symbols of the written.
		
		read_and_count_rws(count, STDIN_FILENO);
			
		add_new_counters_to_total(count, SIZE_ARR);
			
		print_counters_without_fileName_and_total(count, length,
						helper, SIZE_ARR, caliber);
		printf("\n");
							
		zeroing_counters_without_total(count, SIZE_ARR);
		
	}
	
	if (argc > 2) {
		// Because we know that the first argument is "./wc", we need minimum 3 arguments to have Total.  
		int i;
		print_total(count, length, helper, SIZE_ARR, caliber);
		//printf("Arguments counter (files counter): %d\n", argc - 1); 
	} 
	return 0;
}
