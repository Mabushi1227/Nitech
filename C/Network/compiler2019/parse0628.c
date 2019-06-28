#include <stdio.h>
#include <stdlib.h>
#include <getsym.h>
#include <string.h>

extern TOKEN tok;
extern FILE *infile;
extern FILE *outfile;

typedef struct 
{
	int addr;
	char v[MAXIDLEN+1];
}s_entry;

s_entry s_table[32];
int count = 0;  //変数の数を保存
int offset; //使用レジスタの制御
int OffsetFlag = 0; //offsetを継続して使うときに1,0のときはoffsetを1にしておく
int label = 0; //ラベル数
int looping = 0;

void error(char *s);
void outblock(void);
void statement(void);
void expression(int offset);
void condition(int offset, int order);  //order 0->if, 1->while
 
int getxaddr();
int getlabel(int plus);  //使用ラベルの管理,前半ラベル->plus=0,後半ラベルplus=1 
void compare();

void compiler(void){
	init_getsym();

	getsym();

	if (tok.attr == RWORD && tok.value == PROGRAM){

		getsym();

		if (tok.attr == IDENTIFIER){

			getsym();

			if (tok.attr == SYMBOL && tok.value == SEMICOLON){

				//getsym();
				outblock();

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
void outblock(void){
	getsym();
	//fprintf(outfile,"%d",tok.value);
	if(tok.value == VAR){
		do{
			getsym();
			if(tok.attr == IDENTIFIER){
				s_table[count].addr = count; 
				strcpy(s_table[count].v, tok.charvalue);
				//デバッグ用
				//fprintf(outfile,"%s\n",s_table[count].v);

				count++;
			}
			getsym();
		}while(tok.value == COMMA);

		if(tok.value == SEMICOLON){
			statement();
		}else{ 
			printf("error\n");
		}
	}
}

void statement(void){
	int r;
	 
	if(OffsetFlag){
		offset++;
	}else{
		offset = 0;
	} 

	getsym();

	printf("%d\n",tok.value);

	if(tok.attr == IDENTIFIER){
		//代入先のアドレス
		r = getxaddr();
		getsym();
		if(tok.value == BECOMES){
			getsym();
			expression(offset);
			fprintf(outfile,"loadr	r%d,r%d\n",r,count+offset);
			//fprintf(outfile,"%d\n",tok.value);
		}else if(tok.value == PERIOD){
			fprintf(outfile,"halt\n");
		}
	}else if(tok.value == BEGIN){
		//bigin:再帰呼び出し
		do{
			statement();
		}while(tok.value == SEMICOLON);

		//statementを抜けてくるときにendを読み込んでいるはず
		if(tok.value == END){
			getsym();
			if(tok.value == SEMICOLON){
				//statement();  
			}else if(tok.value == PERIOD){
				fprintf(outfile,"halt\n");
			}
		}else{
			printf("%d\n",tok.value);
			fprintf(outfile,"error: NOT END\n"); 
		}
	}else if(tok.value == IF){
		getsym();
		expression(offset);
		condition(offset,0);
		//printf("xxx%d",tok.value);
		if(tok.value == ELSE){
			statement();
			fprintf(outfile,"L%d:\n",label+1);
			label += 2;
		}else if(tok.value == SEMICOLON){
			fprintf(outfile,"L%d:\n",label+1);
			label += 2;
		}else if(tok.value == PERIOD){
				fprintf(outfile,"halt\n");
		}else{
			fprintf(outfile,"error: IN IF");
		}

	}else if(tok.value == WHILE){
		looping++;
		label += 2;
		fprintf(outfile,"L%d:\n",getlabel(0));
		getsym();
		expression(offset);
		//printf("xx%d",tok.value);
		condition(offset,1);

		looping--;
		/* if(){
			OffsetFlag = 0;
		}*/

		//statement();

	}else if(tok.value == WRITE){
		do {
			getsym();
			if(tok.attr == IDENTIFIER){
				//書き出し処理
				fprintf(outfile,"writed	r%d\n",getxaddr());
				fprintf(outfile,"loadi r%d,'\\n'\n",count+offset);
				fprintf(outfile,"writec r%d\n",count+offset);
				getsym();
			}else{
				fprintf(outfile,"error: NOT IDENTIFIER\n");
			}
		}while(tok.value == COMMA);
	}else{
		printf("error:NOT EXIST ORDER\n");
		exit(1);
	}
}

//数式(r[count+offset]に出力する)
void expression(int offset){

	if(tok.attr == NUMBER){
		fprintf(outfile,"loadi	r%d,%d\n",count+offset,tok.value);
	}else if(tok.attr == IDENTIFIER){
		fprintf(outfile,"loadr	r%d,r%d\n",count+offset,getxaddr());
	}else{
		printf("error IN EXPRESSION");
	}

	getsym();
	//分岐
	//各演算で分岐
	switch(tok.value){
		case SEMICOLON:
				//getsym();
				break;
		case PLUS:
				getsym();
				if(tok.attr == NUMBER){
					fprintf(outfile,"addi	r%d,%d\n",count+offset,tok.value);
				}else if(tok.attr == IDENTIFIER){
					fprintf(outfile,"addr	r%d,r%d\n",count+offset,getxaddr());
				}
				getsym();
				break;
		case MINUS:
				getsym();
				if(tok.attr == NUMBER){
					fprintf(outfile,"subi	r%d,%d\n",count+offset,tok.value);
				}else if(tok.attr == IDENTIFIER){
					fprintf(outfile,"subr	r%d,r%d\n",count+offset,getxaddr());
				}
				getsym();
				break;
		case TIMES:
				getsym();
				if(tok.attr == NUMBER){
					fprintf(outfile,"muli	r%d,%d\n",count+offset,tok.value);
				}else if(tok.attr == IDENTIFIER){
					fprintf(outfile,"mulr	r%d,r%d\n",count+offset,getxaddr());
				}
				getsym();
				break;
		case DIV:
				getsym();
				if(tok.attr == NUMBER){
				fprintf(outfile,"divi	r%d,%d\n",count+offset,tok.value);
				}else if(tok.attr == IDENTIFIER){
					fprintf(outfile,"divr	r%d,r%d\n",count+offset,getxaddr());
				}
				getsym();
				break;
		default: 
				//fprintf(outfile,"error\n"); 
				break;
	}
}

//変数(アドレス)の取得
int getxaddr(){
	int xaddr = -1;  //見つからなかったら-1が返される
	int i;
	for(i = 0; i < count; i++){
		if(strcmp(s_table[i].v,tok.charvalue) == 0){
				xaddr = i;
		}	
	}
	return xaddr;
}

void compare(){
	getsym();
	expression(offset+1);
	fprintf(outfile,"cmpr	r%d,r%d\n",count+offset,count+offset+1);
}

//order ifなら0,whileなら1 
void condition(int offset,int order){
	printf("xxx%d,%d\n",tok.value,tok.attr);
	switch (tok.value){
			case EQL:
				compare();
				fprintf(outfile,"jnz	L%d\n",label+order);
				if(tok.value == THEN){
					statement();
				}else if(tok.value == DO){
					statement();
				}else{
					fprintf(outfile,"%d,error: NOT THEN or DO\n",tok.value);
				}
				if(order){
					//while
					fprintf(outfile,"jmp	L%d\n",label);
					fprintf(outfile,"L%d:\n",label+1);
				}else{
					fprintf(outfile,"jmp	L%d\n",label+1);
					fprintf(outfile,"L%d:\n",label);
				}
				break;
			case NOTEQL:
				compare();
				fprintf(outfile,"jz	L%d\n",label+order);
				if(tok.value == THEN){
					statement();
				}else if(tok.value == DO){
					statement();
				}else{
					fprintf(outfile,"%d,error: NOT THEN or DO\n",tok.value);
				}
				if(order){
					//while
					fprintf(outfile,"jmp	L%d\n",label);
					fprintf(outfile,"L%d:\n",label+1);
				}else{
					//if
					fprintf(outfile,"jmp	L%d\n",label+1);
					fprintf(outfile,"L%d:\n",label);
				}
				break;

			case LESSTHAN:
				compare();
				fprintf(outfile,"jge	L%d\n",getlabel(0)+order);
				if(tok.value == THEN){
					statement();
				}else if(tok.value == DO){
					statement();
				}else{
					fprintf(outfile,"%d,error: NOT THEN or DO\n",tok.value);
				}
				if(order){
					//while
					fprintf(outfile,"jmp	L%d\n",getlabel(0));
					fprintf(outfile,"L%d:\n",getlabel(1));
				}else{
					fprintf(outfile,"jmp	L%d\n",getlabel(1));
					fprintf(outfile,"L%d:\n",getlabel(0));
				}
				break;
			/* 
			case LESSTHAN:
				compare();
				fprintf(outfile,"jge	L%d\n",label+order);
				if(tok.value == THEN){
					statement();
				}else if(tok.value == DO){
					statement();
				}else{
					fprintf(outfile,"%d,error: NOT THEN or DO\n",tok.value);
				}
				if(order){
					//while
					fprintf(outfile,"jmp	L%d\n",label);
					fprintf(outfile,"L%d:\n",label+1);
				}else{
					fprintf(outfile,"jmp	L%d\n",label+1);
					fprintf(outfile,"L%d:\n",label);
				}
				break;
				*/
			case GRTRTHAN:
				compare();
				fprintf(outfile,"jle	L%d\n",label+order);
				if(tok.value == THEN){
					statement();
				}else if(tok.value == DO){
					statement();
				}else{
					fprintf(outfile,"%d,error: NOT THEN or DO\n",tok.value);
				}
				if(order){
					//while
					fprintf(outfile,"jmp	L%d\n",label);
					fprintf(outfile,"L%d:\n",label+1);
				}else{
					fprintf(outfile,"jmp	L%d\n",label+1);
					fprintf(outfile,"L%d:\n",label);
				}
				break;

			case LESSEQL:
				compare();
				fprintf(outfile,"jgt	L%d\n",getlabel(0)+order);
				if(tok.value == THEN){
					statement();
				}else if(tok.value == DO){
					statement();
				}else{
					fprintf(outfile,"%d,error: NOT THEN or DO\n",tok.value);
				}
				if(order){
					//while
					fprintf(outfile,"jmp	L%d\n",getlabel(0));
					fprintf(outfile,"L%d:\n",getlabel(1));
				}else{
					fprintf(outfile,"jmp	L%d\n",getlabel(1));
					fprintf(outfile,"L%d:\n",getlabel(0));
				}
				break;
			/* 
			case LESSEQL:
				compare();
				fprintf(outfile,"jgt	L%d\n",label+order);
				if(tok.value == THEN){
					statement();
				}else if(tok.value == DO){
					statement();
				}else{
					fprintf(outfile,"%d,error: NOT THEN or DO\n",tok.value);
				}
				if(order){
					//while
					fprintf(outfile,"jmp	L%d\n",label);
					fprintf(outfile,"L%d:\n",label+1);
				}else{
					fprintf(outfile,"jmp	L%d\n",label+1);
					fprintf(outfile,"L%d:\n",label);
				}
				break;
			*/
			case GRTREQL:
				compare();
				fprintf(outfile,"jlt	L%d\n",label+order);
				if(tok.value == THEN){
					statement();
				}else if(tok.value == DO){
					statement();
				}else{
					fprintf(outfile,"%d,error: NOT THEN or DO\n",tok.value);
				}
				if(order){
					//while
					fprintf(outfile,"jmp	L%d\n",label);
					fprintf(outfile,"L%d:\n",label+1);
				}else{
					fprintf(outfile,"jmp	L%d\n",label+1);
					fprintf(outfile,"L%d:\n",label);
				}
				break;
			default:
				fprintf(outfile,"error: IN THEN\n");
				break;
	}
}

//使用するラベルの管理
int getlabel(int plus){
	printf("%d,%d,%d,%d\n",label, label/2, looping,label - ( label / 2 - looping ) * 2 - 2 + plus);
	return label - ( label / 2 - looping ) * 2 - 2 + plus; 
}