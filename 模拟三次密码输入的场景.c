#include<stdio.h>
int main()
{
	char passwd1[] = "123456";
	char passwd2[10] = {0};
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		printf("请输入密码:>");
		scanf("%s", passwd2);
		if (strcmp(passwd1, passwd2) == 0)
		{
			printf("登陆成功\n");
			break;
		}
		else
		{
			printf("密码错误\n");
		}
	}
	if (i == 3)
		printf("退出系统\n");
	return 0;
}