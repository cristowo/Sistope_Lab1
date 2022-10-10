#include "hijo.h"

/*
* calculos de los hijos (max, min, promedio)(procentaje)(gratis?)
* parametros: FILE *file1, FILE *file2, int Precio, int flag
* retorna: string con todos los calculos
*/
char* calculosHijo(FILE *fileaux, FILE *file, int priceOrig, int flag){
    //años iguales
    int num = getYear(fileaux);
    
    //creacion de arrays de ayuda
    int *id[num];
    int *year[num];
    int *restriction[num];
    int *soon[num];
    int *free[num];
    float price[num];
    char *win[num][3];
    char *mac[num][3];
    char *lin[num][3];
    char *name[num][1000];

    char *linea[1000];
    char *token;
    int i = 0;
    while(fgets(linea, 1000, file) != NULL && i < num){
        token = strtok(linea, ",");id[i] = atoi(token);
        token = strtok(NULL, ",");strcpy(name[i],token);
        token = strtok(NULL, ",");restriction[i] = atoi(token);
        token = strtok(NULL, ",");price[i] = atof(token);
        token = strtok(NULL, ",");soon[i] = atoi(token);
        token = strtok(NULL, ",");year[i] = atoi(token);
        token = strtok(NULL, ",");free[i] = atoi(token);  
        token = strtok(NULL, ",");strcpy(win[i],token);
        token = strtok(NULL, ",");strcpy(mac[i],token);
        token = strtok(NULL, ",");strcpy(lin[i],token);
        i++;
    }

    //calculo a mas caro, a mas barato y promedio
    int count = 0,posMore= 0 ,posLess = 0;
    float moreExpensive = 0, lessExpensive = 0,acum = 0;
    for(int i = 0; i < num; i++){
        if(price[i] >= priceOrig){
            //mas caro
            if(price[i] > moreExpensive){
                moreExpensive = price[i];
                posMore = i;
            }
            //mas barato
            if(price[i] < 1000000){
                lessExpensive = price[i];
                posLess = i;
            }
            //promedio
            acum += price[i];
            count++;
        }
    }
    char parteA[10000];
    if(count == 0){
        sprintf(parteA, "No hay juegos con el precio minimo %d\n", priceOrig);
    }else{
        sprintf(parteA, "El juego mas caro es: %s, con un precio de: %f\nEl juego mas barato es: %s, con un precio de: %f\nEl promedio de los juegos es: %f\n", name[posMore], price[posMore], name[posLess], price[posLess], acum/count);
    }
    
    //porcentaje de juegos por plataforma (no concideramos el precio minimo)
    int countWin = 0, countMac = 0, countLin = 0, countar = 0;
    for(int i = 0; i < num; i++){
        if(strcmp(win[i], "Yes") == 0){
            countWin++;
        }
        if(strcmp(mac[i], "Yes") == 0){
            countMac++;
        }
        if(strcmp(lin[i], "Yes") == 0){
            countLin++;
        }
        countar++;
    }

    char parteB[10000];
    sprintf(parteB, "El porcentaje de juegos para Windows es: %f\nEl porcentaje de juegos para Mac es: %f\nEl porcentaje de juegos para Linux es: %f\n", prom(countWin, countar), prom(countMac, countar), prom(countLin, countar));

    //todos los juegos gratis de un año
    int countFree = 0;
    float cero = 0;
    char *freeGames[num][1000];
    for(int i = 0; i < num; i++){
        if(price[i] == cero){
            strcpy(freeGames[countFree], name[i]);
            countFree++;
        }
    }
    char parteC[10000];
    if(countFree == 0){
        sprintf(parteC, "No hay juegos gratis este año \n");
    }else{
        sprintf(parteC, "Los juegos gratis del año son: \n");
        for(int i = 0; i < countFree; i++){
            sprintf(parteC, "%s%s\n", parteC, freeGames[i]);
        }

    }
    char *result;
    result = (char *)malloc(1000000000 * sizeof(char));
    sprintf(result, "Año: %d\n%s%s%s", year[0],parteA, parteB, parteC);

    return result;
}
/*
* manipula el resultado para que sea compatible
* parametros: int posicion, int b(flag), int precio
* retorna: string con el resultado
*/
char* obtnercalculos(int pos, int b, int price){
    FILE* file2 = fopen("intermedio.csv", "r");
    FILE *file3 = fopen("intermedio.csv", "r");
    fseek(file2, pos, SEEK_CUR);
    fseek(file3, pos, SEEK_CUR);

    char *result;
    result = (char *)malloc(100000 * sizeof(char));
    result = calculosHijo(file2, file3, price, b);

    fclose(file2);
    fclose(file3);

    return result;
    }