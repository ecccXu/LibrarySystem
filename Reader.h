#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern struct Node* list;
extern struct Node1* list1;
void write_File1(struct Node1* headNode, char* fileName);

//菜单
void menu_reader()
{
	printf("\t\t--------------------------------------------------\n");
	printf("\t\t-----------------【读者管理系统】-----------------\n");
	printf("\n\t\t\t\t1.浏览读者个人信息\n");
	printf("\n\t\t\t\t2.新增读者个人信息\n");
	printf("\n\t\t\t\t3.查找读者个人信息\n");
	printf("\n\t\t\t\t4.修改读者个人信息\n");
	printf("\n\t\t\t\t5.删除读者个人信息\n");
	printf("\n\t\t\t\t0.返回主页\n");
	printf("\n\t\t--------------------------------------------------\n");
}

//定义读者类型
struct Reader
{
	char name[20];//姓名
	char sex[5];//性别
	char st_id[20];//学号
	char cclass[15];//班级：eg.物联网22-2
	char tele[15];//联系电话

	//int renum;//归还数量？
	//int lendnum;//借书数量？
};

//链表管理
struct Node1
{
	struct Reader data;
	struct Node1* next;
};

//创建表(初始化指针)
struct Node1* createList1()
{
	struct Node1* headNode = (struct Node1*)malloc(sizeof(struct Node1));
	headNode->next = NULL;
	return headNode;
}

//创建节点
struct Node1* createNode1(struct Reader data)
{
	struct Node1* newNode = (struct Node1*)malloc(sizeof(struct Node1));
	newNode->next = NULL;
	newNode->data = data;
	return newNode;
}

//插入节点(表头法插入)
void insertNode1(struct Node1* headNode, struct Reader data)//插入整个学生类型
{
	struct Node1* newNode = createNode1(data);
	newNode->next = headNode->next;
	headNode->next = newNode;
}

//查找功能（按名字查找）
void searchNode1(struct Node1* headNode, char* name)
{
	struct Node1* pNode = headNode->next;
	while (pNode != NULL)
	{
		if (strcmp(pNode->data.name, name))
		{
			pNode = pNode->next;
		}
		else
			break;
	}
	if (pNode == NULL)
	{
		printf("\n\t\t未找到相关信息!\n");
		system("pause");
	}
	else
	{
		printf("\n");
		printf("\t\t姓名\t性别\t学号\t\t班级\t\t电话\n");
		printf("\t\t%s\t%s\t%s\t%s\t%s\n", pNode->data.name, pNode->data.sex, pNode->data.st_id, pNode->data.cclass, pNode->data.tele);
		printf("\n");
	}
}
//判断用户是否符合(查找功能 ———— 按学号查找)
struct Node1* judge_id(struct Node1* headNode, char* st_id)
{
	struct Node1* pmove = headNode->next;
	while (pmove != NULL)
	{
		if (strcmp(pmove->data.st_id, st_id))
		{
			pmove = pmove->next;
		}
		else
			break;
	}
	if (pmove == NULL)
		return NULL;
	else
		return pmove;
}

//修改功能
void reviseNode1(struct Node1* headNode, char* name)
{
	struct Node1* move = headNode->next;
	while (move != NULL)
	{
		if (strcmp(move->data.name, name))
		{
			move = move->next;
		}
		else
			break;
	}
	if (NULL == move)
	{
		printf("\n未找到该用户！\n");
	}
	else
	{
		printf("\n请按顺序输入新的用户姓名，性别，学号，班级，电话:\n");
		scanf("%s", move->data.name);
		scanf("%s", move->data.sex);
		scanf("%s", move->data.st_id);
		scanf("%s", move->data.cclass);
		scanf("%s", move->data.tele);
		printf("修改成功！\n");
		write_File1(list1, "usersInfo.txt");
	}
}

//删除功能(按名字删除)
void deleteNode1(struct Node1* headNode, char* name)
{
	struct Node1* pNode = headNode->next;
	struct Node1* front_pNode = headNode;
	while (pNode != NULL)
	{
		if (strcmp(pNode->data.name, name))
		{
			pNode = pNode->next;
			front_pNode = front_pNode->next;
		}
		else
			break;
	}
	if (pNode == NULL)
	{
		printf("\n\t\t未找到该用户！\n");
	}
	else
	{
		front_pNode->next = pNode->next;
		free(pNode);
		pNode = NULL;
		printf("\n\t\t删除成功！\n");
	}
	write_File1(list1, "usersInfo.txt");
	printf("\n");
}

//打印链表
void printList1(struct Node1* headNode)
{
	struct Node1* move = headNode->next;
	printf("\t\t姓名\t性别\t学号\t\t班级\t\t电话\n");
	while (move)
	{
		printf("\t\t%s\t%s\t%s\t%s\t%s\n", move->data.name, move->data.sex, move->data.st_id, move->data.cclass, move->data.tele);
		move = move->next;
	}
	printf("\n");
}

//文件读操作
void read_File1(struct Node1* headNode, char* fileName)
{
	//1.开文件
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		fp = fopen(fileName, "w+");
	}
	//2.读文件
	struct Reader data;
	while (fscanf(fp, "%s\t%s\t%s\t%s\t%s\n", data.name, data.sex, data.st_id, data.cclass, data.tele) != EOF)
	{
		insertNode1(list1, data);
		memset(&data, 0, sizeof(data));
		/*
			初始化函数：将某一块内存中的内容全部设置为指定的值
			为新申请的内存做初始化工作
		*/
	}
	//3.关文件
	if (fp != NULL)
		fclose(fp);
}

//文件写操作
void write_File1(struct Node1* headNode, char* filename)
{
	//1.开文件
	FILE* fp;
	fp = fopen(filename, "w");
	//2.写文件
	struct Node1* move = headNode->next;
	while (move)
	{
		fprintf(fp, "%s\t%s\t%s\t%s\t%s\n", move->data.name, move->data.sex, move->data.st_id, move->data.cclass, move->data.tele);
		move = move->next;
	}
	//3.关
	fclose(fp);
}




//////判断读者是否借过书
//char judge1(struct Node1* HeadNode, char a)
//{
//	struct Node1* Pmove = HeadNode->next;
//	while (Pmove != NULL)
//	{
//		if (Pmove->data.st_id != a)
//		{
//			Pmove = Pmove->next;
//		}
//		else
//			break;
//	}
//	if (Pmove == NULL)
//		return 0;
//	else
//	{
//		if (Pmove->data.num>0&& Pmove->data.num<=5)
//			return Pmove->data.num;
//		else
//			return 0;
//	}
//
//}