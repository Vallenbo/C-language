#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char xuehao[14];//学号
	char name[20];  //姓名
	int sex;        //性别
	char tel[14];  //联系电话
	char qq[12];   //QQ号
} ElemType;

typedef struct LNode {
	ElemType data;
	struct LNode *next;
} LNode, *LinkList;

LinkList CreatList(LinkList head) { //头插法建立链表
	LinkList p;
	char flag = 'y';
	head = (LinkList)malloc(sizeof(LNode)); //生成头结点
	head->next = NULL;
	while ((flag == 'Y') || (flag == 'y')) {
		p = (LinkList)malloc(sizeof(LNode));
		if (!p)  exit(-1);
		printf("请输入数据(学号     姓名    性别（0或1）      联系电话       QQ号)：\n");
		scanf("%s%s%d%s%s", &p->data.xuehao, &p->data.name, &p->data.sex, &p->data.tel, &p->data.qq);
		head->next = p;
		p->next = NULL;
		getchar();
		printf("继续输入吗？（y/n）");
		scanf("%c", &flag);
	}
	return head;
}

void PrintList(LinkList head) {
	LNode *p;
	p = head->next;
	printf("  学号         姓名         性别        联系电话       QQ号\n");
	printf("------------------------------------------------------------\n");

	do {
		printf("%-14s%-14s", p->data.xuehao, p->data.name);
		if (p->data.sex) printf("  男  ");
		else printf("  女  ");
		printf("%-14s%-10s\n", p->data.tel, p->data.qq);
		printf("--------------------------------------------------------\n");
		p = p->next;
	} while (p != NULL);
}

void InsertLinkList(LinkList head) { //将插入位置和插入的数据信息改为输入，不作为形参传入信息。
	LinkList p = head, s;
	int i, j = 1;

	printf("请输入要插入结点位置:");
	scanf("%d", &i);

	while (p && j < i - 1) {
		p = p->next ;
		j++;
	}

	if (!p || j < i - 1)  {
		printf("错误！\n");
		return;
	}
	s = (LinkList)malloc(sizeof(LNode));
	printf("请输入要插入的数据：\n");
	printf("学号     姓名    性别（0或1）      联系电话       QQ号\n");
	scanf("%s%s%d%s%s", &s->data.xuehao, &s->data.name, &s->data.sex, &s->data.tel, &s->data.qq);
	s->next = p->next ;
	p->next = s;
	return;
}

void GetElemList(LinkList head, ElemType e) { //读取位置改为在函数内输入
	LinkList p;
	int i, j = 1;
	printf("请输入要读取第几个元素：");
	scanf("%d", &i);
	p = head->next;
	while (p && j < i) {
		p = p->next ;
		j++;
	}
	if (!p || j > i)  {
		printf("没有找到！\n");
		return;
	}
	printf("学号     姓名    性别（0或1）      联系电话       QQ号\n");
	printf("%-14s%-14s", p->data.xuehao, p->data.name);
	if (p->data.sex)   printf("  男  ");
	else   printf("  女  ");
	printf("%-14s%-10s\n", p->data .tel, p->data.qq);
	e = p->data;
}

int DeleteElemLinkList(LinkList head) { //增加下面的函数并适当调整main函数。
	LinkList p = head, q;
	ElemType e;
	int i, j = 1;
	printf("请输入要删除结点位置:");
	scanf("%d", &i);

	while (p && (j < i)) {
		p = p->next ;
		j++;
	}

	if (!p || j < i)  {
		printf("错误！\n");
		return   0;
	}
	q = p->next ;
	e = q->data ;
	p->next = q->next ;
	free(q);
	return  1;
}

int main() {
	int x;
	LinkList head; //定义头指针
	ElemType e;

	while (1) {
		printf("\n---欢迎来到单链表学生管理系统v1.0---\n");
		printf("1、初始化表\n");
		printf("2、查看表的详细信息\n");
		printf("3、对表元素进行存储\n");
		printf("4、对表元素进行删除\n");
		printf("5、对表元素进行查询\n");
		printf("！！！按0键退出！！！\n");
		printf("\n请输入操作:\n");
		scanf("%d", &x);
		switch (x) {
			case 1:
				printf("开始创建单链表......\n");
				head = CreatList(head);
				break;
			case 2:
				PrintList(head);
				break;
			case 3:
				InsertLinkList(head);
				break;
			case 4:
				DeleteElemLinkList(head);
				break;
			case 5:
				GetElemList(head, e);
				break;
			default:
				return 0;
		}
	}
}
