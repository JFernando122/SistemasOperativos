#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <windows.h>
#include <string.h>
#define MIN_LINEA 1
#define MAX_LINEA 10
#define MAX_SEG 15
#define MIN_SEG 1
#define QUANTUM 5
#define INTERVALO 20
typedef struct Nodo{
	char cadena[45];
	char caracter;
	int numero1,numero2,id;
	struct Nodo* siguiente;
}Nodo;


Nodo* agregaNodo(Nodo* cabeza, Nodo a){
	static int id = 0;
	Nodo* aux = cabeza;
	Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
	strcpy(nuevo->cadena,a.cadena);
	nuevo->caracter = a.caracter;
	nuevo->numero1 = a.numero1;
	nuevo->numero2 = a.numero2;
	nuevo->id = ++id;
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
void mostrarListaD(Nodo* cabeza){
	Nodo* aux = cabeza;
	int i = 0,tiempo = 0,intervalos = 0;
	if(cabeza == NULL)
		puts("Lista vacia\n");
	else{
		do{
			if(aux->numero1 < QUANTUM){
				//Sleep(aux->numero1*1000);
				sleep(aux->numero1);
				tiempo += aux->numero1;
				printf("Proceso %d terminado\n",aux->id);
				aux  = borrarNodo(aux,aux->id);
				i++;
			}else{
				//Sleep(QUANTUM*1000);
				sleep(QUANTUM);
				aux->numero1 -= QUANTUM;
				tiempo += QUANTUM;
				printf("id: %d Tiempo restante: %d\n",aux->id,aux->numero1);
				if(aux->numero1 == 0){
					printf("Proceso %d terminado\n",aux->id);
					aux = borrarNodo(aux,aux->id);
					i++;
				}else{
					if(aux != NULL)
				   aux = aux->siguiente;
				}
			}
			if(tiempo >= INTERVALO){
				tiempo -= INTERVALO;
				//printf("Intervalo %d  procesos terminados %d\n",intervalos,i);
				printf("Procesos terminados en %d segundos:%.2f\n",INTERVALO,(double) i/ (double)++intervalos);
			}
		}while(aux != NULL);
	}
}
Nodo* AgregaNodoP(Nodo* cabeza, Nodo a){
	Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
	strcpy(nuevo->cadena,a.cadena);
	nuevo->caracter = a.caracter;
	nuevo->numero1 = a.numero1;
	nuevo->numero2 = a.numero2;
	nuevo->siguiente = cabeza;
	return nuevo;
}
