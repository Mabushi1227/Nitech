#include <stdio.h>
#include <stdlib.h>
#include <getsym.h>
#include <string.h>

extern TOKEN tok;
extern FILE *infile;
extern FILE *outfile;

#define REGISTERAVAIABLE 4

typedef struct 
{
	int addr;
	char v[MAXIDLEN+1];
}s_entry;

s_entry s_table[32];
int count = 0;  //変数の数を保存
//int offset; //使用レジスタの制御
//int OffsetFlag = 0; //offsetを継続して使うときに1,0のときはoffsetを1にしておく
int label = 0; //ラベル数
//int looping = 0; //ループの数
//int using = 0; //計算式の中で使用しているレジスタ数、4を越えると格納

typedef struct {
	int ident; //記録している変数のアドレスを保存
	int used; //使われた順番を記録
	int disable; //上書き可能なら０,不可能なら1
} Register;
Register reg[REGISTERAVAIABLE];

void error(char *s);
void outblock(void);
void statement(void);
void expression(int r); //結果をレジスタ[r]に入れる
void term(int r); //計算式の解析
void factor(int r); //計算式の解析
void condition(int r1,int r2,int order,int labaling);  //結果をレジスタ[r]に入れる, order 0->if, 1->while
 
int getxaddr();
int getlabel(int plus);  //使用ラベルの管理,前半ラベル->plus=0,後半ラベルplus=1 
void compare(int r1,int r2);
void reginit();
int regsearch();
void regctrl(int number);
int regchoice();
void loadi(int r);
int over_i[];

void compiler(void){
	init_getsym();

	getsym();

	if (tok.attr == RWORD && tok.value == PROGRAM){

		getsym();

		if (tok.attr == IDENTIFIER){

			getsym();

			if (tok.attr == SYMBOL && tok.value == SEMICOLON){

				//getsym();
				reginit();
				
				
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
	//int r;
	
	getsym();

	printf("%d\n",tok.value);

	if(tok.attr == IDENTIFIER){
		int xaddr = getxaddr();  //代入先のアドレス
		getsym();
		if(tok.value == BECOMES){
			getsym();  //数式の始め

			int raddr = regchoice(); //代入先のレジスタ
			regctrl(raddr);

			expression(raddr);
			fprintf(outfile,"store	r%d,%d\n",raddr,xaddr);
			reg[raddr].ident = xaddr;
			reg[raddr].disable = 0;
			//using = 0;

			printf("%d\n",tok.value);

			//fprintf(outfile,"loadr	r%d,r%d\n",r,offset); テスト
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
		int labeling = label;
		label += 2;
		getsym();
		int rnumber1 = regchoice();
		regctrl(rnumber1);
		int rnumber2 = regchoice();
		regctrl(rnumber2);
		expression(rnumber1);
		condition(rnumber1,rnumber2,0,labeling);
		//printf("xxx%d",tok.value);
		if(tok.value == ELSE){
			fprintf(outfile,"jmp	L%d\n",labeling+1);
			fprintf(outfile,"L%d:\n",labeling);
			statement();
			fprintf(outfile,"L%d:\n",labeling+1);
		}else if(tok.value == SEMICOLON){
			fprintf(outfile,"L%d:\n",labeling);
		}else if(tok.value == PERIOD){
				fprintf(outfile,"halt\n");
		}else{
			fprintf(outfile,"error: IN IF");
		}

	}else if(tok.value == WHILE){
		int labeling = label;
		label += 2;
		fprintf(outfile,"L%d:\n",labeling);
		getsym(); //IDENTFIER
		//使用するレジスタを決める
		int rnumber1 = regchoice();
		regctrl(rnumber1);
		int rnumber2 = regchoice();
		regctrl(rnumber2);
		expression(rnumber1);
		reg[rnumber1].disable = 1;
		reg[rnumber2].disable = 1;
		//printf("xx%d",tok.value);
		condition(rnumber1,rnumber2,1,labeling);

		reg[rnumber1].disable = 0;
		reg[rnumber2].disable = 0;


		//statement();

	}else if(tok.value == WRITE){ //write命令
		do {
			getsym(); //出力する変数
			if(tok.attr == IDENTIFIER){
				//書き出し処理
				int regnum = regsearch(); //レジスタ内に変数が入っていないかを探索
				if(regnum != -1){         //レジスタ内に入っていればそのレジスタの数値を書く
					fprintf(outfile,"writed	r%d\n",regnum);
					regctrl(regnum);
				}else{ 					  //レジスタに入っていないならロードして書く
					regnum = regchoice();
					regctrl(regnum);
					fprintf(outfile,"load	r%d,%d\n",regnum,getxaddr());
					fprintf(outfile,"writed	r%d\n",regnum);
				}
				//改行を出力する処理
				regnum = regchoice();
				regctrl(regnum);
				fprintf(outfile,"loadi r%d,'\\n'\n",regnum);
				fprintf(outfile,"writec r%d\n",regnum);
				getsym(); // "," or ""
			}else{
				fprintf(outfile,"error: IN WRITE, NOT IDENTIFIER\n");
			}
		}while(tok.value == COMMA);
	}else{
		printf("error:NOT EXIST ORDER\n");
		exit(1);
	}
}

//計算式を解析する関数
//expression() -> term() -> factor()
//最終的な出力はrに対応するレジスタ
///expression()は、数式の初めのトークンが読み込まれた状態で呼び出される
void expression(int r){

	term(r);

	int s;
	if(tok.value == PLUS || tok.value == MINUS){
		int eMemory = 0; //掛け算なら1、割り算なら2を記憶
		if(tok.value == PLUS){
			eMemory = 1;
		}else if(tok.value == MINUS){
			eMemory = 2;
		}
		s = regchoice();
		regctrl(s);
		reg[s].disable = 1;
		getsym();
		expression(s);
		if(eMemory == 1){
			fprintf(outfile,"addr	r%d,r%d\n",r,s);
			reg[s].disable = 0;
		}else if(eMemory == 2){
			fprintf(outfile,"subr	r%d,r%d\n",r,s);
			reg[s].disable = 0;
		}
	}
	//using++;
}

void term(int r){

	factor(r);

	int s;
	if(tok.value == TIMES || tok.value == DIV){
		int tMemory = 0; //掛け算なら1、割り算なら2を記憶
		if(tok.value == TIMES){
			tMemory = 1;
		}else if(tok.value == DIV){
			tMemory = 2;
		}
		s = regchoice();
		regctrl(s);
		reg[s].disable = 1;
		getsym();
		term(s);
		if(tMemory == 1){
			fprintf(outfile,"mulr	r%d,r%d\n",r,s);
			reg[s].disable = 0;
		}else if(tMemory == 2){
			fprintf(outfile,"divr	r%d,r%d\n",r,s);
			reg[s].disable = 0;
		}
	}
}


void factor(int r){
	int fMemory = 0; //マイナスがあるか無いかを記憶
	/*if(tok.value == MINUS){
		fMemory = 1;
		getsym(); // ident,number,(
	}*/

	if(tok.attr == IDENTIFIER){
		fprintf(outfile,"load	r%d,%d\n",r,getxaddr());
		getsym();
	}else if(tok.attr == NUMBER){
		loadi(r);
		getsym();
	}else if(tok.value == LPAREN){
		getsym();
		expression(r);
		if(tok.value == RPAREN){
			getsym();
		}
	}else{
		printf("ERROR IN FACTOR: %d\n",tok.value);
		//getsym();
		//fprintf(outfile,"ERROR IN FACTOR; %d\n",tok.value);
	}

	if(fMemory){
		fprintf(outfile,"muli	r%d,-1\n",r);
	}

}

void loadi(int r){
	if(tok.value <= 32767 && tok.value >= -32768){
		fprintf(outfile,"loadi	r%d,%d\n",r,tok.value);	
	}else{
		label += 2;
		//fprintf(outfile,"L%d:\n",label);
		fprintf(outfile,"load	r%d,L%d\n",r,label+1);
		fprintf(outfile,"L%d: data %d\n", label+1, tok.value);
		//fprintf(outfile,"L%d: data 100000\n", label+1);
	}
	
}

//変数(アドレス)の取得
int getxaddr(){
	int xaddr = -1;  //見つからなかったら-1が返される
	int i;
	for(i = 0; i < count; i++){
		if(strcmp(s_table[i].v,tok.charvalue) == 0){
				xaddr = s_table[i].addr;
		}
	}
	return xaddr;
}

void compare(int r1,int r2){
	getsym();
	expression(r2);
	fprintf(outfile,"cmpr	r%d,r%d\n",r1,r2);
	reg[r1].disable = 0;
	reg[r2].disable = 0;
}

//order ifなら0,whileなら1 
void condition(int r1, int r2, int order,int labeling){
	printf("xxx%d,%d\n",tok.value,tok.attr);
	switch (tok.value){
			case EQL:
				compare(r1,r2);
				fprintf(outfile,"jnz	L%d\n",labeling+order);
				if(tok.value == THEN){
					statement();
				}else if(tok.value == DO){
					statement();
				}else{
					fprintf(outfile,"%d,error: NOT THEN or DO\n",tok.value);
				}
				if(order){
					//while
					fprintf(outfile,"jmp	L%d\n",labeling);
					fprintf(outfile,"L%d:\n",labeling+1);
				}
				break;
			case NOTEQL:
				compare(r1,r2);
				fprintf(outfile,"jz	L%d\n",labeling+order);
				if(tok.value == THEN){
					statement();
				}else if(tok.value == DO){
					statement();
				}else{
					fprintf(outfile,"%d,error: NOT THEN or DO\n",tok.value);
				}
				if(order){
					//while
					fprintf(outfile,"jmp	L%d\n",labeling);
					fprintf(outfile,"L%d:\n",labeling+1);
				}
				break;

			case LESSTHAN:
				compare(r1,r2);
				fprintf(outfile,"jge	L%d\n",labeling+order);
				if(tok.value == THEN){
					statement();
				}else if(tok.value == DO){
					statement();
				}else{
					fprintf(outfile,"%d,error: NOT THEN or DO\n",tok.value);
				}
				if(order){
					//while
					fprintf(outfile,"jmp	L%d\n",labeling);
					fprintf(outfile,"L%d:\n",labeling+1);
				}
				break;
			case GRTRTHAN:
				compare(r1,r2);
				fprintf(outfile,"jle	L%d\n",labeling+order);
				if(tok.value == THEN){
					statement();
				}else if(tok.value == DO){
					statement();
				}else{
					fprintf(outfile,"%d,error: NOT THEN or DO\n",tok.value);
				}
				if(order){
					//while
					fprintf(outfile,"jmp	L%d\n",labeling);
					fprintf(outfile,"L%d:\n",labeling+1);
				}
				break;

			case LESSEQL:
				compare(r1,r2);
				fprintf(outfile,"jgt	L%d\n",labeling+order);
				if(tok.value == THEN){
					statement();
				}else if(tok.value == DO){
					statement();
				}else{
					fprintf(outfile,"%d,error: NOT THEN or DO\n",tok.value);
				}
				if(order){
					//while
					fprintf(outfile,"jmp	L%d\n",labeling);
					fprintf(outfile,"L%d:\n",labeling+1);
				}
				break;
			case GRTREQL:
				compare(r1,r2);
				fprintf(outfile,"jlt	L%d\n",labeling+order);
				if(tok.value == THEN){
					statement();
				}else if(tok.value == DO){
					statement();
				}else{
					fprintf(outfile,"%d,error: NOT THEN or DO\n",tok.value);
				}
				if(order){
					//while
					fprintf(outfile,"jmp	L%d\n",labeling);
					fprintf(outfile,"L%d:\n",labeling+1);
				}
				break;
			default:
				fprintf(outfile,"error: IN THEN\n");
				break;
	}
}

//使用するラベルの管理
/*int getlabel(int plus){
	//printf("%d,%d,%d,%d\n",label, label/2, looping,label - ( label / 2 - looping ) * 2 - 2 + plus);
	return label - ( label / 2 - looping ) * 2 - 2 + plus; 
}*/

//レジスタ変数の初期化
void reginit(){
	int i;
	for (i = 0; i < REGISTERAVAIABLE; i++)
	{
		reg[i].ident = -1;
		reg[i].used = i;
	}
}

///レジスタの選択は実行する１つ上の階層で行う
//レジスタに使用する変数が格納されているかを探索
int regsearch(){
	int r = -1; //見つからなければ-1
	int i,j;
	for (i = 0; i < count; i++)
	{
		//変数の探索
		if(strcmp(s_table[i].v,tok.charvalue) == 0){

			//レジスタ内の探索
			for (j = 0; j < REGISTERAVAIABLE; j++){
				if(reg[j].ident == i){
					r = j;
					return r;
				}	
			}

		}
	}
	return r;
}
/* 
//reg[].usedが0のレジスタ番号を返す
int regchoice(){
	int choice = -1;
	int i;
	for (i = 0; i < REGISTERAVAIABLE; i++)
	{
		if(reg[i].used == 0 && !reg[i].disable){
			choice = i;
		}
	}
	
	return choice;
}*/
//reg[].usedが0のレジスタ番号を返す
int regchoice(){
	int choice = -1;
	int i;
	for (i = 0; i < REGISTERAVAIABLE; i++)
	{
		if(reg[i].used == 0){
			choice = i;
		}
	}
	
	return choice;
}

//numberのレジスタを使用した時の後処理
//expression,condition内では行わない
void regctrl(int number){
	int j;
	for (j = 0; j < REGISTERAVAIABLE; j++) //新しく使用するレジスタ以降を１つずつずらす
	{
		if(reg[j].used > reg[number].used){
			reg[j].used -= 1;
		}	
	}
	reg[number].ident = - 1; //使用するレジスタの初期化
	reg[number].used = REGISTERAVAIABLE - 1; //新しく使用するレジスタのusedを末尾に移動
}

/*前回までのexpression
//数式(結果をレジスタ[r]に出力する)
void expression(int r){
	if(tok.attr == NUMBER){
		fprintf(outfile,"loadi	r%d,%d\n",r,tok.value);
	}else if(tok.attr == IDENTIFIER){
		fprintf(outfile,"load	r%d,%d\n",r,getxaddr());
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
					fprintf(outfile,"addi	r%d,%d\n",r,tok.value);
				}else if(tok.attr == IDENTIFIER){
					fprintf(outfile,"add	r%d,%d\n",r,getxaddr());
					//fprintf(outfile,"addr	r%d,r%d\n",r,getxaddr());
				}
				getsym();
				break;
		case MINUS:
				getsym();
				if(tok.attr == NUMBER){
					fprintf(outfile,"subi	r%d,%d\n",r,tok.value);
				}else if(tok.attr == IDENTIFIER){
					fprintf(outfile,"sub	r%d,%d\n",r,getxaddr());
					//fprintf(outfile,"subr	r%d,r%d\n",r,getxaddr());
				}
				getsym();
				break;
		case TIMES:
				getsym();
				if(tok.attr == NUMBER){
				fprintf(outfile,"muli	r%d,%d\n",r,tok.value);
				}else if(tok.attr == IDENTIFIER){
					fprintf(outfile,"mul	r%d,%d\n",r,getxaddr());
					//fprintf(outfile,"mulr	r%d,r%d\n",r,getxaddr());
				}
				getsym();
				break;
		case DIV:
				getsym();
				if(tok.attr == NUMBER){
					fprintf(outfile,"divi	r%d,%d\n",r,tok.value);
				}else if(tok.attr == IDENTIFIER){
					fprintf(outfile,"div	r%d,%d\n",r,getxaddr());
					//fprintf(outfile,"divr	r%d,r%d\n",offset,getxaddr());
				}
				getsym();
				break;
		default: 
				//fprintf(outfile,"error\n"); 
				break;
	}
}*/