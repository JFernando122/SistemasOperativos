#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodos.h"
#define null NULL

Nodo* leerArchivo(char* nombre, Nodo* cabeza){
	FILE* archivo = fopen(nombre,"r");
	Nodo nodo;
	if(archivo){
		while(!feof(archivo)){
			fscanf(archivo,"%s %c %d %d\n",nodo.cadena,&nodo.caracter,&nodo.numero1,&nodo.numero2);
			cabeza = agregaNodo(cabeza,nodo);
		}
		printf("Archivo %s leido\n",nombre);
		fclose(archivo);
	}
	else
		puts("No se encuentra el archivo\n");
	return cabeza;
}
int main(int argc, char *argv[]) {
	int opcion,nodoaeliminar;
	char nombredelarchivo[20];
	Nodo* cabeza = NULL;
	do{
	puts("¿Que desea hacer?");
	printf("1.- Leer archivo   2.-Borrar nodo   3.-Mostrar lista   4.-Despachar  5.-Salir\n");
	scanf("%d",&opcion);
	switch(opcion){
	case 1:
		printf("Escriba el nombre del archivo.\n");
		scanf("%s",nombredelarchivo);
		strcat(nombredelarchivo,".txt");
		cabeza = leerArchivo(nombredelarchivo,cabeza);
		//mostrarListaE(cabeza);
	break;
	case 2:
		printf("Longitud de la lista %d\n",Longitud(cabeza));
		printf("¿Que nodo desea borrar?");
		scanf("%d",&nodoaeliminar);
		cabeza = borrarNodo(cabeza,nodoaeliminar);
	break;
	case 3:
		mostrarLista(cabeza);
	break;
	case 4:
		mostrarListaD(cabeza);
		cabeza = NULL;
	break;
	case 5:
		puts("Bonito dia...");
	break;
	case 11:
		system("archivo.exe");
	break;
	case 12:
		system("./archivo");
	default:
	puts("Opcion invalida. Intente de nuevo.");
	break;
	}
	}while(opcion!=5);
	return 0;
}

