#include <stdio.h>

#include <stdlib.h>

#include <string.h>

/*Primero declaramos los headers de las funciones*/

int calculator(int n, char * input, char *output,int * indexA);

int operaciones(int n, char *input);

/*Ya definidas las desarrollamos*/

int operaciones(int n, char *input){
	
    short usados[256];
    for(int i=0;i<256;i++){
	    usados[i] = 0; 
    }
    int *indice = malloc(n*sizeof(char));
    int indexB=0;
    int currentReg=0;
    for (int i=0;i<n; i++){
        char c=input[i];
        if(c>='0' && c<='9'){
            indice[indexB++] = c-'0';
        }else{
            char *operation;
            switch (c)
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
            char* acc="accm";
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
                    currentReg=s;
                    break;
                }
            }
            if(val2>=10){
                
                if(val1>=10){
                    printf("%s &%s%d, &%s%d, %s%d\n", operation, v1,val1-10, v2,val2-10, acc,currentReg);
                }else{
                    printf("%s %s, &%s%d, %s%d\n", operation, v1, v2,val2-10, acc,currentReg);
                }
            }else{
                if(val1>=10){
                    printf("%s &%s%d, %s, %s%d\n", operation,  v1,val1-10,v2, acc,currentReg);
                }else{
                    printf("%s %s, %s, %s%d\n", operation, v1, v2, acc, currentReg);
                }
            }
        }
    }
}

int calculator(int n, char * input, char *output,int * indexA){
    (*indexA)=0;
    int digitos=0;
    int *stk = malloc(n*sizeof(char));
    int sIndx=0;
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
                if( sIndx==0 || stk[sIndx-1] == '('){
                    stk[sIndx++] = c;
                    break; 
                }else{
                    output[(*indexA)++]=stk[--sIndx];
                }
            }     
            break;
        case '*':
        case '(':
            digitos=0;
            stk[sIndx++] = c;
            break;
        case ')':
            digitos=0;
            while (1){
                
                if( sIndx==0) return -1;
                char op = stk[--sIndx]; 
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
    while(sIndx>0) {
		char op = stk[--(sIndx)];
		if(op=='(') return -1;
		output[(*indexA)++] = op;
	}
	return 0;
}



int main(int argc, char ** argv){
    if(argc!=2){
        printf("Incorrect number of arguments. Please add the file path to analyze. Aborting\n");
        return -1;
    }
    FILE *fd;
    fd = fopen(argv[1], "r");
    if(fd==NULL){
        printf("File doesn't exist. Aborting\n");
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
            printf("There is a sintax error in the sentence.\n");
        }
        printf("\n");
    }
}
