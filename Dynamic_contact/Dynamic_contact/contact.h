#define _CRT_SECURE_NO_WARNINGS 1

#define INIT_CAP 3
//通讯录初始容量

#define MAX_NAME 15
#define MAX_SEX 5
#define MAX_TELE 12
#define MAX_ADDRESS 20

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum Option
{
	EXIT,//0
	ADD,//1
	DELETE,//2
	SREACH,//3
	MODIFY,//4
	SHOW,//5
	SORT//6
};//增加代码可读性

struct PeoInfo
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	int tele[MAX_TELE];
	char address[MAX_ADDRESS];
};//每一个联系人的信息内容

//通讯录类型
struct Contact
{
	struct PeoInfo* data;//指向一块动态开辟的空间
	int size;//记录当前已有联系人的个数
	int capacity;//当前通讯录的最大容量
};

//初始化通讯录
void InitContact(struct Contact* ps);

//添加一个联系人的信息
void AddContact(struct Contact* ps);

//删除一个联系人的信息
void DeleteContact(struct Contact* ps);

//查找指定联系人并打印其信息
void SreachContact(const struct Contact* ps);

//修改指定联系人的信息
void ModifyContact(struct Contact* ps);

//打印通讯录中的全部信息
void ShowContact(const struct Contact* ps);

//通过名字排序通讯录中联系人的先后顺序
void SortContact(struct Contact* ps);

//销毁通讯录数据
void DestroyContact(struct Contact* ps);