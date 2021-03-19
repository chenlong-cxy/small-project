#include "contact.h"

//检测通讯录状态，若已满，则扩容，若增容时开辟空间失败，则返回1
static int CheckCapacity(struct Contact* ps)
{
	if (ps->size == ps->capacity)//通讯录人数已达上限
	{
		//增容
		struct PeoInfo* ptr = (struct PeoInfo*)realloc(ps->data, (ps->capacity + 2)*sizeof(struct PeoInfo));
		if (ptr != NULL)
		{
			ps->data = ptr;
			ps->capacity += 2;
			return 0;//增容成功
		}
		else
		{
			return 1;//增容失败
		}
	}
	return 0;
}

//加载文件
void LodeContact(struct Contact* ps)
{
	//打开文件
	FILE* pf = fopen("contact.dat", "rb");
	if (pf == NULL)
	{
		printf("加载文件失败\n");
		return ;
	}
	//加载文件内容到通讯录
	struct PeoInfo tmp = { 0 };
	while ( fread(&tmp, sizeof(struct PeoInfo), 1, pf))
	{
		//检测是否需要增容
		int flag = CheckCapacity(ps);
		//检测通讯录状态，若已满，则扩容，若增容时开辟空间失败，则返回1
		if (flag == 1)
		{
			printf("加载文件失败\n");
			return;
		}
		//存储元素
		ps->data[ps->size] = tmp;
		ps->size++;
	}
	//关闭文件
	fclose(pf);
	pf = NULL;
}

//初始化通讯录
void InitContact(struct Contact* ps)
{
	ps->data = (struct PeoInfo*)malloc(INIT_CAP * sizeof(struct PeoInfo));
	if (ps->data == NULL)//开辟失败
		return;
	ps->size = 0;//一开始通讯录为空
	ps->capacity = INIT_CAP;//一开始通讯录的只能存放3个联系人的信息，若不够再扩容
	//加载文件
	LodeContact(ps);
}

//添加一个联系人的信息
void AddContact(struct Contact* ps)
{
	int flag = CheckCapacity(ps);
	if (flag == 1)
	{
		printf("内存空间不足，增容失败\n");
		return;
	}
	//检测通讯录状态，若已满，则扩容，若增容时开辟空间失败，则返回1

	//增加数据
	printf("请输入姓名:>");
	scanf("%s", ps->data[ps->size].name);
	printf("请输入年龄:>");
	scanf("%d", &(ps->data[ps->size].age));
	printf("请输入性别:>");
	scanf("%s", ps->data[ps->size].sex);
	printf("请输入电话:>");
	scanf("%s", ps->data[ps->size].tele);
	printf("请输入地址:>");
	scanf("%s", ps->data[ps->size].address);
	ps->size++;//通讯录中联系人个数+1
	printf("添加成功\n");
}

//通过名字查找联系人，找到了返回下标，没找到返回-1
static int FindByName(char name[MAX_NAME],const struct Contact* ps)
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (strcmp(ps->data[i].name, name) == 0)
			return i;//找到了返回下标
	}
	return -1;//找不到的情况
}

//删除一个联系人的信息
void DeleteContact(struct Contact* ps)
{
	char name[MAX_NAME];
	printf("请输入要删除联系人的姓名:>");
	scanf("%s", name);
	//查找
	int pos = FindByName(name, ps);//找到了返回下标，没找到返回-1
	//删除
	if (pos == -1)
	{
		printf("查无此人\n");
	}
	else
	{
		int j = 0;
		for (j = pos; j < ps->size - 1; j++)
		{
			ps->data[j] = ps->data[j + 1];
		}//从要删除的联系人位置开始，后一位联系人信息覆盖前一个联系人信息
		printf("删除成功\n");
		ps->size--;//通讯录中联系人个数-1
	}
}

//查找指定联系人并打印其信息
void SreachContact(const struct Contact* ps)
{
	char name[MAX_NAME];
	printf("请输入要查找联系人的姓名:>");
	scanf("%s", name);
	int pos = FindByName(name, ps);//找到了返回下标，没找到返回-1
	if (pos == -1)
	{
		printf("查无此人\n");
	}
	else
	{
		printf("%-15s\t%-4s\t%-5s\t%-12s\t%-20s\n", "姓名", "年龄", "性别", "电话", "住址");
		printf("%-15s\t%-4d\t%-5s\t%-12s\t%-20s\n",
			ps->data[pos].name,
			ps->data[pos].age,
			ps->data[pos].sex,
			ps->data[pos].tele,
			ps->data[pos].address);
	}//打印该联系人的信息内容
}

//修改指定联系人的信息
void ModifyContact(struct Contact* ps)
{
	char name[MAX_NAME];
	printf("请输入要修改的联系人的姓名:>");
	scanf("%s", name);
	int pos = FindByName(name, ps);//找到了返回下标，没找到返回-1
	if (pos == -1)
	{
		printf("查无此人\n");
	}
	else
	{
		printf("请输入姓名:>");
		scanf("%s", ps->data[pos].name);
		printf("请输入年龄:>");
		scanf("%d", &(ps->data[pos].age));
		printf("请输入性别:>");
		scanf("%s", ps->data[pos].sex);
		printf("请输入电话:>");
		scanf("%s", ps->data[pos].tele);
		printf("请输入地址:>");
		scanf("%s", ps->data[pos].address);
		printf("修改成功\n");
	}//修改联系人信息，即将该联系人信息重新录入
}

//打印通讯录中的全部信息
void ShowContact(const struct Contact* ps)
{
	if (ps->size == 0)
	{
		printf("通讯录为空\n");
	}//通讯录中联系人个数为0
	else
	{
		printf("%-15s\t%-4s\t%-5s\t%-12s\t%-20s\n", "姓名", "年龄", "性别", "电话", "住址");
		//打印信息栏
		int i = 0;
		for (i = 0; i < ps->size; i++)
		{
			printf("%-15s\t%-4d\t%-5s\t%-12s\t%-20s\n",
				ps->data[i].name,
				ps->data[i].age,
				ps->data[i].sex,
				ps->data[i].tele,
				ps->data[i].address);
		}//打印通讯录全部信息内容
	}
}

//自定义的比较函数
int CmpByName(const void* e1, const void* e2)
{
	return strcmp((const char*)e1, (const char*)e2);
}

//通过名字排序通讯录中联系人的先后顺序
void SortContact(struct Contact* ps)
{
	qsort(ps->data, ps->size, sizeof(struct PeoInfo), CmpByName);//排序
}

//销毁通讯录数据
void DestroyContact(struct Contact* ps)
{
	//释放动态开辟空间
	free(ps->data);
	ps->data = NULL;
}

//保存通讯录内信息到文件中
void SaveContact(struct Contact* ps)
{
	//打开文件
	FILE* pf = fopen("contact.dat", "wb");
	if (pf == NULL)
	{
		printf("保存失败\n");
		return;
	}
	//向文件传输数据
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		fwrite(ps->data + i, sizeof(struct PeoInfo), 1, pf);
	}
	//关闭文件
	fclose(pf);
	pf = NULL;
	printf("保存成功\n");
}