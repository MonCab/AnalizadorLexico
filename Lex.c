#include <stdio.h>
#include <stdlib.h>
//En esta rama metere la vaina de la tabla extra
int main(int argc, char const *argv[]){
//Archivo I/O
	int errorHandler = 0, currentState = 0, yylineno=0,i,j;
	FILE* fptr;
	char *buffer;
	char nextC, help;
	long int sizeOfTheFile;
	int Matriz[20][24]= {{1,-1,-1,-1,-1,-1,2,-1,-1,3,3,6,6,4,8,8,8,8,7,9,9,9,9,19},
						 {-1,10,-1,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,12,12,12,12,12,12,12,-1,12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,-1,-1,-1,-1,-1,3,-1,-1,-1,4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,-1,-1,-1,-1,-1,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,14,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,14,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,14,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,12,12,12,12,12,12,17,-1,12,12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,-1,-1,-1,-1,-1,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,-1,18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,12,12,12,12,12,12,17,-1,12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,19}
						};
						for (i = 0 ; i <20; i++){
							for (j=0; j<=24; j++){
								printf("%d",Matriz[i][j]);
							}
														printf("\n\n");
						} 
	if ((fptr = fopen("test.txt","r")) == NULL){
		printf("Error");
		exit(1);
	}
	//Calcula numero de lineas para mostrar al detectar errores.
	while (!feof(fptr)){
	help = fgetc(fptr);
		if(help== '\n'){
			yylineno++;
		}
	};
	printf("\nNumber of lines %d", yylineno);


	//Calcula el numero de bytes que leerá.
	fseek(fptr, 0L, SEEK_END);
	sizeOfTheFile = ftell(fptr);
	fseek(fptr, 0L, SEEK_SET);
	//Busca un espacio en memoria para el buffer
	buffer = (char*)calloc(sizeOfTheFile, sizeof(char));
	if (buffer == NULL)
		printf("\n\nError en la lectura del archivo");
	//Error de memoria en el buffer (aun por programar)
	//errorHandler = 1;
	//errorHandling(1);
	fread(buffer, sizeof(char), sizeOfTheFile, fptr);
	fclose(fptr); 

	printf("\n\nIn the file : %s\n",buffer);




//Definicion de la estructura/tipo de dato
	typedef struct Token{
	int token_id;
	char type[50];
	char value[100];
	} Token;


	return 0;
}
