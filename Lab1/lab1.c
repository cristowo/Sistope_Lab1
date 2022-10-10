#include "funciones.h"
#include "padre.h"
#include "hijo.h"
#define WRITE 1
#define READ 0

// ./lab1 -i datos_juegos_1000.cvs -o salita.txt -d 2018 -p 20.03 -b

// tomar en cuenta que para la ejecucion del programa
// el archivo .cvs debe estar sin fallas (funciona con las "," mal puestas pero no es la idea XD)
// estas fallas son las "," mal puestas.

int main(int argc, char *argv[]) {
  // Se definen las variables a utilizar
  int year = 0, price = 0, option, b = 0;
  char *inputFile = NULL , *outputFile = NULL;
  int pid;

  //PUNTO 1 --------------------------------------------------------------------
  while ((option = getopt(argc, argv, "i:o:d:p:b")) != -1) {
    switch (option) {
      case 'i':  // nombre del archivo de entrada
        inputFile = optarg;
        break;
      case 'o':  // nombre del archivo de salida
        outputFile = optarg;
        break;
      case 'd':  // año del juego
        sscanf(optarg, "%d", &year);
        break;
      case 'p':  // precio minimo del juego
        sscanf(optarg, "%d", &price);
        break;
      case 'b':  // bandera | flag | opcional
        b = 1;
        break;
      case '?':
        exit(0);
      default:  // En caso que no se haya ingresado alguna flag obligatoria, se
                // aborta la ejecucion
        abort();
    }
  }
  // Validaciones / Lectura del archivo
  FILE *file = fopen(inputFile, "r");
  if (file == NULL) {
    printf("Error al abrir el archivo de entrada \n");}fclose(file);
  //--------------------------------------------------------------------------------

  // PUNTO 3-----------------------------------------------------------------
  ordenarycrear(inputFile, year); // ordena y crea el archivo intermediario
  //-------------------------------------------------------------------------

  FILE *file2 = fopen("intermedio.csv", "r");
  int num = contarTotalonly(file2, year), i=0;
  fclose(file2);

  //PUTNTO 2-4-----------------------------------------------------------------
  int pos = 0, posf = 0;
  while ( i < num){         //padre crea tantos hijos como años hayan
    pid = fork();
    pos = giveme(i);      //el padre le da al hijo la posicion (give hace uso del ftell())
    posf= giveme(i+1);    //el padre le da al hijo la posicion final (give hace uso del ftell())

    if(pid == 0){
      break;
    }
    i++;
  } //el hijo sale del ciclo
  //---------------------------------------------------------------------------

  //PUNTO 5 - 6----------------------------------------------------------------
  if(pid == 0){

    char *result;
    result = (char *)malloc(100000 * sizeof(char));
    result =  obtnercalculos(pos, b, price);          //dentro de aqui se hace uso del fseek()

    char *archivoHijo[30];
    sprintf(archivoHijo, "hijo%d.txt", i);
    FILE *file3 = fopen(archivoHijo, "w");
    fprintf(file3, "%s", result);
    fclose(file3);
    if(b == 1){printf("%s", result);}
    free(result);
  }
  while(wait(NULL) > 0); //el padre espera a que todos los hijos terminen
  //PUNTO 7-8-9---------------------------------------------------------------
  if(pid != 0){ 
  FILE *file4 = fopen(outputFile, "w");
  for(int j = 0; j < num; j++){
    char *archivoHijo[30];
    sprintf(archivoHijo, "hijo%d.txt", j);
    FILE *file5 = fopen(archivoHijo, "r");
    char *linea[10000];
    while(fgets(linea, 10000, file5) != NULL){
      fprintf(file4, "%s", linea);
    }
    fprintf(file4, "\n");
    fclose(file5);
  }
  fclose(file4);
  }
  //--------------------------------------------------------------------------
}