#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
 
#define LENGTH 20

/*char* getpasswd();
int main()
{
	char* p = getpasswd();
	printf("%s\n",p);
	return 0;
}*/


 
char* getpasswd()
{
	static char password[LENGTH];
	int len = 0;
	int ch;
	struct termios oldt,newt;
	//printf("input your password\n");
	while(1)
	{
			tcgetattr(STDIN_FILENO,&oldt);
			newt = oldt;
			newt.c_lflag &=~(ECHO | ICANON); // 标识相应标识位不回显
			tcsetattr(STDIN_FILENO,TCSANOW,&newt); // 设置标识位
			ch = getchar();
			if(ch == '\n'){
				password[len] = '\0';
				tcsetattr(STDIN_FILENO,TCSANOW,&oldt); // 将标识位恢复
				break;
			}
			password[len] = ch;
			len++;
			tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
			printf("*");
	
	}
	printf("\n");
	return password;
}

