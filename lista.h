#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "nodos.h"

Nodo* agregaNodoA(Nodo* cabeza, Nodo a){
	static int id = 0;
	Nodo* aux = cabeza;
	Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
	strcpy(nuevo->cadena,a.cadena);
	nuevo->caracter = a.caracter;
	nuevo->numero1 = a.numero1;
	nuevo->numero2 = a.numero2;
	nuevo->id = ++id;
	nuevo->siguiente = NULL;
	if(cabeza == NULL){
		cabeza = nuevo;
	}else if(nuevo->numero1 <= cabeza->numero1){
		nuevo->siguiente = cabeza;
		cabeza = nuevo;
	}else{
		while(aux->siguiente != NULL && aux->siguiente->numero1 < nuevo->numero1 ){
			aux = aux->siguiente;
		}
		if(aux->siguiente == NULL){
			aux->siguiente = nuevo;
		}else{
			nuevo->siguiente = aux->siguiente;
			aux->siguiente = nuevo;
		}
	}
	return cabeza;
}

Nodo* leerArchivoA(char* nombre, Nodo* cabeza){
	FILE* archivo = fopen(nombre,"r");
	Nodo nodo;
	if(archivo){
		while(!feof(archivo)){
			fflush(archivo);
			fscanf(archivo,"%s %c %d %d\n",nodo.cadena,&nodo.caracter,&nodo.numero1,&nodo.numero2);
			cabeza = agregaNodoA(cabeza,nodo);
		}
		printf("Archivo %s leido\n",nombre);
		fclose(archivo);
	}
	else
		puts("No se encuentra el archivo\n");
	return cabeza;
}
Nodo* leerArchivoD(char* nombre,Nodo* cabeza){
	FILE* archivo = fopen(nombre,"r");
	Nodo nodo;
	if(archivo){
		while(!feof(archivo)){
			fflush(archivo);
			fscanf(archivo,"%s %c %d %d\n",nodo.cadena,&nodo.caracter,&nodo.numero1,&nodo.numero2);
			cabeza = AgregaNodoP(cabeza,nodo);
		}
		printf("Archivo %s leido\n",nombre);
		fclose(archivo);
	}
	else
		puts("No se encuentra el archivo\n");
	return cabeza;
}
void crearArchivos(char* origen,char* destino_ascendente,char* destino_descendente){
	Nodo* cabezaA = NULL;
	Nodo* cabezaD = NULL;
	cabezaA = leerArchivoA(origen,cabezaA);
	FILE* ascendente = fopen(destino_ascendente,"w");
	FILE* descendente = fopen(destino_descendente,"w");
	Nodo* aux1 = cabezaA;
	if(ascendente && cabezaA){
		while(aux1 != NULL){
			fprintf(ascendente,"%s %c %d %d\n",aux1->cadena,aux1->caracter,aux1->numero1,aux1->numero2);
			aux1 = aux1->siguiente;
		}
		fclose(ascendente);
		cabezaD = leerArchivoD(destino_ascendente,cabezaD);
		if(descendente && cabezaD){
			while(cabezaD != NULL){
				fprintf(descendente,"%s %c %d %d\n",cabezaD->cadena,cabezaD->caracter,cabezaD->numero1,cabezaD->numero2);
				cabezaD = cabezaD->siguiente;
			}
		fclose(descendente);
		}
	}
}

