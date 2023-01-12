#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
typedef char SElemType;

/* 链式栈的存储类型 */
typedef struct SNode {   //define structure LinkStack
	SElemType data[20];
	struct SNode *next;
} SNode, *LinkStack;

LinkStack InitStack_L (LinkStack top) {
	top = (LinkStack)malloc(sizeof(SNode));
	if (!top) {
		printf("初始化失败\n");
		return ERROR;
	}
	top->next = NULL;
	printf("\n\n栈初始化成功！\n\n");
	return top;
}

/* 将元素压入链式栈 入栈的元素的值在此函数内从键盘输入*/
int Push_L(LinkStack top) { //Push_L()
	LinkStack new = (LinkStack)malloc(sizeof(SNode));
	if (!new) {
		printf("新节点创建失败！");
		return ERROR;
	}
	printf("请输入节点的数据:\n");
	scanf("%s", new->data);
	new->next = top->next;
	top->next = new;
	return OK;
} //Push_L() end

/*将元素弹出链式栈*/
LinkStack Pop_L(LinkStack top) { //Pop_L()
LinkStack p = top->next;
	if (!top->next) {
		printf("链栈为空\n");
		return;
	}
	printf("出栈元素为：%s\n", p->data);
	top->next=p->next;
	free(p);
	printf("元素弹出成功！\n");
	return top;
} //Pop_L() end

/*取链式栈顶元素*/
void GetTop_L(LinkStack top, SElemType e[]) { //GetTop_L()
	if (!top->next) {
		printf("链栈为空!\n");
	} else {
		strcpy(e, top->next->data);
	}
} //GetTop_L() end

void display(LinkStack top) {
	LinkStack p = top;

	if (!p->next) {
		printf("栈为空!\n");
		return;
	}

	while (p->next) {
		printf("%s", p->next->data);
		printf("->");
		p = p->next;
	}
}


int main() {
	char choice;
	SElemType  e[20] = "";
	LinkStack s = NULL;
	do {
		printf("\n===============================\n");
		printf("           0:退出\n");
		printf("           1:初始化栈\n");
		printf("           2:入栈\n");
		printf("           3:出栈\n");
		printf("           4:读取栈顶元素\n");
		printf("           5:显示栈中元素\n");
		printf("===============================\n");
		printf("输入操作选择代码(0-5):");
		fflush(stdin);
		scanf("%c", &choice);
		while (choice < '0' || choice > '5') {
			printf("输入有误，请重新输入(0-5):");
			fflush(stdin);
			scanf("%c", &choice);
		}
		switch (choice) {
			case '0':
				exit(1);
			case '1':
				s = InitStack_L(s);
				break;
			case '2':
				Push_L(s);
				break;
			case '3':
				s = Pop_L(s);
				break;
			case '4':
				GetTop_L(s, e);
				printf("栈顶元素的值是:%s\n", e);
				break;
			case '5':
				printf("栈中元素的值是: ");
				display(s);
		}
	} while (1);
	return 0;
}
