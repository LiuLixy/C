#include<stdio.h>
int  count_one_bits(unsigned int value)
{
	int count = 0;
	while (value)
	{
		count++;
		value = value&(value - 1);
	}
	return count;
}

int main()
{
	int num = 0;
	int ret = 0;
	printf("请输入一个整数:>");
	scanf("%d", &num);
	ret = count_one_bits(num);
	printf("count = %d", ret);
	return 0;
}