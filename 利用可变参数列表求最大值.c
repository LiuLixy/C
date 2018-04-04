#include<stdio.h>
#include<windows.h>
#include<assert.h>

int find_max(int num, ...)
{
	assert(num > 0);

	va_list arg;
	va_start(arg, num);

	int i = 1;
	int max = va_arg(arg, int);
	for (; i < num; i++)
	{
		int tmp = va_arg(arg, int);
		if (max < tmp)
		{
			max = tmp;
		}
	}
	va_end(arg);
	return max;
}

int main()
{
	printf("max: %d\n", find_max(5, -1, -2, -3, -4, -5));
	system("pause");
	return 0;
}