
#include <stdio.h>

FILE *archivo;
int espacios, linea, bandera_esp, bandera_com, bandera_mul_com;
int contador = 0;
int lineas[30000];
char caracteres[8] = {'{', '}', '(', ')' , '[', ']', '\'', '\"'};

struct datos{
	int valor;
	int linea;
	int indentacion;
};

struct datos recibido[30000];

char valor_desbalanceado(char val){
	switch (val){
		case '(': return ')';
		case '[': return ']';
		case '{': return '}';
		case ')': return '(';
		case ']': return '[';
		case '}': return '{';
		case '\"': return '\"';
		case '\'': return '\'';
		default: return ' ';
	}
}

int contiene(char val, char *arr, int start, int end){
	for (int i = start; i < end; i++)
		if (arr[i] == val)
			return 1;
		return 0;
}

int comparar(char val1, char val2){
	if (val1 == '(' && val2 == ')') return 1;
	else if (val1 == '[' && val2 == ']') return 1;
	else if (val1 == '{' && val2 == '}') return 1;
	else if (val1 == '\"' && val2 == '\"') return 1;
	else if (val1 == '\'' && val2 == '\'') return 1;
	return 0;
}

void desbalanceado(){
	int errores = 0;
	for (int i = 0; i < contador; i++){
		if (contiene(recibido[i].valor, caracteres, 2, 8)){
			printf("There is a missing %c error in this linea: %d\n", valor_desbalanceado(recibido[i].valor), recibido[i].linea + 1);
			errores++;
		}else if (contiene(recibido[i].valor, caracteres, 0, 1)){
			for (int j = recibido[i].linea + 1; j <= linea; j++){
				if (recibido[i].indentacion == lineas[j]){
					printf("There is a missing %c error in this linea: %d\n", valor_desbalanceado(recibido[i].valor), j+1);
					errores++;
					break;
				}
			}
		}else if (contiene(recibido[i].valor, caracteres, 1, 2)){
			for (int j = recibido[i].linea - 1; j >= 0; j--){
				if (recibido[i].indentacion == lineas[j]){
					printf("There is a missing %c error in this linea: %d\n", valor_desbalanceado(recibido[i].valor), j + 1);
					errores++;
					break;
				}

			}
		}
	}
	if (!errores)
		printf("There is no errors.\n");
}


void checar_si_balanceados(){
	for (int i = 0; i < contador - 1; i++){
		for (int j = i + 1; j < contador; j++){
			if (comparar(recibido[i].valor, recibido[j].valor) && recibido[i].indentacion == recibido[j].indentacion){
				if (recibido[i].valor == '\"' || recibido[i].valor == '\'')
					while (i + 1 <= j - 1){
						recibido[i].valor = 0;
						recibido[j].valor = 0;
						i++;
						j--;
					}
				recibido[i].valor = 0;
				recibido[j].valor = 0;
			}
		}
	}
}





void buscar_valores(char val, int l, int s){
	struct datos d = {val, l, s};
	if (contiene(val, caracteres,0, 8))
		recibido[contador++] = d;
}




int main(int argc, char *argv[]){
	if (argc != 2){
		printf("Error: 1 argument is required, %d were passed.\n", argc - 1);
		return -1;
	}
	archivo = fopen(argv[1], "r");
	linea = 0;
	bandera_esp = 0;
	bandera_com = 0;
	bandera_mul_com = 0;
	char l[250];
	while ((fgets(l, sizeof(l), archivo))){
		for (int i = 0; l[i] != '\0'; i++){
			if (l[i] == '/' && l[i+1] == '/')
				break;
			else if (l[i] == '/' && l[i + 1] == '*')
				bandera_mul_com = 1;
			else if (l[i] == '*' && l[i + 1] == '/')
				bandera_mul_com = 0;
			else if (l[i] == ' ' && !bandera_esp)
				espacios++;
			else
				bandera_esp = 1;
			if (l[i - 1] != '\\' && !bandera_com && !bandera_mul_com)
				buscar_valores(l[i], linea, espacios);
			}
		lineas[linea] = espacios;
		espacios = 0;
		bandera_esp = 0;
		bandera_com = 0;
		linea++;
	}
	checar_si_balanceados();
	desbalanceado(recibido, contador);

}
