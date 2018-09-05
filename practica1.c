#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodos.h"
#include "estadisticas.h"
typedef struct master{
	Nodo* cabeza;
	Nodo_E* estadistica;
}master;
master* leerArchivo(char* nombre, master* master){
	FILE* archivo = fopen(nombre,"r");
	Nodo nodo;
	Nodo_E nodo_e;
	static int id = 0;
	if(archivo){
		while(!feof(archivo)){
			fscanf(archivo,"%s %c %d %d\n",nodo.cadena,&nodo.caracter,&nodo.numero1,&nodo.numero2);
			nodo.id = ++id;
			nodo_e.tiempo_ejecucion = nodo.numero1;
			nodo_e.id = nodo.id;
			master->cabeza = agregaNodo(master->cabeza,nodo);
			master->estadistica = agregarNodoE(master->estadistica,nodo_e);
		}
		printf("Archivo %s leido\n",nombre);
		fclose(archivo);
	}
	else
		puts("No se encuentra el archivo\n");
	return master;
}
void mostrarListaD(master* master){
	Nodo* aux = master->cabeza;
	Nodo_E* temp;
	int i = 0,tiempo = 0,intervalos = 0;
	if(aux == NULL)
		puts("Lista vacia\n");
	else{
		do{
			if(aux->numero1 < QUANTUM){
				//Sleep(aux->numero1*1000);
				//sleep(aux->numero1);
				tiempo += aux->numero1;
				printf("Proceso %d terminado\n",aux->id);
				temp = buscarNodo_E(master->estadistica,aux->id);
				temp->tiempo_terminacion = intervalos*INTERVALO + tiempo;
				/*if(temp == NULL)
					puts("Nulo");
				else
					puts("No nulo");*/
				aux  = borrarNodo(aux,aux->id);
				i++;
			}else{
				//Sleep(QUANTUM*1000);
				//sleep(QUANTUM);
				aux->numero1 -= QUANTUM;
				tiempo += QUANTUM;
				printf("id: %d Tiempo restante: %d\n",aux->id,aux->numero1);
				if(aux->numero1 == 0){
					printf("Proceso %d terminado\n",aux->id);
					temp = buscarNodo_E(master->estadistica,aux->id);
					temp->tiempo_terminacion = intervalos*INTERVALO + tiempo;
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
		mostrarE(master->estadistica);
	}
}
int main(int argc, char *argv[]) {
	int opcion,nodoaeliminar;
	char nombredelarchivo[20];
	master* master = (struct master*)calloc(1,sizeof(master));
	master->cabeza = NULL;
	master->estadistica = NULL;
	do{
	puts("Que desea hacer?");
	printf("1.- Leer archivo   2.-Borrar nodo   3.-Mostrar lista   4.-Despachar  5.-Salir\n");
	scanf("%d",&opcion);
	switch(opcion){
	case 1:
		printf("Escriba el nombre del archivo.\n");
		scanf("%s",nombredelarchivo);
		strcat(nombredelarchivo,".txt");
		master = leerArchivo(nombredelarchivo,master);
		//mostrarListaE(cabeza);
	break;
	case 2:
		printf("Longitud de la lista %d\n",Longitud(master->cabeza));
		printf("Que nodo desea borrar?");
		scanf("%d",&nodoaeliminar);
		master->cabeza = borrarNodo(master->cabeza,nodoaeliminar);
	break;
	case 3:
		mostrarLista(master->cabeza);
	break;
	case 4:
		mostrarListaD(master);
		master->cabeza = NULL;
	break;
	case 5:
		puts("Bonito dia...");
	break;
	case 11:
		system("archivo.exe");
	break;
	case 12:
		system("./archivo");
	break;
	default:
	puts("Opcion invalida. Intente de nuevo.");
	break;
	}
	}while(opcion!=5);
	return 0;
}

