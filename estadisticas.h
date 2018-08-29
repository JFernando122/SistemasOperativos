#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo_E{
	int tiempo_terminacion;
	int tiempo_ejecucion;
	int id;
	struct Nodo_E* siguiente;
}Nodo_E;

Nodo_E* agregarNodoE(Nodo_E* cabeza, Nodo_E a){
	Nodo_E* nuevo = (Nodo_E*) malloc(sizeof(Nodo_E));
	Nodo_E* aux = cabeza;
	nuevo->tiempo_terminacion = 0;
	nuevo->tiempo_ejecucion = a.tiempo_ejecucion;
	nuevo->id = a.id;
	nuevo->siguiente = NULL;
	if(cabeza){
		while(aux->siguiente != NULL)
			aux = aux->siguiente;
		aux->siguiente = nuevo;
	}else
		cabeza = nuevo;
	return cabeza;
}

Nodo_E* buscarNodo_E(Nodo_E* cabeza, int id){
	Nodo_E* aux = cabeza;
	if(cabeza != NULL){
		while(aux != NULL && aux->id != id)
			aux = aux->siguiente;
	}
	return aux;
}
void mostrarE(Nodo_E* cabeza){
	int promedioterminacion = 0, promedioespera = 0,total = 0;
	while(cabeza != NULL){
		printf("Proceso: %d Tiempo de terminacion %d: tiempo de ejecucion: %d Tiempo de espera: %d\n",cabeza->id,cabeza->tiempo_terminacion,cabeza->tiempo_ejecucion,cabeza->tiempo_terminacion-cabeza->tiempo_ejecucion);
		promedioterminacion+= cabeza->tiempo_terminacion;
		promedioespera+= cabeza->tiempo_terminacion-cabeza->tiempo_ejecucion;
		total++;
		cabeza = cabeza->siguiente;
	}
	printf("Tiempo de terminacion promedio: %d tiempo de espera promedio: %d\n",promedioterminacion/total,promedioespera/total);
}
