#include <stdio.h>
#include <stdlib.h>
#include <getsym.h>
extern TOKEN tok;
extern FILE *infile;
extern FILE *outfile;

void error(char *s);
void statement(void);

void compiler(void){
	init_getsym();

	getsym();

	if (tok.attr == RWORD && tok.value == PROGRAM){

		getsym();

		if (tok.attr == IDENTIFIER){

			getsym();

			if (tok.attr == SYMBOL && tok.value == SEMICOLON){
				//statmentの始めで読込を行いたいのでここではgetsym()をしていない
				//getsym();

				statement();

				if (tok.attr == SYMBOL && tok.value == PERIOD){
					fprintf(stderr, "Parsing Completed. No errors found.\n");
				} else error("At the end, a period is required.");
			}else error("After program name, a semicolon is needed.");
		}else error("Program identifier is needed.");
	}else error("At the first, program declaration is required.");
}

void error(char *s){
	fprintf(stderr, "%s\n", s);
	exit(1);
}

//
// Parser
//

void statement(void){
	getsym();

	//数式を読み込んだとき
	if(tok.attr == NUMBER){
		fprintf(outfile,"loadi	r0,%d\n",tok.value);
		getsym();
		//各演算で分岐
		switch(tok.value){
			case PLUS:
					getsym();
					fprintf(outfile,"addi	r0,%d\n",tok.value);
					break;
			case MINUS:
					getsym();
					fprintf(outfile,"subi	r0,%d\n",tok.value);
					break;
			case TIMES:
					getsym();
					fprintf(outfile,"muli	r0,%d\n",tok.value);
					break;
			case DIV:
					getsym();
					fprintf(outfile,"divi	r0,%d\n",tok.value);
					break;
			default: 
					fprintf(outfile,"error\n"); 
					break;
		}
		//書き出し処理
		fprintf(outfile,"writed	r0\n");
		fprintf(outfile,"loadi r1,'\\n'\n");
		fprintf(outfile,"writec r1\n");
		//次のトークンで制御分岐
		getsym();
		if(tok.value == SEMICOLON){
			statement();
		}else if(tok.value == PERIOD){
			fprintf(outfile,"halt\n");
		}
	}else if(tok.value == BEGIN){
		//bigin:再帰呼び出し
		statement();
		//statementを抜けてくるときにendを読み込んでいるはず
		if(tok.value == END){
			getsym();
			if(tok.value == SEMICOLON){
				statement();
			}else if(tok.value == PERIOD){
				fprintf(outfile,"halt\n");
			}
		}else {
			fprintf(outfile,"error\n"); 
		}
	}else{
		fprintf(outfile,"error\n");
	}
}

