%{	
    #include<stdio.h>	

    #include <stdlib.h>	

    #include<string.h>	


    extern int yy_scan_string();	

    extern int yylex_destroy();	

    extern FILE *yyin;	

    extern int yylex();	
%}	

/*We start with S, and build the grammar  S -> aBc, B -> bc | b */	
%start s	
%% 	
    s:  'a' b 'c'    	
        ;	
    b:  'b' 'c' | 'b' 	
        ;	
%%	


/* The main routin where we check number of given parameters and read each string to determine if they are valid or not.*/	
int main(int argc, char **argv) {	
    FILE    *fd;	

    if (argc != 2) {	
        printf("Please check the number of parameters.\n");	
        return -1;	
    }	

    if (!(fd = fopen(argv[1], "r"))){	
        printf("Error. \n");	
        return -1;	
    }	

    size_t len;	
    char * line = NULL;	
    int notValid;	
    len= 0;	

    while (getline(&line, &len, fd) != -1) {	
        printf("%s", line);	
        yy_scan_string(line);	
        notValid = yyparse();	
        printf("%sAccepted\n",  (notValid ? "No ": ""));	
        yylex_destroy();	
    }	

    fclose(fd);	
    if (line){	
      free(line);	
    }	

	return 0;	
}	
