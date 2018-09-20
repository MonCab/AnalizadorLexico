#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//Falta programar el token generator
//Falta programar el errorHandler
//Siempre si faltan las frias.
//Falta concatenar el buffer yytext para guardar el valor de los tokens.

int charToInt(char header){
	//printf("%c\n",header );
	if (isdigit(header))
		return 9;
	if (isalpha(tolower(header))){
		switch(header){
			case 'i':
				return 1;
			case 'f':
				return 2;
			case 'e':
				return 3;
			case 'l':
				return 4;
			case 's':
				return 5;
			case 'v':
				return 6;
			case 'r':
				return 7;
			default:
				return 8;
		}
	}
	switch (header){
		case '@':
			return 0;
		case '=':
			return 10;
		case '>':
			return 11;
		case '<':
			return 12;
		case '.':
			return 13;
		case '+':
			return 14;
		case '-':
			return 15;
		case '/':
			return 16;
		case '*':
			return 17;
		case '!':
			return 18;
		case '(':
			return 19;
		case ')':
			return 20;
		case '{':
			return 21;
		case '}':
			return 22;
		case ' ':
			return 23;
		default:
			return -1;
	}
	return -1;
}

int main(int argc, char const *argv[]){
//Archivo I/O
	/*
		errorHandler Variable para errores
		yylineno contará las líneas
		final parte del algoritmo
		iterate recorre el archivo caracter por caracter
		help sirve para contar las líneas
		bufer es la parte de la memoria que guardará TODO el texto del archivo y se maneja como 
		un arreglo de chars.
		sizeofthefile define cuantos caracteres leerá y avanzará 'iterate'
		yytext es una variable para ir guardando el valor de un token
	*/
	int errorHandler = 0, currentState = 0, yylineno=0, final = -1,iterate = 0,j ;
	FILE* fptr;
	char *buffer;
	char nextC, help , yytext[100];
	long int sizeOfTheFile;

						//{-1,-1,-1,1,-1,1,1,-1,1,1,-1,-1,-1,1,1,1,-1,1,-1,1};
	int valueOfState[] ={-1,-1,-1,0,-1,0,0,-1,0,0,-1,-1,-1,0,0,0,-1,0,-1,0} ;
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

	if ((fptr = fopen("test.txt","r")) == NULL){
		printf("Error");
	}
	//Calcula numero de lineas para mostrar al detectar errores.
	while (!feof(fptr)){
	help = fgetc(fptr);
		if(help== '\n'){
			yylineno++;
		}
	}
	//Calcula el numero de bytes que leerá.
	fseek(fptr, 0L, SEEK_END);
	sizeOfTheFile = ftell(fptr);
	fseek(fptr, 0L, SEEK_SET);
	//Busca un espacio en memoria para el buffer
	buffer = (char*)calloc(sizeOfTheFile, sizeof(char));
	if (buffer == NULL)
		printf("\n\nError en la lectura del archivo");

	//Carga el texto en memoria
	fread(buffer, sizeof(char), sizeOfTheFile, fptr);


	//aquí se genera un ciclo infinito
	while (iterate <= sizeOfTheFile){
		//j se usa para simplificar la notación Matriz[][]
		j = charToInt(buffer[iterate]);
		if (Matriz[currentState][j] != -1){
			currentState = Matriz[currentState][j];
			printf("\n\nSe Agregó al buffer de lex el caracter : %c \n\n", buffer[iterate]);
			yytext[strlen(yytext)] =  buffer[iterate];
			final = valueOfState[currentState];
		}else{
			if (final != -1){
				//Token Generator Function
				printf("\n\n Se generó un token \n");
				currentState = 0;
				//Limpia el arreglo de yytext
				memset(yytext,0,100);
				
				
			}else{
				printf("\n\nError Lexico\n");
			}
		}
		iterate += sizeof(char);
		
	}
	

	fclose(fptr); 
//Definicion de la estructura/tipo de dato
	typedef struct Token{
	int token_id;
	int type;
	char value[100];
	} Token;


	return 0;
}
