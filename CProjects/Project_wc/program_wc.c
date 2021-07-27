#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


int main(int argc, char *argv[]) {
		
			int argument;
			int rall = 0; // all rows in programs
			int wall = 0; // all wards in programs
			int sall = 0; // all simbols in programs
			//int length[6] = {0, 0, 0, 0, 0, 0}; // 6
			// {length_r, length_w, length_s, length_rall, length_wall, length_ sall};
			int length_rall = 0;
			int length_wall = 0;
			int length_sall = 0;
			int size = 8; // no size 9 e po-dobre
			int length_r = 0;
			int length_w = 0;
			int length_s = 0;
			char testing[100]; // sluji za da znaem koe e naj-dylgoto chislo i syotvetno 
			// po nego da mojem da podredim drugite
			
			for (argument = 1; argument < argc; argument++){
			
				char buff[200];
				int fd;
				int rcount = 0; // rows counter
				int wcount = 0; // words counter
				int scount = 0; // simbols counter
				int wbool = 0; // true - 1 or false - 0. If we have 1 we are on word!
				int wk = 0; // again for wcount. Its for us to know that we are on first letter in word!
			
				fd = open(argv[argument], O_RDONLY);
			
			
				if (fd == -1) { // pri greshki
						perror("open");
						return -1;
				}
		
		
				int status_read = 1;
				int new_lines = 0;
				int should_exit = 0;
				while(status_read > 0 && !should_exit) {
					int i;
					status_read = read(fd, buff, 200); //chete do 200 simvola vyv buff

					if (status_read < 0) {
						perror("read");
						return 1;
					}
					for(i = 0; i < status_read; i++){
						if (buff[i] == '\n'){
							new_lines++;
						}
			// ---------------------- rows counter ----------------------------
						if (buff[i] == '\n'){
							rcount++;
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
							wcount++;
							wk++;
						}
					
			// ---------------------- simbols counter -------------------------
						scount++;
						
			// ----------------------------------------------------------------
			/*
						if(new_lines == 10){
							status_read = i+1;
							should_exit = 1;
							break;
						}
			*/
					}
			/*
				int written = 0;
				while (written < status_read) {
				int status_write = write(STDOUT_FILENO, buff + written, status_read);	
				// kak da izvedem file ako ima poveche ot 200 byte v nego
				// kak da prochetem proizvolen broj
				

			
					if (status_write < 0) {
						if (errno == EINTR) { // toest nomer na greshkata e errno
							status_write = 0;
						}
						else {
							perror("write");
							return 1;
						}
					}
						
						written += status_write;
				}
			*/
			}
			
			
		//trqbva da si zatvarqme file vseki pyt poneje ne e qsno kakvo stava s dannite
		//i nqma da imame visoki ocenki ako ne go zatvorim
		
			if (close(fd) == -1) {
				perror("close");
				return -1;

			}
			 // proverqvane za greshki // pri zatvarqne na file
		//vryshto 0 ako e ok i -1 ako ima greshka
		
		
			rall += rcount;
			wall += wcount;
			sall += scount;
			
				
				sprintf(testing,"%d",rcount);
				length_r = strlen(testing);
				printf("length_r:%d\n", length_r);
				
				sprintf(testing,"%d",wcount);
				length_w = strlen(testing);
				printf("length_w:%d\n", length_w);
				
				sprintf(testing,"%d",scount);
				length_s = strlen(testing);
				printf("length_s:%d\n", length_s);
				
			length_r = size - length_r;
			while(length_r > 0) {
				printf(" ");
				length_r -= 1;
			}	
			printf("%d ", rcount);
			length_w = size - length_w;
			while(length_w > 0) {
				printf(" ");
				length_w -= 1;
			}
			printf("%d ", wcount);
			length_s = size - length_s;
			while(length_s > 0) {
				printf(" ");
				length_s -= 1;
			}
			printf("%d\t", scount);
			printf("%s\n", argv[argument]); // print the name of file
			printf("-------------------------------------------\n");
				
		}
		if (argc > 2) {
			
			sprintf(testing,"%d",rall);
			length_rall = strlen(testing); 
			sprintf(testing,"%d",wall);
			length_wall = strlen(testing); 
			sprintf(testing,"%d",sall);
			length_sall = strlen(testing); 
			printf("%d\n", length_rall);
			printf("%d\n", length_wall);
			printf("%d\n", length_sall);
			
		//printf("length_sall:%d\n", length_sall);
		length_rall = size - length_rall;
			while(length_rall > 0) {
				printf(" ");
				length_rall -= 1;
			}	
			printf("%d ", rall);
			length_wall = size - length_wall;
			while(length_wall > 0) {
				printf(" ");
				length_wall -= 1;
			}
			printf("%d ", wall);
			length_sall = size - length_sall;
			while(length_sall > 0) {
				printf(" ");
				length_sall -= 1;
			}
			printf("%d\t", sall);
			printf("total\n");
			printf("Arguments counter (files counter): %d\n", argc - 1);
		}
		
		return 0;
}
/*
Dom: da napishem finkciqta wc
wc test.c 
kalko reda ima kolko symvola i oshte dava za nego
da inplementirame programata wc
zadyljitelno da se polzva samo vzetotto ot dnes ne sys scanf
trqbva da mojem da puskame i po nqkolko argumenta
wc test.c test.txt zad1.c

pishe v kato argumenti na main 
toest argv i argc

Wajno e za krajnata ocenka!!!
 
shte izpitva ne nego i da ne go pishem posledniq den!!!
*/
