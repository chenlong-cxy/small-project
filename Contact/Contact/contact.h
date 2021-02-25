#define _CRT_SECURE_NO_WARNINGS 1

#define MAX 1000

#define MAX_NAME 20
#define MAX_SEX 5
#define MAX_TELE 12
#define MAX_ADDRESS 20

#include <stdio.h>
#include<string.h>

enum Fun
{
	exit,
	Add,
	Delete,
	Sreach,
	Modify,
	Show,
	Sort
};
struct PeoInfo
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	int tele[MAX_TELE];
	char address[MAX_ADDRESS];
};

//通讯录类型
struct Contact
{
	struct PeoInfo data[MAX];//存放1000个信息
	int size;//记录当前已有元素个数
};

//初始化通讯录
void InitContact(struct Contact* ps);

//添加联系人
void AddContact(struct Contact* ps);

//显示联系人
void ShowContact(const struct Contact* ps);