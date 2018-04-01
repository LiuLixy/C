#include<stdio.h>
#include<stdlib.h>
#include<time.h>


void menu()
{
	printf("*****************************\n");
	printf("**    1.play     0.exit    **\n");
	printf("*****************************\n");
}

void game()
{
	int num = 0;
	int input = 0;
	srand((unsigned int)time(NULL));
	num = rand()%100+1;
	while (1)
	{
		printf("请输入你猜的数字:>");
		scanf("%d", &input);
		if (num == input)
		{
			printf("恭喜你，猜对了\n");
			break;
		}
		else if (num > input)
		{
			printf("猜小了\n");
		}
		else
		{
			printf("猜大了\n");
		}
	}
}

int main()
{
	int input = 0;
	do
	{
		menu();
		printf("请选择：>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			break;
		default:
			printf("选择错误\n");
			break;
		}
	} while (input);
	return 0;
}