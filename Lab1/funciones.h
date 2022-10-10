#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

//cantidad de juegos
int contarTotal(FILE *file, int year);

//cuenta la cantidad de años que hay en el archivo
int contarTotalonly(FILE *file, int year);

//retorna la posicion en donde inicia (ftell)
int posicionB(char *name, int i);

//retorna el año de la primera posicion
int getYear(FILE *file);

//retorna el porcentaje
float prom(int a, int b);