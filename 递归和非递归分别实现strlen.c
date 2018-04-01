int my_strlen(const char *str)  
{
	if (str == NULL || *str == '\0')
		return 0;
	else
		return  1 + my_strlen(++str);
}

int my_strlen(const char str[])
{
	int count = 0;
	if(str == NULL || *str == '\0')
		return 0;
	else
	{
		while (*str)
		{
			str++;
			count++;
		}
	}
	return count;
}

int  main()
{
	char str[] = "abcdefg";
	int ret = my_strlen(str);
	printf("%d\n", ret);
	system("pause");
	return 0;
}