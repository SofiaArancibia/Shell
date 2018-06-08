/**@brief Funcion Pipe. Se encarga de crear la tubería que conectará dos comandos (la salida del primero con la entrada del 
segundo). 
 @author Arancibia, Sofia Casandra
 @date 04/07/2015
*/

#include <wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <iomanip>

using namespace std;

extern void ejecutar(char **args);
extern void s_inst(char *inst,char *ar[]);

void tuberia(char *arg1[], char *arg2[]){	
	

	pid_t pid1,pid2;
	
	int fd[2]; //descriptor de archivo	
	
	pid1=fork();

	switch(pid1){
		case -1:
			printf("Error en fork()");
			exit(EXIT_FAILURE);
			break;
		case 0: //proceso hijo (1)
			pipe(fd); //la funcion pipe crea la tuberia
			pid2=fork();
			switch(pid2){
				case -1:
					printf("Error en fork()");
					exit(EXIT_FAILURE);
		//			break;
				case 0: //proceso hijo (2)
					close(fd[0]);
					dup2(fd[1],1);
					close(fd[1]);
					if (execvp(arg1[0],arg1) != 0){
							printf("%s\n", (char*) strerror(errno));
							exit(EXIT_FAILURE);
					}else exit(EXIT_SUCCESS);
		//			break;
				default: //proceso padre
					close(fd[1]);
					dup2(fd[0],0);
					close(fd[0]);
					if (execvp(arg2[0],arg2) != 0){
						printf("%s\n", (char*) strerror(errno));
						exit(EXIT_FAILURE);
					}else exit(EXIT_SUCCESS);
		//			break;
			}
			break;
		
		default:
		wait(NULL);
	}
}	
