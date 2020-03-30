//Homework 3 A01227885

//We do the includes
%{
#include <stdio.h>
#include <stdlib.h>
%}

//For each symbol we translate what it means
%%
\/\/(.+)        ;
f               { fprintf(result, "floatdcl"); }
i               { fprintf(result, "intdcl"); }
p               { fprintf(result, "PRINT"); }
=               { fprintf(result, "assign"); }
[a-eghj-oq-z]   { fprintf(result, "id"); }
[0-9]+\.[0-9]+  { fprintf(result, "fnum"); }
[0-9]+          { fprintf(result, "inum"); }
\+              { fprintf(result, "plus"); }
-               { fprintf(result, "minus"); }
\*              { fprintf(result, "times"); }
\/              { fprintf(result, "division"); }
%%

//Our proccess which will read our data file and will print on out result fille, both exterrnal
int main(int argc, char **argv){
    extern FILE *data, *result;
    
    if( argc == 2){
        data = fopen(argv[1], "r");
        
        result = fopen("lex.out", "w");
        
        if( data != NULL && result != NULL){
            yylex();
        }
        else{
            printf("NotValid\n");
        }
    }
    else{
        printf("Usage: ./lexical_scan <input file>\n");
    }
    fclose(data);
    fclose(result);
}
