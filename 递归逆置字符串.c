void reverse_string(char *str)
{
	if (*str == '\0')
		printf("%c", *str);
	else
	{
		reverse_string(++str);
		printf("%c", *(--str));
	}
}

int main()
{
	char str[] = "abcdef";
	reverse_string(str);
	system("pause");
	return 0;
}