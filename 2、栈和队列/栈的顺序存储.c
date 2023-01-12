#include "stdio.h"
#include "stdlib.h"
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0
typedef char SElemType;

/* 顺序栈的存储类型 */
typedef struct SqStack {       //define structure SqStack()
	SElemType * base;
	SElemType * top;
	int stacksize;
} SqStack, * P_SqStack;

/*初始化顺序栈*/
int InitStack(P_SqStack S) { //InitStack() sub-function
	S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S->base) {
		printf("分配空间失败!\n");
		return (ERROR);
	}

	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	printf("栈初始化成功！\n");
	return (OK);
} //InitStack() end

/*将元素压入顺序栈*/
void Push(P_SqStack S, SElemType e) {
	if (S->top - S->base == S->stacksize) {
		printf("栈满！\n");
		return ERROR;
	}
	*S->top++ = e;
	printf("存储成功\n");
} //Push() end

/* 将元素弹出顺序栈*/
void Pop(P_SqStack S, SElemType e) {
	if (S->top == S->base) return ERROR;
	S->top = --S->top;
	printf("出栈元素为：%c\n", *S->top);
} //Pop() end

/*取顺序栈顶元素*/
void GetTop(P_SqStack S) {
	if (S->top == S->base) {
		printf("栈为空\n");
		return ERROR;
	}
	S->top = --S->top;
	printf("栈顶元素的值是:%c\n", *S->top);
} //GetTop() end


//显示栈中元素
void display(SqStack s) {
	if (s.top == s.base) {
		printf("栈为空\n");
		return ERROR;
	}
	for (SElemType * P = --s.top; P >= s.base; P--) {
		printf("%c->", *P);
	}
}

int main() {
	int choice;
	SElemType e;
	SqStack s;
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
		scanf("%d", &choice);
		while (choice < 0 || choice > 5)  {
			printf("输入有误，请重新输入(0-5):");
			scanf("%d", &choice);
		}
		switch (choice) {
			case 0:
				exit(1);
			case 1:
				InitStack(&s);
				break;
			case 2:
				printf("请输入要入栈的元素：\n");
				scanf("%s", &e);
				Push(&s, e);
				break;
			case 3:
				Pop(&s, e);
				break;
			case 4:
				GetTop(&s);
				break;
			case 5:
				printf("栈中元素的值是为：\n");
				display(s);
				break;
		}
	} while (1);
	return 0;
}
