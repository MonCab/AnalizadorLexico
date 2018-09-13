#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//Falta programar el token generator
//Falta programar el errorHandler


//Definicion de la estructura/tipo de dato
typedef struct Token{
	char type[50];
	char value[100];
} Token;

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
		case '\n':
		case '\t':
			return 23;
		default:
			return -1;
	}
	return -1;
}

int tablaCompacta(int i, int j){
	//Valor de los elementos no nulos de toda la tabla
	int Valor[57]={1,2,10,11,11,11,3,15,15,15,15,4,15,15,15,15,
				14,5,6,7,7,7,7,7,7,7,7,7,12,15,15,8,7,7,7,7,
				7,7,13,7,7,9,15,10,3,15,12,7,7,7,7,7,7,13,7,7,14};

	//Columna que corresponde a cada elemento del vector Valor
	int Col[57]={0,6,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,
	1,3,1,2,3,4,5,6,7,8,9,9,10,2,4,1,2,3,4,5,6,7,8,9,5,3,9,13,10,
	9,1,2,3,4,5,6,7,8,9,23};

	//Se almacena la posición del vector valor donde comienzan los elementos de cada renglón
	int Fila[20]={0,17,19,28,29,30,31,32,41,42,43,45,46,47,56,57};

	//Contiene el número de elementos no nulos de cada renglón
	int Num[16]={17,2,9,1,1,1,1,9,1,1,2,1,1,9,1,0};

	int num, com, k;

	num = Num[i];

	if(num == 0)
		return -1;
	else{
		com = Fila[i];
		k = 0;
		while(k < num){
			if(Col[com+k] == j)
				return Valor[com + k];

			k++;
		}
	}
	return -1;
}

Token tokenGenerator(char *yytext, int currentState){
	Token token;

	switch(currentState){
		case 10:
			strcpy(token.type, "Constante entera");
			strcpy(token.value, yytext);
			break;
		case 11:
			if(strcmp(yytext, "=") == 0){
				strcpy(token.type, "Operador asignacion");
				strcpy(token.value, yytext);
			}else{
				strcpy(token.type, "Operadores relacionales");
				strcpy(token.value, yytext);
			}
			break;
		case 12:
			strcpy(token.type, "Constante decimales");
			strcpy(token.value, yytext);
			break;
		case 13:
			strcpy(token.type, "Identificadores");
			strcpy(token.value, yytext);
			break;
		case 14:
			break;
		case 15:
			if(strchr(yytext, '+') != NULL || strchr(yytext, '-') != NULL || strchr(yytext, '/') != NULL || strchr(yytext, '*') != NULL){
				strcpy(token.type, "Operadores aritmeticos");
				strcpy(token.value, yytext);
			}

			if(strcmp(yytext, "=") == 0){
				strcpy(token.type, "Operadores relacionales");
				strcpy(token.value, yytext);
			}

			if(strchr(yytext, '(') != NULL || strchr(yytext, ')') != NULL || strchr(yytext, '{') != NULL || strchr(yytext, '}') != NULL){
				strcpy(token.type, "Simbolos especiales");
				strcpy(token.value, yytext);
			}

			if(strcmp(yytext, "@") == 0){
				strcpy(token.type, "Palabras reservadas");
				strcpy(token.value, yytext);
			}
			break;
		default:
			printf("Error en la funcion tokenGenerator\n");
	}

	return token;
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
	char nextC, help , *yytext, auxConcat[2];
	yytext=(char*)malloc(1*sizeof(char));
	strcpy(yytext,"");
	long int sizeOfTheFile;
	Token token;

						//{-1,-1,-1,1,-1,1,1,-1,1,1,-1,-1,-1,1,1,1,-1,1,-1,1};
	int valueOfState[] ={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0} ;

	/*int Matriz[15][24]= {{1,-1,-1,-1,-1,-1,8,-1,-1,11,12,12,12,2,14,14,14,14,3,14,14,13},
						 {-1,4,-1,5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,-1,-1,-1,-1,-1,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,14,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,14,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,-1,7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,14,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,9,9,9,9,9,9,9,9,9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,9,9,9,9,9,9,10,9,9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,9,9,9,9,9,9,10,9,9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,-1,-1,-1,-1,-1,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,14,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13},
						 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
						};*/

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
		//if (Matriz[currentState][j] != -1){
		if(tablaCompacta(currentState, j) != -1){
			currentState = tablaCompacta(currentState, j); //Matriz[currentState][j];
			//printf("\n\nSe Agregó al buffer de lex el caracter : %c \n\n", buffer[iterate]);
			auxConcat[0] = buffer[iterate];
			auxConcat[1]='\0';
			yytext=(char*)realloc(yytext,(sizeof(yytext)+sizeof(buffer[iterate])+sizeof('\0')));
			strcat(yytext,auxConcat); 
			final = valueOfState[currentState];
		}else{
			if (final != -1){
				//Token Generator Function
				token = tokenGenerator(yytext, currentState);
				printf("\n\nToken generado: <%s, %s> ", token.type, token.value);
				//printf("\n\n Se generó un token %s \n" , yytext);

				currentState = 0;
				strcpy(yytext,"");
				
				
			}else{
				printf("\n\nError Lexico\n");
			}
		}
		iterate += sizeof(char);
		
	}
	

	fclose(fptr); 

	return 0;
}
