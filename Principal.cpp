/**@brief Funcion principal(main). Contiene el bucle que se ejecutará hasta que 
el usuario ingrese el comando "exit".
Se lee una instruccion desde el standard input, con la función s_inst() se crea un arreglo 
con el comando y sus argumentos. Finalmente, con la funcion Ejecutar se lanza la instrucción.
 @author Arancibia, Sofia Casandra
 @date 03/07/2015
*/


#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno> 
#include <fstream>


using namespace std;

extern void s_inst(char *inst,char *ar[]);
extern void ejecutar(char **args);
extern void tuberia(char *arg1[], char *arg2[]);
extern void camino(string path, char car);

bool f_pipe(string s){//funcion que retorna true en caso de que haya un pipe (|) en la instruccion
	if ((s.find('|'))==string::npos) //si no encontro...
	return false;
	else
	return true;
}

int main(){	
	
	printf("___________________________________\n");
	printf("so2015shell\n");
	printf("Autor: ARANCIBIA, Sofia Casandra\n");
	printf("Version: 1.0\n");
	printf("Año: 2015\n");
	printf("___________________________________\n");
	

	
	while(true){		
		
		printf("%%"); //prompt		
		
		//leo el comando como string (para desligarme de tener que prefijar un tamaño del arreglo)
		std::string com;		
		
		//leo hasta el enter
		getline(std::cin,com,'\n'); //por defecto ya era '\n'
		
		if(com.length()==0) continue; //si presiono enter y no hay ningun comando, pensala de nuevo...
				
		//verifico si la instruccion es compuesta.
		bool pi_pe;
		pi_pe=f_pipe(com);
		
		//convierto el string a cadena de char (const para poder usar el c_str() )
		const char* com1;
		com1=com.c_str();	
		
				
		//arreglo resultado de s_inst
		//el tamaño maximo será lo que ocupa la instruccion completa. Así me aseguro de
		//no guardar espacio de menos.
		int len=com.size();
		char* s_a[len];		
		
		if(pi_pe==true){//si en la instruccion se conectan dos comandos..
				
			char* d_a[len];
			char* d_b[len];						
			char *d; //para strtok
			char *p; //para strtok
			
			//separo los dos comandos
			d = strtok((char*)com1,"|");
			p = strtok(NULL,"|");
			//divido cada comando en un arreglo de palabras
			s_inst(d,d_a);
			s_inst(p,d_b);
			//ejecuto
			tuberia(d_a,d_b);
			
		}else{
		
		//creo mi arreglo de argumentos
		s_inst((char*)com1,s_a);
		
		//Evaluación de casos especiales		
		if(strcmp(s_a[0],"camino")==0){		
		string p=s_a[1]; //guardo la ruta		
		
		if(!s_a[2]){printf("Comando incorrecto\n");continue;}
		else if(strcmp(s_a[2],"+")==0){camino(p,'+');continue;}
		else if(strcmp(s_a[2],"-")==0){camino(p,'-');continue;}			
		
		}
		
		if(strcmp(s_a[0],"exit")==0){
			exit(EXIT_SUCCESS);
			return 0;			
		}else if(strcmp(s_a[0],"cd")==0){	//con exec no puede ejecutarse el comando cd.
			//Lo reemplazo con la funcion chdir -> int chdir(const char *path);			
			if(chdir(s_a[1])!= 0){ //no se pudo cambiar de directorio
				printf("%s\n", (char*) strerror(errno));
			}
		}else if(strcmp(s_a[0],"cat")==0 && strcmp(s_a[1],">")==0){ //comando cat > algo.*
			ofstream outf(s_a[2]);
			string cont;
			getline(std::cin,cont,'\n'); //lee contenido desde el teclado hasta presionar enter
			outf<<cont<<"\n"; //lo escribe en el archivo de nombre especificado en la instruccion
			outf.close();			
		}		
		else{ 
			ejecutar(s_a);			
		}	
		
		}
	}
	
	
	return 0;
}

//Referencias
//http://www.cplusplus.com/reference/string/string/getline/
//E. Balagurusamy. "PROGRAMACION ORIENTADA A OBJETOS CON C++", 3ra edicion
//http://www.cplusplus.com/reference/cstring/strtok/
