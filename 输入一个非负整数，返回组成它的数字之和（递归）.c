int DigitSum(int n)
{
	if (n < 10)
		return n;
	else
		return n % 10 + DigitSum(n / 10);  
}

int  main()
{
	int n = 0;
	printf("Please Enter: ");
	scanf("%d", &n);
	int ret = DigitSum(n);
	printf("%d\n", ret);
	system("pause");
	return 0;
}