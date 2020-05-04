all:
	flex syntax_analaizer.l
	bison -d syntax_analaizer.y
	gcc -o syntax_analaizer syntax_analaizer.tab.c lex.yy.c -ly -ll

clean:
	rm syntax_analaizer
	rm syntax_analaizer.tab.h
	rm syntax_analaizer.tab.c
	rm lex.yy.c 
