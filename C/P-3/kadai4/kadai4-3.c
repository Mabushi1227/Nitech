#include <stdio.h>
//(* ここに解答を書き加える *)
enum animal {Dog, Cat, Monkey, Invalid};

void dog(void)
{
	puts("ワンワン！！");
}
void cat(void)
{
	puts("ニャア！！");
}
void monkey(void)
{
	puts("キッキッ！！");
}

enum animal select(void)
{
	int tmp;
	do {
		printf("0:犬　1:猫　2:猿　3:終了:::");
		scanf("%d",&tmp);
	} while (tmp < Dog || tmp > Invalid);
	return (tmp);
}

int main(void)
{
	enum animal selected;
//(* ここに解答を書き加える *)
  do {
    switch (selected  = select()) {
      case Dog  :dog(); break;
      case Cat  :cat(); break;
      case Monkey : monkey(); break;
      default: break;
    }
  } while(selected != Invalid);

	return (0);
}
