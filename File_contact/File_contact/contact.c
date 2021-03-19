#include "contact.h"

//���ͨѶ¼״̬���������������ݣ�������ʱ���ٿռ�ʧ�ܣ��򷵻�1
static int CheckCapacity(struct Contact* ps)
{
	if (ps->size == ps->capacity)//ͨѶ¼�����Ѵ�����
	{
		//����
		struct PeoInfo* ptr = (struct PeoInfo*)realloc(ps->data, (ps->capacity + 2)*sizeof(struct PeoInfo));
		if (ptr != NULL)
		{
			ps->data = ptr;
			ps->capacity += 2;
			return 0;//���ݳɹ�
		}
		else
		{
			return 1;//����ʧ��
		}
	}
	return 0;
}

//�����ļ�
void LodeContact(struct Contact* ps)
{
	//���ļ�
	FILE* pf = fopen("contact.dat", "rb");
	if (pf == NULL)
	{
		printf("�����ļ�ʧ��\n");
		return ;
	}
	//�����ļ����ݵ�ͨѶ¼
	struct PeoInfo tmp = { 0 };
	while ( fread(&tmp, sizeof(struct PeoInfo), 1, pf))
	{
		//����Ƿ���Ҫ����
		int flag = CheckCapacity(ps);
		//���ͨѶ¼״̬���������������ݣ�������ʱ���ٿռ�ʧ�ܣ��򷵻�1
		if (flag == 1)
		{
			printf("�����ļ�ʧ��\n");
			return;
		}
		//�洢Ԫ��
		ps->data[ps->size] = tmp;
		ps->size++;
	}
	//�ر��ļ�
	fclose(pf);
	pf = NULL;
}

//��ʼ��ͨѶ¼
void InitContact(struct Contact* ps)
{
	ps->data = (struct PeoInfo*)malloc(INIT_CAP * sizeof(struct PeoInfo));
	if (ps->data == NULL)//����ʧ��
		return;
	ps->size = 0;//һ��ʼͨѶ¼Ϊ��
	ps->capacity = INIT_CAP;//һ��ʼͨѶ¼��ֻ�ܴ��3����ϵ�˵���Ϣ��������������
	//�����ļ�
	LodeContact(ps);
}

//���һ����ϵ�˵���Ϣ
void AddContact(struct Contact* ps)
{
	int flag = CheckCapacity(ps);
	if (flag == 1)
	{
		printf("�ڴ�ռ䲻�㣬����ʧ��\n");
		return;
	}
	//���ͨѶ¼״̬���������������ݣ�������ʱ���ٿռ�ʧ�ܣ��򷵻�1

	//��������
	printf("����������:>");
	scanf("%s", ps->data[ps->size].name);
	printf("����������:>");
	scanf("%d", &(ps->data[ps->size].age));
	printf("�������Ա�:>");
	scanf("%s", ps->data[ps->size].sex);
	printf("������绰:>");
	scanf("%s", ps->data[ps->size].tele);
	printf("�������ַ:>");
	scanf("%s", ps->data[ps->size].address);
	ps->size++;//ͨѶ¼����ϵ�˸���+1
	printf("��ӳɹ�\n");
}

//ͨ�����ֲ�����ϵ�ˣ��ҵ��˷����±꣬û�ҵ�����-1
static int FindByName(char name[MAX_NAME],const struct Contact* ps)
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (strcmp(ps->data[i].name, name) == 0)
			return i;//�ҵ��˷����±�
	}
	return -1;//�Ҳ��������
}

//ɾ��һ����ϵ�˵���Ϣ
void DeleteContact(struct Contact* ps)
{
	char name[MAX_NAME];
	printf("������Ҫɾ����ϵ�˵�����:>");
	scanf("%s", name);
	//����
	int pos = FindByName(name, ps);//�ҵ��˷����±꣬û�ҵ�����-1
	//ɾ��
	if (pos == -1)
	{
		printf("���޴���\n");
	}
	else
	{
		int j = 0;
		for (j = pos; j < ps->size - 1; j++)
		{
			ps->data[j] = ps->data[j + 1];
		}//��Ҫɾ������ϵ��λ�ÿ�ʼ����һλ��ϵ����Ϣ����ǰһ����ϵ����Ϣ
		printf("ɾ���ɹ�\n");
		ps->size--;//ͨѶ¼����ϵ�˸���-1
	}
}

//����ָ����ϵ�˲���ӡ����Ϣ
void SreachContact(const struct Contact* ps)
{
	char name[MAX_NAME];
	printf("������Ҫ������ϵ�˵�����:>");
	scanf("%s", name);
	int pos = FindByName(name, ps);//�ҵ��˷����±꣬û�ҵ�����-1
	if (pos == -1)
	{
		printf("���޴���\n");
	}
	else
	{
		printf("%-15s\t%-4s\t%-5s\t%-12s\t%-20s\n", "����", "����", "�Ա�", "�绰", "סַ");
		printf("%-15s\t%-4d\t%-5s\t%-12s\t%-20s\n",
			ps->data[pos].name,
			ps->data[pos].age,
			ps->data[pos].sex,
			ps->data[pos].tele,
			ps->data[pos].address);
	}//��ӡ����ϵ�˵���Ϣ����
}

//�޸�ָ����ϵ�˵���Ϣ
void ModifyContact(struct Contact* ps)
{
	char name[MAX_NAME];
	printf("������Ҫ�޸ĵ���ϵ�˵�����:>");
	scanf("%s", name);
	int pos = FindByName(name, ps);//�ҵ��˷����±꣬û�ҵ�����-1
	if (pos == -1)
	{
		printf("���޴���\n");
	}
	else
	{
		printf("����������:>");
		scanf("%s", ps->data[pos].name);
		printf("����������:>");
		scanf("%d", &(ps->data[pos].age));
		printf("�������Ա�:>");
		scanf("%s", ps->data[pos].sex);
		printf("������绰:>");
		scanf("%s", ps->data[pos].tele);
		printf("�������ַ:>");
		scanf("%s", ps->data[pos].address);
		printf("�޸ĳɹ�\n");
	}//�޸���ϵ����Ϣ����������ϵ����Ϣ����¼��
}

//��ӡͨѶ¼�е�ȫ����Ϣ
void ShowContact(const struct Contact* ps)
{
	if (ps->size == 0)
	{
		printf("ͨѶ¼Ϊ��\n");
	}//ͨѶ¼����ϵ�˸���Ϊ0
	else
	{
		printf("%-15s\t%-4s\t%-5s\t%-12s\t%-20s\n", "����", "����", "�Ա�", "�绰", "סַ");
		//��ӡ��Ϣ��
		int i = 0;
		for (i = 0; i < ps->size; i++)
		{
			printf("%-15s\t%-4d\t%-5s\t%-12s\t%-20s\n",
				ps->data[i].name,
				ps->data[i].age,
				ps->data[i].sex,
				ps->data[i].tele,
				ps->data[i].address);
		}//��ӡͨѶ¼ȫ����Ϣ����
	}
}

//�Զ���ıȽϺ���
int CmpByName(const void* e1, const void* e2)
{
	return strcmp((const char*)e1, (const char*)e2);
}

//ͨ����������ͨѶ¼����ϵ�˵��Ⱥ�˳��
void SortContact(struct Contact* ps)
{
	qsort(ps->data, ps->size, sizeof(struct PeoInfo), CmpByName);//����
}

//����ͨѶ¼����
void DestroyContact(struct Contact* ps)
{
	//�ͷŶ�̬���ٿռ�
	free(ps->data);
	ps->data = NULL;
}

//����ͨѶ¼����Ϣ���ļ���
void SaveContact(struct Contact* ps)
{
	//���ļ�
	FILE* pf = fopen("contact.dat", "wb");
	if (pf == NULL)
	{
		printf("����ʧ��\n");
		return;
	}
	//���ļ���������
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		fwrite(ps->data + i, sizeof(struct PeoInfo), 1, pf);
	}
	//�ر��ļ�
	fclose(pf);
	pf = NULL;
	printf("����ɹ�\n");
}