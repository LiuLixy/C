#include<stdio.h>
int main()
{
	int num = 0;
	printf("Please Enter:>");
	scanf("%d", &num);
	char a[32];
	int i = 0;
	for (i = 0; i < 32; i++)
	{
		a[i] = num % 2;
		num /= 2;
	}
	printf("偶数: ");
	for (i = 31; i >= 0; i -= 2)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	printf("奇数: ");
	for (i = 30; i >= 0; i -= 2)
	{
		printf("%d ", a[i]);
	}
	return 0;
}