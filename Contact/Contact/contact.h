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

//ͨѶ¼����
struct Contact
{
	struct PeoInfo data[MAX];//���1000����Ϣ
	int size;//��¼��ǰ����Ԫ�ظ���
};

//��ʼ��ͨѶ¼
void InitContact(struct Contact* ps);

//�����ϵ��
void AddContact(struct Contact* ps);

//��ʾ��ϵ��
void ShowContact(const struct Contact* ps);