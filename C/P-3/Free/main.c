#include <stdio.h>
#include "methods.h"
#include "sorts.h"

#include <time.h>
#include <unistd.h>

#define N 10 //配列の要素数

//実行する処理を管理するため、現在の状態を記憶しておくための構造体変数
typedef struct status {
  int phase; //実行するプログラムの位置を管理する値
  int function; //フェーズ内部でどの機能を実行するかを管理する値
  int sort; // どのソートに対して実行するかを管理する値
  int info_flag; //sort_infoに数値を格納しているかしていないかを管理する値
}Status;



int main(void){
  Status s = {0,0,0,0};  //statusを全て0で初期化
  int array[N];

  //[~へ戻る]を実現するループ
  do{
    //phase == 0
    if(s.phase == 0){
      printf("\n(数値生成フェーズです)\n");
      random_def(array,N);
      s.phase = receive_phase(s.phase);
    }

    //phase == 1
    while(s.phase == 1){
      printf("\n(確認フェーズに移動しました)\n");
      s.function = receive_function(s.phase);
      switch(s.function){
        case 0:
            sort_info();  break;
        case 1:
            explain();  break;
        case 2:
            array_status(array,N); break;
        case -1:
            s.phase = 2;  break;
        }
        if(s.function >= 0){
          s.phase = receive_phase(s.phase);
        }
    }

    //phase == 2
    while(s.phase == 2){
      printf("\n(過程フェーズに移動しました)\n");
      s.function = receive_function(s.phase);
      switch(s.function){
        case 0:
            bubble(array,N); break;
        case 1:
            selection(array,N); break;
        case 2:
            heap(array,N); break;
        case 3:
            merge(array,N); break;
        case -1:
            s.phase = 1;  break;
        case -2:
            s.phase = -1;
            printf("プログラムを終了します。"); break;
      }
      if(s.function >= 0 && s.function <= 5){
          s.phase = receive_phase(s.phase);
      }
    }
  }while(s.phase != -1); //phaseが-1なら終了する
}
