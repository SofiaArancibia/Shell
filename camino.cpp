/**@brief Esta función permite al usuario agregar o quitar rutas de la 
variable PATH, la cual contiene las rutas a las carpetas donde se encuentran
los principales ejecutables del sistema operativo. 
De momento, sólo es posible modificar la variable temporalmente, esto es,
al finalizar la aplicación, la variable PATH no habrá sido modificada.
En versiones posteriores, se mejorará este asunto.
 @author Arancibia, Sofia Casandra
 @date 13/07/2015
*/

#include <string>
#include <stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;

void camino(string path, char car){ 
	//car es '+' o '-'
//	
//	const char* n_path;
//	char *v_path; 	
//	v_path=getenv("PATH"); //path viejo
		
	
	char *p,*q;
	string path1,path2,path3;
	const char* n_path,* n_path1,* n_path2,* n_path3;
	char *v_path;     
	v_path=getenv("PATH"); //path viejo
	//system("echo $PATH"); //para ver lo que hay en la variable 
	
	switch(car){
	case '+': //agregar camino		
		n_path=path.c_str(); //path nuevo
		strcat(v_path,":"); //concateno el path viejo con el separador ':'
		strcat(v_path,n_path); //concateno con la ruta que quiero agregar
		setenv("PATH",v_path,1); //seteo el valor de la variable		
		system("echo $PATH"); //para ver lo que hay en la variable 
		break;
	case '-': //eliminar camino
//		int len=path.length()+2;  //+2 porque despues agrego ':' dos veces
//		string str=string(v_path); //path viejo
//		path=":"+path+":"; //agrego : al path ingresado como parametro
//		n_path=path.c_str(); //convierto
//		char *p;
//		p=strstr(v_path,n_path);
//		if(p!=NULL){
//			str.replace(str.find(path),len-1, "");
//		}
//		n_path=str.c_str(); //path nuevo
//		setenv("PATH",n_path,1); //seteo el valor de la variable
//		system("echo $PATH");
//		break;
		int len=path.length()+1; 
		string str=string(v_path); //path viejo
		
		
		path1=path+":"; 
		n_path1=path1.c_str(); //convierto
		
		p=strstr(v_path,n_path1);
		if(p!=NULL){
			
			str.replace(str.find(path1),len, "");
			
		}
		else{
			path2=path+"\0";
			path3=path+"/";
			n_path2=path2.c_str(); //extremo derecho.
			n_path3=path3.c_str();
			
			p=strstr(v_path,n_path2);
			q=strstr(v_path,n_path3);
			if(p!=NULL){
				if(q==NULL){
					str.replace(str.find(path2)-1,len, "");
				}
			}
			
		}
		
		
		
		n_path=str.c_str(); //path nuevo
		setenv("PATH",n_path,1); //seteo el valor de la variable
		system("echo $PATH");
		break;
	}    
	
}
	

//Referencias
//http://www.cplusplus.com/reference/cstdlib/getenv/
//http://www.greenend.org.uk/rjk/tech/putenv.html
//http://www.cplusplus.com/reference/string/string/replace/
//http://www.cplusplus.com/reference/cstring/strstr/?kw=strstr
