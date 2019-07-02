#include<stdio.h>

int main(void)
{
    int ch;
    FILE *sfp, *dfp;
    char sname[64],dname[64];
    int count=0;/*大文字のカウント*/
    int line=1;/*行数番号*/

    printf("コピー元ファイル名を入力してください：");
    scanf("%s",sname);
    printf("コピー先ファイル名を入力してください：");
    scanf("%s",dname);

    if((sfp = fopen(sname,"r")) == NULL)
        printf("コピー元ファイルをオープンできません。\n");
    else{
        /* ファイルから読み込み */
        if((dfp = fopen(dname,"w")) == NULL)
            printf("コピー先ファイルをオープンできません。\n");
        else{
            while((ch = fgetc(sfp)) != EOF){
            /*各行の大文字の数をカウントし小文字に変換*/
//(* ここに解答を書き加える *)
                if(ch >= 65 && ch <= 90){
                count++;
                ch = ch + 32;
                }
                /*各行の終わりにきたら行番号と大文字の数を表示*/
                if(ch == '\n'){
                    printf("line%d = %d\n", line, count);
                    line++;
                    count=0;
                }
                /*コピー先ファイルにコピー*/
//(* ここに解答を書き加える *)
                fputc(ch,dfp);
            }
            fclose(dfp);
        }
        fclose(sfp);

        /* コピー後, コピー先のファイルの内容を表示 */
        /* コピー先ファイルをオープン */
        if((dfp = fopen(dname,"r")) == NULL){
            printf("コピー先ファイルをオープンできません。\n");
        }
        else{
            printf("コピー実行後\n");
            while((ch = fgetc(dfp)) != EOF){
                printf("%c",ch);
            }
            fclose(dfp);
        }
    }

    return (0);
}
