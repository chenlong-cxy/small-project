#define _CRT_SECURE_NO_WARNINGS 1

#define INIT_CAP 3
//ͨѶ¼��ʼ����

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
	SORT,//6
	SAVE//7
};//���Ӵ���ɶ���

struct PeoInfo
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	int tele[MAX_TELE];
	char address[MAX_ADDRESS];
};//ÿһ����ϵ�˵���Ϣ����

//ͨѶ¼����
struct Contact
{
	struct PeoInfo* data;//ָ��һ�鶯̬���ٵĿռ�
	int size;//��¼��ǰ������ϵ�˵ĸ���
	int capacity;//��ǰͨѶ¼���������
};

//��ʼ��ͨѶ¼
void InitContact(struct Contact* ps);

//����һ����ϵ�˵���Ϣ
void AddContact(struct Contact* ps);

//ɾ��һ����ϵ�˵���Ϣ
void DeleteContact(struct Contact* ps);

//����ָ����ϵ�˲���ӡ����Ϣ
void SreachContact(const struct Contact* ps);

//�޸�ָ����ϵ�˵���Ϣ
void ModifyContact(struct Contact* ps);

//��ӡͨѶ¼�е�ȫ����Ϣ
void ShowContact(const struct Contact* ps);

//ͨ����������ͨѶ¼����ϵ�˵��Ⱥ�˳��
void SortContact(struct Contact* ps);

//����ͨѶ¼����
void DestroyContact(struct Contact* ps);

//����ͨѶ¼����Ϣ���ļ���
void SaveContact(struct Contact* ps);