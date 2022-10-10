#include "funciones.h"

/*
* cantidad de juegos
* parametros: file archivo, int año
* retorna: int cantidad de juegos
*/
int contarTotal(FILE *file, int year){
  char *linea[1000];
  char *token;
  int i=0;
  while(fgets(linea, 1000, file) != NULL){
    token = strtok(linea, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    if(atoi(token) >= year){
    i++;
    }
  }return i;}

/*
* cuenta la cantidad de años que hay en el archivo
* parametros: file archivo, int año
* retorna: int cantidad de años
*/
int contarTotalonly(FILE *file, int year){
  char *linea[1000];
  char *token;
  int i=0;
  int currentYear = year-1; //menos 1 para que entre el primer año, (sabemos desde antes que ya esta ordeando ascendemente)
  while(fgets(linea, 1000, file) != NULL){
    token = strtok(linea, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    if(atoi(token) >= year && atoi(token) > currentYear){
    i++;
    currentYear = atoi(token);
    }
  }return i;}

/*
* retorna la posicion en donde inicia (ftell)
* parametros: int i, char nombre archivo
* retorna: int posicion
*/

int posicionB(char *name, int i){
  FILE *file = fopen(name, "r");
  char *linea[1000];
  char *token;
  int yearaux = 0;
  int j = 0, k = 0;
  while(fgets(linea, 1000, file) != NULL){
    token = strtok(linea, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
  if(yearaux == 0){
    yearaux = atoi(token);}
  //k++;
  if(yearaux < atoi(token)){
    yearaux = atoi(token);  
    j++;
  }
  if(j == i){
    fclose(file);
    return k;
  }
  k++;
  }
}

/*
* retorna el año de la primera posicion
* parametros: FILE *file
* retorna: int año
*/
int getYear(FILE *file){
  char *linea[1000];
  char *token;
  int i=0, j=0;
  while(fgets(linea, 1000, file) != NULL){
    token = strtok(linea, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    if(i==0){i = atoi(token);} //caso incial
    if(i == atoi(token)){j++;} //si el año es igual al anterior, se suma
  }return j;}

/*
* retorna el porcentaje
* parametros: int a, int b
* retorna: float porcentaje
*/
float prom(int a, int b){
  return (float)(a*100/b);
}