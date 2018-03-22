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
}Hstring;//堆的存储方式
typedef struct node {
	Hstring heapptr_a;// heap's pointer 存储1-99的字符，最后一个是/0
	Hstring heapptr_b;// heap's pointer 存储100-199字符
	Hstring heapptr_c;// heap's pointer 200-299
	Hstring heapptr_d;// heap's pointer 300-399
	node* next;//连接下一行
}Node, *Linelist;//每行的存储结构
int CreateFirstLine(Linelist &L)         //创建文件首行头结点 
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
Linelist LineInsert_L(Linelist &L, int i)    //插入一行到第i个节点处
{
	Linelist ptr = L;
	Linelist s=NULL;//要插入的行 
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
//在当前堆的末尾加入一个字符
{
	if (count_word <= 99)
	{
		line->heapptr_a.length = count_word;
		current_heap.str[count_word] = str;
	}
	else if (count_word == 100)//第101个字符存在第二个堆
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
		current_heap.str = line->heapptr_c.str;//转存C堆
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
int CreateFile(Linelist &L)//创建一个文件
{
	char str;
	int count_word = 0;//输入一行的总字数（不含/0）
	Linelist line = L;
	Hstring current_heap;
	line->heapptr_a.str = (char*)malloc(100 * sizeof(char));//分配堆
	memset(line->heapptr_a.str, '\0', 100 * sizeof(char));//数组全部初始化为/0
	current_heap = line->heapptr_a;
	str = _getch();
	putchar(str);
	while (str != '#')//首次读取  设终止符为#
	{
		if (str == 13)
		{
			current_heap=Add_A_Word(line, current_heap, count_word, str);
			printf("\n");
			count_word = 0;
			line = LineInsert_L(L, g_Linenumber + 1);//新建一行链表
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
int PrintLine(Linelist L)//打印整个文件
{
	Linelist l = L;
	while (l != NULL)
	{
		printf("\n 当前文件如下：\n");
		if (l->heapptr_a.str != NULL)
		{
			int count = 0;
			while (count <= 99 && l->heapptr_a.str[count] != '\0') 
			{
				printf("%c", l->heapptr_a.str[count]);
				count++;
			}
			printf("\nA块长度：%d", l->heapptr_a.length);

		}
		if (l->heapptr_b.str != NULL)
		{
			int count = 0;
			while (count <= 99 && l->heapptr_b.str[count] != '\0')
			{
				printf("%c", l->heapptr_b.str[count]);
				count++;
			}
			printf("\nB块长度：%d", l->heapptr_b.length);
		}
		if (l->heapptr_c.str != NULL)
		{
			int count = 0;
			while (count <= 99 && l->heapptr_c.str[count] != '\0')
			{
				printf("%c", l->heapptr_c.str[count]);
				count++;
			}
			printf("\nC块长度：%d", l->heapptr_c.length);
		}
		if (l->heapptr_d.str != NULL)
		{
			int count = 0;
			while (count <= 99 && l->heapptr_d.str[count] != '\0')
			{
				printf("%c", l->heapptr_d.str[count]);
				count++;
			}
			printf("\nD块长度：%d", l->heapptr_d.length);
		}

		l = l->next;
	}
	
	return OK;
}
int DeleteHeap(Linelist &L)//释放堆的空间
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