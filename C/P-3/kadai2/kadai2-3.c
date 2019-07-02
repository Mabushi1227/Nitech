#include <stdio.h>

int main(void)
{
	int i;
	int va[5];
	int vb[5];

	for(i=0;i<5;i++){
		printf("va[%d]:",i);
		scanf("%d", &va[i]);
	}

  for (i = 0; i < 5; i++) {
    vb[i] = va[4-i];
  }

  puts(" va vb");
puts("-------");
for(i = 0; i < 5; i++)
  printf("%3d%3d\n", va[i], vb[i]);
return (0);
}
