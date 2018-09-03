#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//En esta rama metere la vaina de la tabla extra
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
	int errorHandler = 0, currentState = 0, yylineno=0, final = -1,iterate = 0,j ;
	FILE* fptr;
	char *buffer;
	char nextC, help , yytext[100] = "";
	long int sizeOfTheFile;
	int valueOfState[] ={-1,-1,-1,-1,-1,-1,-1,-1,0,0,-1,-1,-1,-1,0,0,-1,-1,-1,-1} ;
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
		exit(1);
	}
	//Calcula numero de lineas para mostrar al detectar errores.
	while (!feof(fptr)){
	help = fgetc(fptr);
		if(help== '\n'){
			yylineno++;
		}
	};
	//Calcula el numero de bytes que leerá.
	fseek(fptr, 0L, SEEK_END);
	sizeOfTheFile = ftell(fptr);
	fseek(fptr, 0L, SEEK_SET);
	//Busca un espacio en memoria para el buffer
	buffer = (char*)calloc(sizeOfTheFile, sizeof(char));
	if (buffer == NULL)
		printf("\n\nError en la lectura del archivo");
	//Error de memoria en el buffer (aun por programar)
	//Carga el texto en memoria
	fread(buffer, sizeof(char), sizeOfTheFile, fptr);



	//while (iterate < sizeOfTheFile){
		j = charToInt(buffer[iterate]);
		//printf("%d\n",j );
		//printf("%c\n", buffer[iterate]);
		//printf("%c\n", buffer[iterate+sizeof(char)]);
		//printf("%d-%d\n",currentState,charToInt(buffer[iterate]));
		printf("%d",Matriz[currentState][j]);
		if (Matriz[currentState][j] != -1){
			printf("\nHere");
			currentState = Matriz[currentState][j];
			printf("%c\n", buffer[iterate]);
			//strcpy(yytext,buffer[iterate]);
			printf("\n\nSe Agregó al buffer de lex");
			iterate += sizeof(char);
			printf("%d\n", iterate);
			final = valueOfState[currentState];
		}else{
			if (final != -1){
				//Token Generator Function
				printf("\n\n Se generó un token");
				currentState = 0;
				//return Token
			}else{
				//printf("\n\nError Lexico");
			}
		}
	//}
		printf("Size of File :%li\n", sizeOfTheFile);
		j = charToInt(buffer[iterate]);
		//printf("%d\n",j );
		//printf("%c\n", buffer[iterate]);
		//printf("%c\n", buffer[iterate+sizeof(char)]);
		//printf("%d-%d\n",currentState,charToInt(buffer[iterate]));
		printf("%d",Matriz[currentState][j]);
		if (Matriz[currentState][j] != -1){
			currentState = Matriz[currentState][j];
			printf("%c\n", buffer[iterate]);
			//strcpy(yytext,buffer[iterate]);
			printf("\n\nSe Agregó al buffer de lex ");
			iterate += sizeof(char);
			printf("%d\n", iterate);
			final = valueOfState[currentState];
		}else{
			if (final != -1){
				//Token Generator Function
				printf("\n\n Se generó un token");
				currentState = 0;
				//return Token
			}else{
				//printf("\n\nError Lexico");
			}
		}




	fclose(fptr); 
//Definicion de la estructura/tipo de dato
	typedef struct Token{
	int token_id;
	char type[50];
	char value[100];
	} Token;


	return 0;
}
