#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <windows.h>
#include <string.h>
#define MIN_LINEA 1
#define MAX_LINEA 5
#define MAX_SEG 7
#define MIN_SEG 1
#define QUANTUM 3
#define INTERVALO 20
typedef struct Nodo{
	char cadena[45];
	char caracter;
	int numero1,numero2,id;
	struct Nodo* siguiente;
}Nodo;

Nodo* juntarListas(Nodo* lista1, Nodo* lista2){
    Nodo* aux1;
    Nodo* aux2;
    aux1=lista1;
    aux2=lista2;
    if(lista1 != NULL && lista2 != NULL){
        do{
            aux1=aux1->siguiente;
     }while(aux1->siguiente!=lista1);
    
     do{
         aux2=aux2->siguiente;
      }while(aux2->siguiente!=lista2);

        aux1->siguiente=lista2;
         aux2->siguiente=lista1;
    }else if (lista1 == NULL)
        lista1 = lista2;
    return lista1;
}

Nodo* agregaNodo(Nodo* cabeza, Nodo a){
	Nodo* aux = cabeza;
    //Nodo* aux1=a.siguiente;
	Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
	strcpy(nuevo->cadena,a.cadena);
	nuevo->caracter = a.caracter;
	nuevo->numero1 = a.numero1;
	nuevo->numero2 = a.numero2;
	nuevo->id = a.id;
	nuevo->siguiente = cabeza;
	if(cabeza == NULL){
		cabeza = nuevo;
		cabeza->siguiente = cabeza;
	}
	else{
		while(aux->siguiente != cabeza){
			aux = aux->siguiente;
		}
		aux->siguiente = nuevo;
	}
    /*while(aux1.siguiente!=a){
    aux1=aux1.siguiente;    
    }
    aux1.siguiente=cabeza;*/
	return cabeza;
}
int Longitud(Nodo* cabeza){
	Nodo* aux = cabeza;
	int i = 0;
	if(cabeza != NULL){
		do{
			i++;
			aux = aux->siguiente;
		}while(aux != cabeza);
	}
	return i;
}
Nodo* borrarNodo(Nodo* cabeza,int id){
	Nodo* aux = cabeza;
	Nodo* temp = cabeza;
	if(id < 1 || cabeza == NULL){
		printf("Posicion invalida, o lista vacia\n");
	}else{
		if(id != cabeza->id){
			while(aux->siguiente != cabeza && aux->siguiente->id != id){
				aux = aux->siguiente;
			}
			if(aux->siguiente != cabeza){
				temp = aux->siguiente;
				aux->siguiente = aux->siguiente->siguiente;
				//printf("Nodo a eliminar:\n%s %c %d %d\n",temp->cadena,temp->caracter,temp->numero1,temp->numero2);
				free(temp);
			}else
				printf("id: %d no existe\n",id);
		}else{
			if(cabeza == cabeza->siguiente){
				temp = cabeza;
				cabeza = NULL;
			}else{
				while (aux->siguiente != cabeza)
					aux = aux->siguiente;
				aux->siguiente = aux->siguiente->siguiente;
				temp = cabeza;
				cabeza = cabeza->siguiente;
				//printf("Nodo a eliminar:\n%s %c %d %d\n",temp->cadena,temp->caracter,temp->numero1,temp->numero2);
			}
			free(temp);
		}
	}
	return cabeza;
}
void mostrarListaE(Nodo* cabeza){
	Nodo* aux = cabeza;
	int aleatoriolineas,aleatoriotiempo;
	if(cabeza == NULL)
		puts("Lista vacia\n");
	else{
		do{
			aleatoriolineas = rand() % (MAX_LINEA - MIN_LINEA) + 1;
			aleatoriotiempo = rand() % (MAX_SEG - MIN_SEG ) + 1;
			for(int i = 0 ; i < aleatoriolineas; i++){
				printf("%s %c %d %d id:%d\n",aux->cadena,aux->caracter,aux->numero1,aux->numero2,aux->id);
				aux = aux->siguiente;
				if(aux == cabeza)
					break;
			}
			puts("");
			//Sleep(aleatoriotiempo*1000);
			sleep(aleatoriotiempo);
		}while(aux != cabeza);
	}
}
void mostrarLista(Nodo* cabeza){
	Nodo* aux = cabeza;
	if(cabeza == NULL)
		puts("Lista vacia\n");
	else{
		do{
			printf("%s %c %d %d id:%d\n",aux->cadena,aux->caracter,aux->numero1,aux->numero2,aux->id);
			aux = aux->siguiente;
		}while(aux != cabeza);
	}
}

