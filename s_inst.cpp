/**@brief Funcion que guarda 'palabras' en un arreglo
Cada palabra es un t�rmino de la instrucci�n. Luego, en este arreglo se busca lo necesario. Por ejemplo
el primer elemento ser� el comando ('cd', 'ls',...). Luego seguir�n los argumentos de dicho comando.
Se podr� buscar, por ejemplo, el caracter '|' (pipe) para conectar comandos.
Si se encuentra, la palabra inmediata siguiente ser� otro comando. 
 @author Arancibia, Sofia Casandra
 @date 03/07/2015
*/ 


#include <cstring>

using namespace std;

void s_inst(char *inst,char *ar[]){	
	int i=0;
	char *p; //para strtok
		//strtok divide una oracion en palabras (tokens)
		//char * strtok ( char * str, const char * delimiters );
		p = strtok(inst," ");
		ar[i]=p;		
			while(p != NULL){//al llegar al final de la oracion strtok retorna null.
				i++;
				//la primera llamada recibe la cadena, las siguientes usan la cadena que resta luego de la primer llamada.
				//eso se indica pasandole null al primer arguemento de strtok.
				p = strtok(NULL, " ");
				//se agrega la palabra al arreglo.
				ar[i]=p;				
			}
			i++; 
//			ar[i]='\0';
}


//Referencias:
//http://www.cplusplus.com/reference/cstring/strtok/

	
