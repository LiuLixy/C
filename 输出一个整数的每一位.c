#include<stdio.h>
//递归
void print(int n)
{
	if (n < 0)
		n = -n;
	if (n >= 10)
		print(n/10);
	printf("%d ", n%10);
}

int main()
{
	int num = 0;
	printf("Please Enter:>");
	scanf("%d", &num);
	print(num);
	return 0;
}
