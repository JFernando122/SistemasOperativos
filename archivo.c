#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#define MAX_LINEAS 500
#define MAX_NUM 100
#define MIN_NUM 1

void crearArchivo(char* nombre){
	srand(time(NULL));
	FILE* archivo = fopen(nombre,"w");
	char caracter;
	int numero1,numero2;
	int aux;
	int aleatoriocadena;
	if(archivo){
		for(int i = 0 ; i < MAX_LINEAS; i++){
			do{
				caracter = (rand() % ('z' - 'A' + 1)) + 'A';
			}while(!(caracter < 90 || caracter > 97));
			aleatoriocadena = rand() % 10 + 5;
			for(int j = 0 ; j < aleatoriocadena; j++){
				do{
					aux = (rand() % ('z' - 'A' + 1)) + 'A';
				}while(aux > 90 && aux < 97);
				fprintf(archivo,"%c",aux);
			}
			fflush(archivo);
			fprintf(archivo," ");
			numero1 = (rand() % (MAX_NUM - MIN_NUM)) + MIN_NUM;
			numero2 = (rand() % (MAX_NUM - MIN_NUM)) + MIN_NUM;
			fprintf(archivo,"%c %d %d\n",caracter,numero1,numero2);
		}
	}
	fclose(archivo);
}

int main(){
	Nodo* cabeza = NULL;
	char nombre[25];
	char nombreA[25];
	char nombreD[25];
	puts("Dame el nombre del archivo");
	scanf("%s",nombre);
	strcpy(nombreA,nombre);
	strcpy(nombreD,nombre);
	strcat(nombre,".txt");
	strcat(nombreA,"1.txt");
	strcat(nombreD,"2.txt");
	crearArchivo(nombre);
	crearArchivos(nombre,nombreA,nombreD);
	return 0;
}
