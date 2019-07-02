#include <stdio.h>
#include <math.h>

#define N 10
static int change_counter;

//昇順か降順かどちらかを受け取る処理
int receive_updown(int v){
  printf("{ 昇順(1)|降順(-1) }選択してください:");
  do{
    scanf("%d",&v);
  }while (v != 1 && v != -1);

  return v;
}

//バブルソートを行うメソッド
void bubble(const int *a, int n){

  printf("バブルソートを実行します\n");

  int v = receive_updown(v);

  int i,j,change,*ar;
  ar = calloc(N,sizeof(int));

  for (i = 0; i < N; i++) {
    ar[i] = *a++;
  }

  if(v == 1){
    printf("昇順にソートします\n");
    for (i = 0; i < n-1; i++) {
      change = 0;
      for(j = n-1;j > i; j--){
        if(*(ar+j-1) > *(ar+j)){
          swap(int,*(ar+j-1),*(ar+j));
          printf("%dと%dの交換\n",*(ar+j-1),*(ar+j));
          printf(" ソート済み\n  ");
          print_a(ar,i);
          printf(" 未ソート\n  ");
          print_a(ar+i,n-i);
          change++;
        }
      }
      //1周して変更がなければソート完了しているので打ち切る
      if(change == 0) { printf("ソート完了\n"); break;}
      change_counter += change;
    }
  }else{
    printf("降順にソートします\n");
    for (i = n-1; i > 0; i--) {
      change = 0;
      for(j = 0;j < n-1; j++){
        if(*(ar+j) < *(ar+j+1)){
          swap(int,*(ar+j),*(ar+j+1));
          printf("%dと%dの交換\n",*(ar+j-1),*(ar+j));
          printf(" ソート済み\n  ");
          print_a(ar,n-i);
          printf(" 未ソート\n  ");
          print_a(ar+i,i);
          change++;
        }
      }
      //1周して変更がなければソート完了しているので打ち切る
      if(change == 0) { printf("ソート完了\n"); break;}
      change_counter += change;
    }
  }
  printf("移動回数:%d\nソート結果:",change_counter);
  print_a(ar,N);
  free(ar);
}

//セレクションソートを行うメソッド
void selection(const int *a, int n){
  printf("セレクションソートを実行します\n");

  int v = receive_updown(v);

  int i,j,*ar;
  change_counter = 0;
  ar = calloc(N,sizeof(int));

  for (i = 0; i < N; i++) {
    ar[i] = *a++;
  }

  if(v == 1){
    printf("昇順にソートします\n");
    int min;
    for (i = 0; i < n-1; i++) {
      min = i;
      for (j = i+1 ; j < n; j++) {
        if(*(ar+j) < *(ar+min)){
          min = j;
        }
      }
      printf(" ソート済み\n  ");
      print_a(ar,i);
      printf(" 未ソート\n  ");
      print_a(ar+i,n-i);
      change_counter++;
      printf("\n未ソート内の最小値:%d\n",*(ar+min));
      printf("%dと%dの交換\n",*(ar+i),*(ar+min));
      swap(int,*(ar+i),*(ar+min));
    }
  }else{
    printf("降順にソートします\n");
    int max;
    for (i = 0; i < n-1; i++) {
      max = i;
    for (j = i+1; j < n; j++) {
        if(*(ar+j) > *(ar+max)){
          max = j;
        }
      }
      printf(" ソート済み\n  ");
      print_a(ar,i);
      printf(" 未ソート\n  ");
      print_a(ar+i,n-i);
      change_counter++;
      printf("\n未ソート内の最小値:%d\n",*(ar+max));
      printf("%dと%dの交換\n",*(ar+i),*(ar+max));
      swap(int,*(ar+i),*(ar+max));
    }
  }
  printf("移動回数:%d\nソート結果:",change_counter);
  print_a(ar,n);
  free(ar);
}

//ヒープ木の法則に従って、値を整理していく。
void down_heap(int a[],int i,int n,int v){
  int left = i*2+1;
  int right = i*2+2;
  int tmp = i;

  //昇順
  if (v == 1){
    if(left <= n && a[left] > a[tmp]) {
      tmp = left;
    }else if(right <= n && a[right] > a[tmp]){
      tmp = right;
    }
  //降順
  }else if(v == -1){
    if(left <= n && a[left] < a[tmp]){
      tmp = left;
    }else if(right <= n && a[right] < a[tmp]){
      tmp = right;
    }
  }
  if(tmp != i){
    swap(int,a[i],a[tmp]);
    down_heap(a,tmp,n,v);
    down_heap(a,i,n,v);
  }
}

//arのヒープ木を作成する {O(n)}
void Heapify(int a[],int n,int v){
  int i;
  for(i = n/2-1; i >= 0; i--){
    down_heap(a,i,n,v);
  }
}

void heap(const int *a, int n){
  printf("ヒープソートを実行します\n");

  int v = receive_updown(v);

  int i,j,*ar;
  ar = calloc(n,sizeof(int));

  for (i = 0; i < n; i++) {
    ar[i] = *a++;
  }

  //ヒープ木の形式にする
  Heapify(ar,n,v);
  printf("データのヒープ木\n");
  print_a(ar,n);
  //ソート本体
  int tmp;
  for (i = n-1; i >= 0; i--) {
    swap(int,*ar,*(ar+i)); //最大値,最小値を格納
    printf("%dと%dの交換\n",*(ar+i),*ar);
    Heapify(ar,i-1,v);
    print_a(ar,n);
  }
  printf("ソート結果:");
  print_a(ar,n);
  free(ar);
}

//ソート過程に使用する配列
static int *process;

static void merge_sort(int a[],int left,int right,int v){
  if(left < right){
    int center = (left+right)/2;
    int p = 0;
    int j = 0;
    int k = left;
    int process_len = center-left;

    //前半部分のソート(再帰)
    merge_sort(a,left,center,v);
    //後半部分のソート(再帰)
    merge_sort(a,center+1,right,v);

    int i;
    //前半部分ををprocessに入れる
    for (i = left; i <= center; i++) {
        process[p++] = a[i];
        a[i] = -1;
    }
    /*aに、aの値(後半部分)とprocessの値(前半部分)の大小関係を
      比較しながら、格納していく */
    if(v == 1){
      while(i<=right && j < p){
          a[k++] = (process[j] <= a[i]) ? process[j++] : a[i++];
      }
    }else if(v == -1){
      while(i<=right && j < p){
          a[k++] = (process[j] >= a[i]) ? process[j++] : a[i++];
      }
    }

    //前半部分の数値の方が先に終わった場合、processの残りを格納
    while(j < p){
      a[k++] = process[j++];
    }

  }
}

//マージソートを行うメソッド
void merge(const int *a, int n){
  printf("マージソートを実行します\n");

  int v = receive_updown(v);

  int i,j,*ar;
  ar = calloc(n,sizeof(int));

  for (i = 0; i < n; i++) {
    ar[i] = *a++;
  }

  process = calloc(n,sizeof(int));
  merge_sort(ar,0,n-1,v);
  free(process);

  print_a(ar,n);
  free(ar);
}
