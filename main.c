#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>
#include <stdlib.h>

/*简易的超市管理系统
 *主要功能：商品的增,删,改,查,创建用户等功能
 *根据不同的用户有不同的权限
 *
 *作者:yy
 *时间:2018-8-21
 */

char* getpasswd();



MYSQL mysql;

int denglu(char* usr,char* passwd);
void insert();
void delete();
void update();
void select1();
void create_usr();

int main()
{
	mysql_init(&mysql);
	if(!mysql_real_connect(&mysql,"localhost","root","","yy",0,NULL,0))
		fprintf(stderr,"link error:%s\n",mysql_error(&mysql));
	mysql_query(&mysql,"set names utf8");

	char usr[10];
	//char passwd[10];
	printf("------->用户名:");
	scanf("%s",usr);
	printf("------->密码:");
	while(getchar()!='\n');
//	scanf("%s",passwd);
	char* passwd=getpasswd();
	//printf("%s\n",passwd);
	int s = denglu(usr,passwd);
	while(1)
        {
		if(-1==s)
		{
			printf("**********************************\n");
			printf("欢迎使用超市管理系统!\n今天也要元气满满哦！\n作者:yy\n2018-8-21\n");
			printf("**********************************\n");
			printf("\t    主菜单\n");
			printf("**********************************\n");
			printf("1.添加商品\t\t2.删除商品\n3.修改库存\t\t4.查询商品\n5.创建普通用户\n");
			printf("**********************************\n");
			int i;
			scanf("%d",&i);

			//添加
			if(1==i)
			{
				insert();
			}

			else if(2==i)
			{
				delete();
			}

			else if(3==i)
			{
				update();
			}

			else if(4==i)
			{
				select1();
			}
			else if(5==i)
			{
				create_usr();
			}
		}
		else if(0==s)
		{

			printf("**********************************\n");
			printf("欢迎使用超市管理系统!\n今天也是充满希望的一天哦！\n作者:yy\n2018-8-21\n");
			printf("**********************************\n");
			printf("\t    主菜单\n");
			printf("**********************************\n");
			printf("1.添加商品\t\t2.查询商品\n");
			printf("**********************************\n");
			int i;
			scanf("%d",&i);

			//添加
			if(1==i)
			{
				insert();
			}

			else if(2==i)
			{
				select1();
			}

		}
		else return 0;
	}
	mysql_close(&mysql);	

	return 0;
}

//登录
int denglu(char* usr,char* passwd)
{

	char sql_usr[100];
	sprintf(sql_usr,"select susr,passwd from usr where susr = '%s'",usr);
	if(mysql_query(&mysql,sql_usr))
		fprintf(stderr,"error:%s\n",mysql_error(&mysql));
	else
	{
		MYSQL_RES* res;

		res = mysql_store_result(&mysql);
		MYSQL_ROW row;
	

		row = mysql_fetch_row(res);
		if(row == NULL)
		{	
			printf("用户名不存在!\n-->\n");
			 return 1;
		}
		if(strcmp(row[0],usr)==0)
		{
			if(strcmp(row[1],passwd)==0)
			{
				printf("登录成功！\n-->\n");
				int i=0;
				for(;i<5;i++)
				printf("->\n");
				if(strcmp(usr,"boss")==0)
				{
					printf("当前为root用户!\n-->\n");
					return -1;
				}
				return 0;
			}
			else 
			{
				printf("用户名或密码错误!\n-->\n");
				return 1;
			}
		}
	 
	
		mysql_free_result(res);

	}

}

//创建用户
void create_usr()
{
	char sql[100];
	char usr[20];
	int passwd;
	printf("请输入创建的用户名:\n-->");
	scanf("%s",usr);
	printf("请输入6位数的密码(只能数字)\n-->");
	scanf("%d",&passwd);
	sprintf(sql,"insert into usr values('%s',%d)",usr,passwd);
	if(mysql_query(&mysql,sql))
		fprintf(stderr,"insert error:%s\n",mysql_error(&mysql));
	 
	else
	{
		if(mysql_affected_rows(&mysql)==1) printf("创建成功！\n-->\n");
		else printf("创建失败!\n-->\n");
	}
}



//添加
void insert()
{

		char sql[100];
		int num,sno,price;
		char name[40];
		char birth[20];
		printf("输入编号 日期 名称 数量 单价\n-->");
		scanf("%d %s %s %d %d",&sno,birth,name,&num,&price);
		sprintf(sql,"insert into market values(%d,'%s','%s',%d,%d,%d)",sno,birth,name,num,price,num*price);
		if(mysql_query(&mysql,sql))
			fprintf(stderr,"insert error:%s\n",mysql_error(&mysql));

	
	char q;
	while(getchar()!='\n');
	printf("按任意键继续-->\n");
	scanf("%c",&q);
}

//删除
void delete()
{

		printf("请输入要删除的商品名称：\n-->");
		char name[40];
		scanf("%s",name);
		char sql[100];
		sprintf(sql,"delete from market where 名称 = '%s'",name);
		if(mysql_query(&mysql,sql))
			fprintf(stderr,"delete error:%s\n",mysql_error(&mysql));
		else
		{
			if(mysql_affected_rows(&mysql)==1) printf("删除成功！\n-->\n");
			else printf("删除失败!\n-->\n");
		}
	
	char q;
	while(getchar()!='\n');
	printf("按任意键继续-->\n");
	scanf("%c",&q);
}

//修改
void update()
{

		printf("请输入要修改的商品名称:\n-->");
		char name[40];
		scanf("%s",name);
		printf("请输入需要修改的选项:\n1.入库日期  2.名称\n3.数量    4.单价\n");
		int j;
		char a[20];
		scanf("%d",&j);
		switch(j)
		{
			case 1: 
				sprintf(a,"入库日期");
				break;
			case 2:
				sprintf(a,"名称");
				break;
			case 3:
				sprintf(a,"数量");
				break;
			case 4:
				sprintf(a,"单价");
				break;
		}
		printf("请输入修改后的内容:\n-->");
		char b[30];
		scanf("%s",b);
		char sql[100];
		sprintf(sql,"update market set %s = '%s' where 名称 = '%s'",a,b,name);
		if(mysql_query(&mysql,sql))
			fprintf(stderr,"update error:%s\n",mysql_error(&mysql));
		else
		{
			if(mysql_affected_rows(&mysql)==1) printf("修改成功！\n-->\n");
			else printf("修改失败！\n-->\n");

		}
		
		char sql1[100];
		sprintf(sql1,"update market set 金额 = 单价*数量 where 名称 = '%s'",name);
		mysql_query(&mysql,sql1);

	char q;
	while(getchar()!='\n');
	printf("按任意键继续-->\n");
	scanf("%c",&q);

}

//查询
void select1()
{	int i;
	printf("1.部分商品信息\t2.全部商品信息\n");
	scanf("%d",&i);
	
	if(1==i)
	{
		printf("请输入需要查询商品信息的名称：\n-->");
		char name[40];
		scanf("%s",name);
		char sql[100];
		sprintf(sql,"select * from market where 名称 = '%s'",name);
		if(mysql_query(&mysql,sql))
			fprintf(stderr,"error select:%s\n",mysql_error(&mysql));
		else
		{
			MYSQL_RES* res;

			res = mysql_store_result(&mysql);

			MYSQL_ROW row;
			
			row = mysql_fetch_row(res);

			if(row==NULL)
				printf("该商品不存在！\n-->\n");
			else
				printf("%s %s %s %s %s %s\n\n",row[0],row[1],row[2],row[3],row[4],row[5]);
			mysql_free_result(res);

		}
		char q;
		while(getchar()!='\n');
		printf("按任意键继续-->\n");
		scanf("%c",&q);
	}
	else if(2==i)
	{
		if(mysql_query(&mysql,"select * from market"))
			fprintf(stderr,"error select:%s\n",mysql_error(&mysql));
		else
		{
			MYSQL_RES* res;
			res = mysql_store_result(&mysql);
			MYSQL_ROW row;
			while(row=mysql_fetch_row(res))
				printf("%s %s %s %s %s %s\n",row[0],row[1],row[2],row[3],row[4],row[5]);
			printf("\n");
			mysql_free_result(res);
		}

	char q;
	while(getchar()!='\n');
	printf("按任意键继续-->\n");
	scanf("%c",&q);
	}
}
