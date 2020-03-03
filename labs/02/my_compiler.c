#include <stdio.h>


int main(int argc, char **argv){
	FILE *f =fopen(argv[1], "r");
	char lines [100];
	int i =0;
	while (fscanf(f, "%[^\n]", lines)!=""){
		fscanf(f, "%[^\n]", lines);
		printf("Line" + str(i)+lines);
		i=i+1;
	}
}
