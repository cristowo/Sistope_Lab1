#include "padre.h"

/*
* crea el archivo intermedio y lo ordena
* parametros: char nombre archivo, int año
* retorna: void
*/
void ordenarycrear(char *inputFile, int year){
  FILE *file = fopen(inputFile, "r");
  int num = contarTotal(file, year);    //para ver la cantidad de juegos en el año
  fclose(file);
//---------------------------------------------
  //crea el archivo intermedio
  int *id[num];
  char *nombre[num][100];
  int *restriccion_edad[num];
  float precio[num];
  bool *soon[num];
  int *anio[num];
  bool *gratis[num];
  char *win[num][3];
  char *mac[num][3];
  char *lin[num][3];
//--------------------------------------------- 
  file = fopen(inputFile, "r");
  char *linea[1000];
  char *token;
  int i = 0;
  while(fgets(linea, 1000, file) != NULL && i < num){
    token = strtok(linea, ",");id[i] = atoi(token);
    token = strtok(NULL, ",");strcpy(nombre[i],token);
    token = strtok(NULL, ",");restriccion_edad[i] = atoi(token);
    token = strtok(NULL, ",");precio[i] = atof(token);
    token = strtok(NULL, ",");soon[i] = atoi(token);
    token = strtok(NULL, ",");anio[i] = atoi(token);
    token = strtok(NULL, ",");gratis[i] = atoi(token);  
    token = strtok(NULL, ",");strcpy(win[i],token);
    token = strtok(NULL, ",");strcpy(mac[i],token);
    token = strtok(NULL, ",");strcpy(lin[i],token);
    if(anio[i] >= year){i++;}
  }
  fclose(file);

  //ordenar ascendete
  int aux;
  char aux2[1000];
  for(int i = 0; i < num; i++){
    for(int j = 0; j < num; j++){
      if(anio[i] < anio[j]){
        aux = anio[i];
        anio[i] = anio[j];
        anio[j] = aux;
        aux = id[i];
        id[i] = id[j];
        id[j] = aux;
        aux = restriccion_edad[i];
        restriccion_edad[i] = restriccion_edad[j];
        restriccion_edad[j] = aux;
        aux = soon[i];
        soon[i] = soon[j];
        soon[j] = aux;
        aux = gratis[i];
        gratis[i] = gratis[j];
        gratis[j] = aux;
        aux = precio[i];
        precio[i] = precio[j];
        precio[j] = aux;
        strcpy(aux2, nombre[i]);
        strcpy(nombre[i], nombre[j]);
        strcpy(nombre[j], aux2);
        strcpy(aux2, win[i]);
        strcpy(win[i], win[j]);
        strcpy(win[j], aux2);
        strcpy(aux2, mac[i]);
        strcpy(mac[i], mac[j]);
        strcpy(mac[j], aux2);
        strcpy(aux2, lin[i]);
        strcpy(lin[i], lin[j]);
        strcpy(lin[j], aux2);
      }}}
  //crea el archivo intermedio
  FILE *intermedio = fopen("intermedio.csv", "w");
  i = 0;
  while(i<num){
    fprintf(intermedio, "%d,%s,%d,%f,%d,%d,%d,%s,%s,%s", id[i], nombre[i], restriccion_edad[i], precio[i], soon[i], anio[i], gratis[i], win[i], mac[i], lin[i]);
    i++;
  }
  fclose(intermedio);}
  
  /*
  * cuenta la cantidad de juegos en el año
  * parametros: int num de creacion del fork
  * retorna: int
  */
  int giveme(int i){
    FILE *file2 = fopen("intermedio.csv", "r");
    char *linea[1000];
    char *token;
    int k = 0, aux = 0;
    while(fgets(linea, 1000, file2) != NULL && k != posicionB("intermedio.csv", i)){
      aux=ftell(file2);                   //guarda la posicion para darsela al hijo
      token = strtok(linea, ",");
      k++;
    }//NOTA MENTAL: usar aux xd
    fclose(file2);
    return aux;
  }