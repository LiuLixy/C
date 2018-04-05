#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <assert.h>

char *my_strncpy(char *dest, const char *src, int count)
{
	assert(dest);
	assert(src);
	char *p = dest;
	while (count--)
	{
		*dest++ = *src++;
	}
	if (*(dest - 1) != '\0')
		*dest = '\0';
	return p;
}

char *my_strncat(char *dest, const char *src, int count)
{
	assert(dest);
	assert(src);
	char *p = dest;
	while (*dest) {
		*dest++;
	}
	while (count-- && *src) {
		*dest++ = *src++;
	}
	*dest = '\0';
	return p;
}

int my_strncmp(const char *str1, const char *str2, int count)
{
	assert(str1);
	assert(str2);

	while (count-- && (*str1 == *str2))
	{
		if (str1 == '\0')
			return 0;
		str1++;
		str2++;
	}
	if ((*str1 - *str2) == 0)
		return 0;
	else if ((*str1 - *str2) > 0)
		return 1;
	else
		return -1;
}

int main()
{
	char str1[] = "abcdef";
	char str2[64] = { 0 };
	printf("%s\n", my_strncpy(str2, str1, 2));
	printf("%s\n", my_strncat(str1, str1, 5));
	printf("%d\n", my_strncmp(str1, str2, 4));
	system("pause");
	return 0;
}