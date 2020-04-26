#Homework 5 A01227885

#First we do the includes

#include <stdio.h>
#include <stdlib.h>

#A struct to save our data
struct differ{
    int indexes[10]; 
    int instr[10];
    int len;
};

#We define the funcitons we are gonna be using
char parser(char * word, int  length, int id);
void addIns( struct differ * paths, int i);
void same(char x, char * word, struct differ * paths, int * len);
void joinEl(struct differ * paths,struct differ * extra);
void copyDifferent(struct differ * src, struct differ * dest);
void genFile(char * word, int length, int bitInstr, int id);
void funcOne(char * word, struct differ * indx, int * len);
void funcTwo(char * word, struct differ  *paths, int * len);

#Our intructions matrix
char instr[5][13] = {"    1 -> 2;\n\0","    1 -> 3;\n\0","    1 -> 4;\n\0","    3 -> 5;\n\0","    3 -> 6;\n\0" };

#Our functions
char parser(char * word, int  length, int id){
    struct differ paths;
    paths.indexes[0] =0;
    paths.instr[0] = 0;
    paths.len=1;
    funcTwo(word, &paths,  &length);
    for(int i=0;i<paths.len;i++){
        if(paths.indexes[i] == length) 
        {
            genFile(word, length,  paths.instr[i], id);
            return 1;
        }
    }
    return 0;
}

void addIns( struct differ * paths, int i){
    for(int j =0 ;j< paths->len;j++) {
        paths->instr[j] = (paths->instr[j] ) | (1<<i);
    }
}

void same(char x, char * word, struct differ * paths, int * length){
    int newLen=0;
    for(int j = 0 ;j<paths->len ; j++){
        if(paths->indexes[j] < (*length)){
            if(word[paths->indexes[j]] == x){
                paths->indexes[newLen] = paths->indexes[j] + 1;
                paths->instr[newLen] = paths->instr[j];
                newLen++;
            }
        }
    }
    paths->len = newLen;
}

void joinEl(struct differ * paths,struct differ * extra){
    char isIn, i;
    i=0;
    while(i<extra->len){
        isIn=0;
        for(int j=0;j<paths->len;j++){
            if(paths->indexes[j] == extra->indexes[i]){
                isIn = 1;
                break;
            }
        }
        if(!isIn){
            paths->indexes[paths->len] = extra->indexes[i];
            paths->instr[paths->len] = extra->instr[i];
            paths->len+=1; 
        }
        i++;
    }
}

void copyDifferent(struct differ * src, struct differ * dest){
    dest->len = src->len;
    for(int j =0 ;j< src->len;j++){
        dest->indexes[j] = src->indexes[j];
        dest->instr[j] = src->instr[j];
    }
}

void genFile(char * word, int length, int bitInstr, int id){
    FILE *file;
    char buff[30]; 
    snprintf(buff, 30, "derivation_tree%d.dot", id);
    file=fopen(buff, "w");
    fprintf(file, "digraph G{\n");   
    fprintf(file, "    1 [label=\"S\"];\n");
    fprintf(file, "    2 [label=\"a\"];\n");
    fprintf(file, "    3 [label=\"B\"];\n");
    fprintf(file, "    4 [label=\"c\"];\n");
    fprintf(file, "    5 [label=\"b\"];\n");
    if(bitInstr==31) fprintf(file, "    6 [label=\"c\"];\n");
    int j;
    j=0;
    while(bitInstr>0){
        if(bitInstr&1) fprintf(file, "%s",instr[j]);
        bitInstr/=2;
        j++;
    }
    fprintf(file,"    labelloc=\"t\";\n");
    fprintf(file,"    label=\"");
    for(int i=0;i<length;i++){fprintf(file,"%c", word[i]);}
    fprintf(file,"\";\n");
    fprintf(file, "}\n");
    fclose(file);
}

void funcOne(char * word, struct differ * paths, int * len){
    struct differ c1;
    copyDifferent(paths , &c1);
    same('b', word, paths, len);
    addIns(paths, 3);
    same('c', word, paths, len);
    addIns(paths, 4);
    same('b', word, &c1, len); 
    addIns(&c1, 3);
    joinEl(paths, &c1);
}

void funcTwo(char * word, struct differ*  paths, int * len){
    same('a', word, paths, len);
    if(paths->len == 0) return;
    addIns(paths, 0);
    funcOne( word, paths, len);
    if(paths->len == 0) return;
    addIns(paths, 1);
    same('c', word, paths, len);
    addIns(paths, 2);
}

#Our main function to open the file.
int main()
{
    int cont =0;
    char result;
    char buff[50];
    char * line = NULL;
    FILE * fp;
    size_t len = 0;
    size_t read;
    fp = fopen("tokens.txt", "r");
    if (fp == NULL) exit(EXIT_FAILURE);
    while ((read = getline(&line, &len, fp)) != -1) {
        if(line[read-1] == '\n' || line[read-1] == '\0' ){
            result = parser(line,   read-1,  cont);
        }else{
            result = parser(line,   read,  cont);
        }
        snprintf(buff, 50, "Generated \"derivation_tree%d.dot\"", cont);
        printf("%s: %s\n", line, result?buff:"There was an error");
        cont++;
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
    return 0;
}

