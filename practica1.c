#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "nodos.h"
#include "estadisticas.h"

typedef struct Multilista{
	int prioridad;
	struct Nodo* lista;
	struct Multilista* siguiente;
}Multilista;
typedef struct master{
	Multilista* cabeza;
	Nodo_E* estadistica;
}master;

Multilista* creaNodoM(Nodo nodo){
	Multilista* nuevo = (Multilista* )malloc(sizeof(Multilista));
	nuevo->siguiente = NULL;
	nuevo->lista = agregaNodo(NULL,nodo);
	nuevo->prioridad = nodo.numero2;
	return nuevo;
}
Multilista* agregaNodoM(Multilista* cabeza, Nodo nodo){
	Multilista* aux = cabeza;
	Multilista* temp;
	if(cabeza == NULL){
		cabeza = creaNodoM(nodo);
	}else if(cabeza->prioridad == nodo.numero2){
		cabeza->lista = agregaNodo(cabeza->lista,nodo);
		}
	else if(nodo.numero2 > cabeza->prioridad){
		temp = creaNodoM(nodo);
		temp->siguiente = cabeza;
		cabeza = temp;
	}else{
		while(aux->siguiente != NULL && aux->siguiente->prioridad>nodo.numero2){
			aux = aux->siguiente;
			}
		if(aux->siguiente == NULL){
			aux->siguiente = creaNodoM(nodo);
			}
		else if(aux->siguiente->prioridad == nodo.numero2){
			aux = aux->siguiente;
			aux->lista = agregaNodo(aux->lista,nodo);
		}else if(aux->siguiente->prioridad < nodo.numero2){
			temp = creaNodoM(nodo);
			temp->siguiente = aux->siguiente;
			aux->siguiente = temp;
			}
	}
	return cabeza;
}
void mostrarMultilista(Multilista* cabeza){
	Multilista* aux = cabeza;
	while(aux != NULL){
		printf("Prioridad: %d\n",aux->prioridad);
		mostrarLista(aux->lista);
		aux = aux->siguiente;
	}
}

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
			master->cabeza = agregaNodoM(master->cabeza,nodo);
			master->estadistica = agregarNodoE(master->estadistica,nodo_e);
		}
		printf("Archivo %s leido\n",nombre);
		fclose(archivo);
	}
	else
		puts("No se encuentra el archivo\n");
	return master;
}
int check(){printf("pasa");return 0;}
Nodo* mostrarListaD(Nodo* cabeza, Nodo_E* estadistica){
	Nodo* aux = cabeza;
	Nodo_E* temp;
	Nodo* temp1;
	int i = 0,tiempo = 0,intervalos = 0,lon = Longitud(cabeza);
	if(aux == NULL)
		puts("Lista vacia\n");
	else{
        
		for(int j = 0; j < lon; j++){
			if(aux->numero1 < QUANTUM){
				//Sleep(aux->numero1*1000);
				sleep(aux->numero1);
				tiempo += aux->numero1;
				printf("Proceso %d terminado\n",aux->id);
				temp = buscarNodo_E(estadistica,aux->id);
				temp->tiempo_terminacion = intervalos*INTERVALO + tiempo;
				temp1 = aux;
				aux  = aux->siguiente;
				cabeza  = borrarNodo(cabeza,temp1->id);
				i++;
			}else{
				//Sleep(QUANTUM*1000);
				sleep(QUANTUM);
                //printf("%d",check()+aux->numero1);
				aux->numero1 -= QUANTUM;
				tiempo += QUANTUM;
				printf("id: %d Tiempo restante: %d\n",aux->id,aux->numero1);
				if(aux->numero1 == 0){
					printf("Proceso %d terminado\n",aux->id);
					temp = buscarNodo_E(estadistica,aux->id);
					temp->tiempo_terminacion = intervalos*INTERVALO + tiempo;
					temp1 = aux;
					aux = aux->siguiente;
					cabeza = borrarNodo(cabeza,temp1->id);
					i++;
				}else{
				   aux = aux->siguiente;
				}
			}
			/*if(tiempo >= INTERVALO){
				tiempo -= INTERVALO;
				printf("Procesos terminados en %d segundos:%.2f\n",INTERVALO,(double) i/ (double)++intervalos);
			}*/
            }
		//}while(cabeza != NULL && aux != cabeza);
		//mostrarE(estadistica);
	}
    return cabeza;
}
void despachar(master* master){
	Multilista* aux = master->cabeza;
    Multilista* aux2 = NULL;
	Nodo* temp;
	while(aux->prioridad > 1){
        puts("Lista a ejecutarse\n\n");
        mostrarLista(aux->lista);
        puts("\n\n");
        temp=mostrarListaD(aux->lista, master->estadistica);
        if(aux->siguiente != NULL && aux->siguiente->prioridad==(aux->prioridad)-1){
            aux->siguiente->lista=juntarListas(aux->siguiente->lista, temp);
            /*printf("Prioridad1: %d prioridad2: %d\n",aux->prioridad,aux->siguiente->prioridad);
            puts("Listas fusionadas\n");
            mostrarLista(aux->siguiente->lista);
            puts("Fin lista\n");*/
         }else{
            printf("Creando prioridad:%d\n",aux->prioridad-1);
            aux2=(Multilista*) malloc(sizeof(Multilista));
            aux2->prioridad=aux->prioridad-1;
            aux2->lista=temp;
            aux2->siguiente=aux->siguiente;
            aux->siguiente = aux2;
         }
            aux=aux->siguiente; 
    }
    temp=juntarListas(aux->lista, temp);
    do{
    temp=mostrarListaD(temp, master->estadistica);
    }while(temp!=NULL);

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
		mostrarMultilista(master->cabeza);
        //mostrarLista(juntarListas(mostrarListaD(master->cabeza->lista,master->estadistica),master->cabeza->siguiente->lista));
        //mostrarLista(master->cabeza->lista);
        //puts("despachado");
       // mostrarLista(mostrarListaD(master->cabeza->lista,master->estadistica));
        despachar(master);
		//puts("C");
		//mostrarListaE(master->cabeza);
	break;
	case 2:
		/*printf("Longitud de la lista %d\n",Longitud(master->cabeza));
		printf("Que nodo desea borrar?");
		scanf("%d",&nodoaeliminar);
		master->cabeza = borrarNodo(master->cabeza,nodoaeliminar);*/
	break;
	case 3:
		//mostrarLista(master->cabeza);
	break;
	case 4:
		//mostrarListaD(master);
		//master->cabeza = NULL;
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

