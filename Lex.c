#include <stdio.h>
#include <stdlib.h>
//En esta rama metere la vaina de la tabla extra
int main(int argc, char const *argv[]){
//Archivo I/O
	int errorHandler = 0, currentState = 0, yylineno=0;
	FILE* fptr;
	char *buffer;
	char nextC, help;
	long int sizeOfTheFile;

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
