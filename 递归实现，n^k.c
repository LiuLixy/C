int my_pow(int n, int k)
{
	int sum = 0;
	if (k == 0)
		return 1;
	else if (k > 0)
	{
		sum = n * my_pow(n, k - 1);
	}
	return sum;
}

int main()
{
	int n = 0;
	int k = 0;
	printf("Please Enter(n,k): ");
	scanf("%d%d", &n, &k);
	int ret = my_pow(n, k);
	printf("%d\n", ret);
	system("pause");
	return 0;
}