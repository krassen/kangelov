//--------------------------------------------
// NAME: Krassen Angelov
// CLASS: XIa
// NUMBER: 14
// PROBLEM: #2
// FILE NAME: shell_krassen_angelov_11a.c 
// FILE PURPOSE:
// Shell is a program that takes your commands from the 
// standard input (keyboard) and gives them to the operating system
// to perform.
//---------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

#define STRS_SIZE 255

//--------------------------------------------
// FUNCTION: parse_cmdline 
// This function is parsing commands that are taken from the standard
// input (keyboard). 
// Example: 
//	form: "/bin/ls -l /usr/include" to {"/bin/ls", "-l", "/usr/include"}
// PARAMETERS:
// *cmdline - the place where is saved the string with commands from the
// standard input (keyboard).
//----------------------------------------------


char** parse_cmdline(const char* cmdline){
	char *word = (char*)malloc(STRS_SIZE * sizeof(char)); // memory allocation for the string - parsed_lines
	int length_cmdline = 0;
	length_cmdline = strlen(cmdline);
 	
 	// ---------------------- mini strings counter (from the string: cmdline) ---------------------------
	int miniStrs_bool = 0; // true - 1 or false - 0. If we have 1 we are on mini string!
	int onFirst_symbol_miniStr = 0; // Again for mini strings count. We use it to know if we are on first symbol of each mini string!
	int mini_strs_count = 0;
	int index;
	for(index = 0; index <= length_cmdline; index++){
		if(cmdline[index] != ' ' && cmdline[index] != '\0'){
			miniStrs_bool = 1;
		}
		else {
			miniStrs_bool = 0;
			onFirst_symbol_miniStr = 0;
		}

		if(miniStrs_bool == 1 && onFirst_symbol_miniStr == 0){
			mini_strs_count++; // mini_strs_count = mini_strs_count + 1;
							   // mini_strs_count -> increase by one
			onFirst_symbol_miniStr++; // onFirst_letter_miniStr = onFirst_letter_miniStr + 1; 
									  // onFirst_letter_miniStr -> increase by one
		}	
	}
	// -------------------------------------------------------------------------------------------
	
	
	char **parsed_lines = (char**)malloc((mini_strs_count)*sizeof(char)); // memory allocation for the array of strings: parsed_lines
	int pl_index = 0; // parsed lines index
	int word_index = 0; // index for the string: word
	int i;
	for(i = 0; i <= length_cmdline ; i++){
		if(cmdline[i] != ' ' && cmdline[i] != '\0'){
			word[word_index] = cmdline[i]; // character form string - word,
										   // intake symbol of string - csmdline
			word_index++; // word_index = word_index + 1; 
						  // word_index -> increase by one
			
		}
		else {
			parsed_lines[pl_index++] = strdup(word);
			memset(word,0,sizeof(word)); // mumset - Sets all bytes of the block of
										 // memory pointed by string - word, to zero. 	 
			word_index = 0;
		}	
	}		
		
	parsed_lines[mini_strs_count] = NULL; // The last element of the array of strings -
										  // parsed_lines, accept NULL.
	
	return parsed_lines;
}
	
int main(int argc, char *argv[])
{
	char str_line[STRS_SIZE];
	char commands[STRS_SIZE];
	char **parsed_line;
	char command[STRS_SIZE]; // It's a string that we use to print the error messages. 
	printf("$ ");
	while(fgets(str_line, 255, stdin)){ // Taking commands from standard input and putting 
										//them in the string - commands. 
		printf("$ ");
		strcat(commands, str_line);
	}
	
	printf("\n");
	
	pid_t pid = fork();
	
	if (pid == 0) {
		/* This is the child process. */
		printf("Hello from child!\n");
		printf("going to run shell from child...\n");
		parsed_line = parse_cmdline(commands);
		if(execv(parsed_line[0], parsed_line)){
			strcpy(command, parsed_line[0]);
			perror(command);
		}
		free(parsed_line);
		return 9;
	} else if (pid > 0) {
		/* This is the parent process.
		 Wait for the child to complete. */
		printf("Hello from parent!\n");
		printf("Waiting for child process..\n");
		int status = 0;
		wait(&status);
		if (WIFEXITED(status)) {
			int exit_status = WEXITSTATUS(status);
			printf("Child process '%d' terminated normally with exit status code: %d\n", pid, exit_status);
		} else {
			printf("Child process exited abnormally!\n");
		return 1;
	}
	} else {
		/* The fork failed. */
		perror("fork");
		return 1;
	}
					
  return 0;
}
