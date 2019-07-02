#include <time.h>
#include <stdio.h>

/*--- 現在の年月日と午前か午後かを表示する ---*/
void put_time(void)
{//(* ここに解答を書き加える *)
  time_t current;
  struct tm *local;

  time(&current);
  local = localtime(&current);

  if(local->tm_hour <= 0 && local->tm_hour >= 11){
    printf("%4d年%2d月0%d日午前",local->tm_year + 1900,local->tm_mon+1,local->tm_mday);
  }else{
    printf("%4d年%2d月0%d日午後",local->tm_year + 1900,local->tm_mon+1,local->tm_mday);
  }
}

int main(void)
{
	printf("現在は");
	put_time();
	printf("です\n");

	return(0);
}
