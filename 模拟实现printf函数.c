#include<stdio.h>
#include<windows.h>
#include<assert.h>

int printInt(int a)
{
	if (a > 9)
	{
		printInt(a / 10);
	}
	return putchar(a % 10 + '0');
}

int my_printf(const char *format, ...)
{
	assert(format);

	va_list arg;
	va_start(arg, format);

	int count = 0;
	const char* start = format;
	while (*start)
	{
		if (*start == '%')
		{
			start++;
			switch (*start) 
			{
			case'c':
				putchar(va_arg(arg, char));
				break;
			case's':
			{
				char *s = va_arg(arg, char*);
				while (*s)
				{
					putchar(*s);
					s++;
				}
			}
				break;
			case'd':
				printInt(va_arg(arg, int));
				break;
			case'%':
				putchar(*start);
				break;
			default:
				return -1;

			}
		}
		else if (*start == '\\')
		{
			putchar('\\');
			start++;
			putchar(*start);
		}
		else
		{
			putchar(*start);
			count++;
		}
		start++;
	}
	va_end(arg);
	return count;
}


int main()
{
	char *msg = "world";
	char c = 'A';
	int a = 100;
	my_printf("hello %s, hello %c, hello %d, %% \\n\n", msg, c, a);
	system("pause");
	return 0;
}