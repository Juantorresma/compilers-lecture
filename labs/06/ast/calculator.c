#include <stdio.h>

#include <stdlib.h>

#include <string.h>

/*Primero declaramos los headers de las funciones*/

int calculator(int n, char * input, char *output,int * indexA);

int operaciones(int n, char *input);

/*Ya definidas las desarrollamos*/

int operaciones(int n, char *input){
	
    short usados[256];
    int *indice = malloc(n*sizeof(char));
    int indexB=0;
    int actual=0;
    for(int i=0;i<256;i++){
	    usados[i] = 0; 
    }
    for (int i=0;i<n; i++){
        char caracter=input[i];
        if(caracter>='0' && caracter<='9'){
            indice[indexB++] = caracter-'0';
        }else{
            char *operation;
            switch (caracter)
            {
            case '+':
                operation="add";
                break;
            case '-':
                operation="sub";
                break;
            default:
                operation="mul";
                break;
            }
            int val2=  indice[--indexB];
            int val1 = indice[--indexB];
            char * v2,*v1;
            char* acc="acum";
            if(val2>=10){
                 v2= acc;
                 usados[val2-10] =0;
            }else{
                v2 = (char *)malloc(sizeof(char) *2 );
                v2[0]= ((char)(val2+'0'));
                v2[1]= 0;
            }
            if(val1>=10){
                 v1= acc;
                 usados[val1-10] =0;
            }else{
                v1 = (char *)malloc(sizeof(char) *2 );
                v1[0]= ((char)(val1+'0'));
                v1[1]= 0;
            }

            for(int s=0;s<256;s++){ 
                if(usados[s] == 0){
                    indice[indexB++] = 10+s;
                    usados[s] = 1;
                    actual=s;
                    break;
                }
            }
            if(val2>=10){
                
                if(val1>=10){
                    printf("%s &%s%d, &%s%d, %s%d\n", operation, v1,val1-10, v2,val2-10, acc,actual);
                }else{
                    printf("%s %s, &%s%d, %s%d\n", operation, v1, v2,val2-10, acc,actual);
                }
            }else{
                if(val1>=10){
                    printf("%s &%s%d, %s, %s%d\n", operation,  v1,val1-10,v2, acc,actual);
                }else{
                    printf("%s %s, %s, %s%d\n", operation, v1, v2, acc, actual);
                }
            }
        }
    }
}

int calculator(int n, char * input, char *output,int * indexA){
    (*indexA)=0;
    int digitos=0;
    int *indice = malloc(n*sizeof(char));
    int indexB=0;
    int done=0;
    for(int i=0;i<n;i++){
        if(done) break;
        char c= input[i];
        switch (c) {
        case '\t':
        case ' ':
            continue;
            break;
        case '\n':
            done=1;
            break;
        case '+':
        case '-':
            digitos=0;
            while (1){
                if( indexB==0 || indice[indexB-1] == '('){
                    indice[indexB++] = c;
                    break; 
                }else{
                    output[(*indexA)++]=indice[--indexB];
                }
            }     
            break;
        case '*':
        case '(':
            digitos=0;
            indice[indexB++] = c;
            break;
        case ')':
            digitos=0;
            while (1){
                
                if( indexB==0) return -1;
                char op = indice[--indexB]; 
                if(op=='(') break;
                output[(*indexA)++]=op;
                
            }   
            break;
        default:
            if(c==' ' || c=='\t') continue;
            if(c<'0' || c>'9') return -1;
            if(digitos) return -1;
            output[(*indexA)++]=c;
            digitos++;
            break;
        }
    }
    while(indexB>0) {
		char op = indice[--(indexB)];
		if(op=='(') return -1;
		output[(*indexA)++] = op;
	}
	return 0;
}



int main(int argc, char ** argv){
    if(argc!=2){
        printf("Favor de verificarl el numero de argumentos.\n");
        return -1;
    }
    FILE *fd;
    fd = fopen(argv[1], "r");
    if(fd==NULL){
        printf("Hubo un error al abrir el archivo. \n");
        return -1;
    }
    char line[1024];
    while(fgets(line, 1024, fd)!=NULL){
        int n= strlen(line);
        int index = 0;
        for(int q=0;q<n;q++){
                if(line[q]=='\n') break;
                printf("%c", line[q]);
            }printf("\n");
        char * output =(char *) malloc((n+1)*sizeof(char));
        if(calculator( n, line, output, &index)==0){
            for(int i=0;i<index;i++){
                printf("%c", output[i]);
            }printf("\n\n");
            operaciones(index,output);
        }else{
            printf("Hay un error sintactico.\n");
        }
        printf("\n");
    }
}
