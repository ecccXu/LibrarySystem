#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern struct Node* list;
extern struct Node1* list1;
void write_File(struct Node* headNode, char* fileName);

//菜单（图书管理）
void bookmenu()
{
	printf("\t\t--------------------------------------------------\n");
	printf("\t\t-----------------【图书管理系统】-----------------\n");
	printf("\n\t\t\t\t1.浏览图书信息\n");
	printf("\n\t\t\t\t2.新增图书信息\n");
	printf("\n\t\t\t\t3.查找图书信息\n");
	printf("\n\t\t\t\t4.修改图书信息\n");
	printf("\n\t\t\t\t5.删除图书信息\n");
	printf("\n\t\t\t\t0.返回主页\n");
	printf("\n\t\t--------------------------------------------------\n");
}

//定义图书类型
struct Book
{
	int num;//图书编号
	char title[30];//书名
	char author[30];//作者
	char press[20];//出版社
	int quantity;//数量
	double price;//价格
};

//链表管理
struct Node
{
	struct Book data;
	struct Node* next;
};

//创建表头(初始化指针)
struct Node* createList()
{
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	headNode->next = NULL;
	return headNode;
}

//创建节点
struct Node* createNode(struct Book data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->next = NULL;
	newNode->data = data;
	return newNode;
}

//插入节点(表头法插入)
void insertNode(struct Node* headNode, struct Book data)//插入整个图书类型
{
	struct Node* newNode = createNode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;
}

//查找功能（按书名查找）
void searchNode(struct Node* headNode, char* title)
{
	struct Node* pNode = headNode->next;
	while (pNode != NULL)
	{
		if (strcmp(pNode->data.title, title))
		{
			pNode = pNode->next;
		}
		else
			break;
	}
	if (pNode == NULL)
	{
		printf("\t\t未找到相关信息！\n");
		system("pause");
	}
	else
	{
		printf("\n");
		printf("\t\t编号\t书名\t作者\t出版社\t数量\t\t价格\n");
		printf("\t\t%d\t%s\t%s\t%s\t%d\t%.2f\n", pNode->data.num, pNode->data.title, pNode->data.author, pNode->data.press, pNode->data.quantity, pNode->data.price);
		printf("\n");
	}
}
//判断书籍是否符合(查找功能 ———— 按书名查找)
struct Node* judge_ttl(struct Node* HeadNode, char* title)
{
	struct Node* Pmove = HeadNode->next;
	while (Pmove != NULL)
	{
		if (strcmp(Pmove->data.title, title))
		{
			Pmove = Pmove->next;
		}
		else
			break;
	}
	if (Pmove == NULL)
		return NULL;
	else
		return Pmove;
}

//修改功能
void reviseNode(struct Node* headNode, char* title)
{
	struct Node* move = headNode->next;
	while (move != NULL)
	{
		if (strcmp(move->data.title, title))
		{
			move = move->next;
		}
		else
			break;
	}
	if (NULL == move)
	{
		printf("未找到该书籍！\n");
	}
	else
	{
		printf("\n请按顺序输入新的图书编号，书名，作者，出版社，数量，价格：\n");
		fflush(stdin);     //清空缓冲区
		scanf("%d%s%s%s%d%lf", &move->data.num, move->data.title, move->data.author, move->data.press, &move->data.quantity, &move->data.price);
		printf("修改成功！\n");
		write_File(list, "booksInfo.txt");
	}
}

//删除功能(按书名删除)
void deleteNode(struct Node* headNode, char* title)
{
	struct Node* pNode = headNode->next;
	struct Node* front_pNode = headNode;
	while (pNode != NULL)
	{
		if (strcmp(pNode->data.title, title))
		{
			pNode = pNode->next;
			front_pNode = front_pNode->next;
		}
		else
			break;
	}
	if (pNode == NULL)
	{
		printf("\t\t未找到该书籍！\n");
	}
	else
	{
		front_pNode->next = pNode->next;
		free(pNode);
		pNode = NULL;
		printf("\t\t删除成功！\n");
	}
	write_File(list, "booksInfo.txt");
	printf("\n");
}

//打印链表
void printList(struct Node* headNode)
{
	struct Node* Move = headNode->next;
	printf("\t\t编号\t书名\t作者\t出版社\t\t数量(单位:本)\t价格(单位:元/本)\n");
	while (Move)
	{
		printf("\t\t%d\t%s\t%s\t%s\t%d\t\t%.2f\n", Move->data.num, Move->data.title, Move->data.author, Move->data.press, Move->data.quantity, Move->data.price);
		Move = Move->next;
	}
	printf("\n");
}
//小列表
void printlist(struct Node* headNode)
{
	struct Node* move = headNode->next;
	printf("\t\t编号\t书名\t作者\t\t出版社\t\t数量(单位:本)\n");
	while (move)
	{
		printf("\t\t%d\t%s\t%s\t\t%s\t\t%d\n", move->data.num, move->data.title, move->data.author, move->data.press, move->data.quantity);
		move = move->next;
	}
	printf("\n");
}

/*数据文件储存于读取*/
//文件读操作
void read_File(struct Node* headNode, char* fileName)
{
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		fp = fopen(fileName, "w+");
	}
	struct Book data;
	while (fscanf(fp, "%d\t%s\t%s\t%s\t%d\t%lf\n", &data.num, data.title, data.author, data.press, &data.quantity, &data.price) != EOF)
	{
		insertNode(list, data);
		memset(&data, 0, sizeof(data));
	}
	if (fp != NULL)
		fclose(fp);
}
//文件写操作
void write_File(struct Node* headNode, char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "w");
	struct Node* move = headNode->next;
	while (move)
	{
		fprintf(fp, "%d\t%s\t%s\t%s\t%d\t%.2f\n", move->data.num, move->data.title, move->data.author, move->data.press, move->data.quantity, move->data.price);
		move = move->next;
	}
	fclose(fp);

}