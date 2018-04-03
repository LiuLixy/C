int factorial(int n)   //  ตÝน้
{
	if (n <= 1)
		return n;
	else
		return n * factorial(n - 1);
}

int factorial(int n)
{
	int i = 1;
	int sum = 1;
	for (i = 1; i <= n; i++)
	{
		sum *= i;
	}
	return sum;
}

int main()
{
	int n = 0;
	printf("Please Enter: ");
	scanf("%d", &n);
	int ret = factorial(n);
	printf("%d\n", ret);
	system("pause");
	return 0;
}