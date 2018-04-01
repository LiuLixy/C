#include<stdio.h>
int main()
{
	int m = 0;
	int n = 0;
	int q = 0;
	int count = 0;
	int i = 0;
	printf("Please Enter:>");
	scanf("%d %d", &m, &n);
	q = m^n;
	for (i = 0; i < 32; i++)
	{
		if ((q >> i) & 1 == 1)
		{
			count++;
		}
	}
	printf("count = %d", count);
	return 0;
}