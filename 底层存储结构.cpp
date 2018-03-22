#include <stdio.h>
#include <stdlib.h> 
#include <Windows.h>
#include <conio.h>
#define OK 1
#define OVERFLOW -1
int g_Linenumber = 0;
typedef struct {
	char* str;
	int length;
}Hstring;//�ѵĴ洢��ʽ
typedef struct node {
	Hstring heapptr_a;// heap's pointer �洢1-99���ַ������һ����/0
	Hstring heapptr_b;// heap's pointer �洢100-199�ַ�
	Hstring heapptr_c;// heap's pointer 200-299
	Hstring heapptr_d;// heap's pointer 300-399
	node* next;//������һ��
}Node, *Linelist;//ÿ�еĴ洢�ṹ
int CreateFirstLine(Linelist &L)         //�����ļ�����ͷ��� 
{
	L = (Node*)malloc(sizeof(Node));
	if (!L)return OVERFLOW;
	L->heapptr_a.str = NULL;
	L->heapptr_b.str = NULL;
	L->heapptr_c.str = NULL;
	L->heapptr_d.str = NULL;
	L->next = NULL;
	g_Linenumber++;
	return OK;
}
Linelist LineInsert_L(Linelist &L, int i)    //����һ�е���i���ڵ㴦
{
	Linelist ptr = L;
	Linelist s=NULL;//Ҫ������� 
	int j = 0;
	while (ptr && j<i - 2) { ptr = ptr->next; j++; }
	if (!ptr|| j > i - 2)
	{
		printf("ERROR");
		exit(-1);
	}
	s = (Node*)malloc(sizeof(Node));

	s->heapptr_a.str = NULL;
	s->heapptr_b.str = NULL;
	s->heapptr_c.str = NULL;
	s->heapptr_d.str = NULL;
	s->heapptr_a.length = 0;
	s->heapptr_b.length = 0;
	s->heapptr_c.length = 0;
	s->heapptr_d.length = 0;

	s->next = ptr->next;
	ptr->next = s;
	return s;
}
Hstring Add_A_Word(Linelist line, Hstring current_heap,int count_word,char str)
//�ڵ�ǰ�ѵ�ĩβ����һ���ַ�
{
	if (count_word <= 99)
	{
		line->heapptr_a.length = count_word;
		current_heap.str[count_word] = str;
	}
	else if (count_word == 100)//��101���ַ����ڵڶ�����
	{
		line->heapptr_a.length = count_word;
		line->heapptr_b.str = (char*)malloc(100 * sizeof(char));
		memset(line->heapptr_b.str, '\0', 100 * sizeof(char));
		current_heap.str = line->heapptr_b.str;
		current_heap.str[count_word - 100] = str;
	}
	else if (count_word > 100 && count_word <= 199)
	{
		line->heapptr_b.length = count_word-100;
		current_heap.str[count_word - 100] = str;
	}
	else if (count_word == 200)
	{
		line->heapptr_b.length = count_word-100;
		line->heapptr_c.str = (char*)malloc(100 * sizeof(char));
		memset(line->heapptr_c.str, '\0', 100 * sizeof(char));
		current_heap.str = line->heapptr_c.str;//ת��C��
		current_heap.str[count_word - 200] = str;
	}
	else if (count_word > 200 && count_word <= 299)
	{
		line->heapptr_c.length = count_word-200;
		current_heap.str[count_word - 200] = str;
	}
	else if (count_word == 300)
	{
		line->heapptr_c.length = count_word-200;
		line->heapptr_d.str = (char*)malloc(100 * sizeof(char));
		memset(line->heapptr_d.str, '\0', 100 * sizeof(char));
		current_heap.str = line->heapptr_d.str;
		current_heap.str[count_word - 300] = str;
	}
	else if (count_word > 300 && count_word <= 398)
	{
		line->heapptr_d.length = count_word-300;
		current_heap.str[count_word - 300] = str;
	}
	return current_heap;
}
int CreateFile(Linelist &L)//����һ���ļ�
{
	char str;
	int count_word = 0;//����һ�е�������������/0��
	Linelist line = L;
	Hstring current_heap;
	line->heapptr_a.str = (char*)malloc(100 * sizeof(char));//�����
	memset(line->heapptr_a.str, '\0', 100 * sizeof(char));//����ȫ����ʼ��Ϊ/0
	current_heap = line->heapptr_a;
	str = _getch();
	putchar(str);
	while (str != '#')//�״ζ�ȡ  ����ֹ��Ϊ#
	{
		if (str == 13)
		{
			current_heap=Add_A_Word(line, current_heap, count_word, str);
			printf("\n");
			count_word = 0;
			line = LineInsert_L(L, g_Linenumber + 1);//�½�һ������
			line->heapptr_a.str = (char*)malloc(100 * sizeof(char));
			memset(line->heapptr_a.str, '\0', 100*sizeof(char));
			current_heap.str = line->heapptr_a.str;
			++g_Linenumber;
		}
		else
		{
			current_heap = Add_A_Word(line, current_heap, count_word, str);
			count_word++;
		}

		str=_getch();
		putchar(str);
	}
	return OK;
}
int PrintLine(Linelist L)//��ӡ�����ļ�
{
	Linelist l = L;
	while (l != NULL)
	{
		printf("\n ��ǰ�ļ����£�\n");
		if (l->heapptr_a.str != NULL)
		{
			int count = 0;
			while (count <= 99 && l->heapptr_a.str[count] != '\0') 
			{
				printf("%c", l->heapptr_a.str[count]);
				count++;
			}
			printf("\nA�鳤�ȣ�%d", l->heapptr_a.length);

		}
		if (l->heapptr_b.str != NULL)
		{
			int count = 0;
			while (count <= 99 && l->heapptr_b.str[count] != '\0')
			{
				printf("%c", l->heapptr_b.str[count]);
				count++;
			}
			printf("\nB�鳤�ȣ�%d", l->heapptr_b.length);
		}
		if (l->heapptr_c.str != NULL)
		{
			int count = 0;
			while (count <= 99 && l->heapptr_c.str[count] != '\0')
			{
				printf("%c", l->heapptr_c.str[count]);
				count++;
			}
			printf("\nC�鳤�ȣ�%d", l->heapptr_c.length);
		}
		if (l->heapptr_d.str != NULL)
		{
			int count = 0;
			while (count <= 99 && l->heapptr_d.str[count] != '\0')
			{
				printf("%c", l->heapptr_d.str[count]);
				count++;
			}
			printf("\nD�鳤�ȣ�%d", l->heapptr_d.length);
		}

		l = l->next;
	}
	
	return OK;
}
int DeleteHeap(Linelist &L)//�ͷŶѵĿռ�
{
	Linelist l = L;
	while (l != NULL)
	{
		if (l->heapptr_a.str)free(l->heapptr_a.str);
		if (l->heapptr_b.str)free(l->heapptr_b.str);
		if (l->heapptr_c.str)free(l->heapptr_c.str);
		if (l->heapptr_d.str)free(l->heapptr_d.str);
		l = l->next;
	}
	return OK;
}
int main()
{
	Linelist line;
	CreateFirstLine(line);
	CreateFile(line);
	PrintLine(line);
	DeleteHeap(line);
	system("pause");
}