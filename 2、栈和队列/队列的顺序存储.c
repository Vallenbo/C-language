#include<stdio.h>
#include<stdlib.h>
# define MAXQSIZE 100
# define OK 1
# define ERROR 0
typedef char QElemType; /* 定义QElemType为char或别的自定义类型 */
/* 顺序队列的存储类型 */
typedef struct SqQueue {    //define structure SqQueue
	QElemType *base;
	int front;
	int rear;
} SqQueue, * P_SqQueue;

/* 构造空顺序队列*/
int InitQueue(P_SqQueue Q) { //InitQueue()
	Q->base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
	if (!Q->base) {
		printf("分配空间失败! \n");
		return (ERROR);
	}
	Q->front = Q->rear = 0;
	printf("队列初始化成功! \n");
	return (OK);
} //InitQueue() end

/* 求顺序队列长度*/
int QueueLength(P_SqQueue Q) {     //QueueLength()
	return ((Q->rear - Q->front + MAXQSIZE) % MAXQSIZE);
}

/*在顺序队列尾插入新元素*/
int EnQueue(P_SqQueue Q, QElemType e) { //EnQueue()
	if ((Q->rear + 1) % MAXQSIZE == Q->front) {
		printf("队列已满! \n");
		return (ERROR);
	}
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
	return (OK);
} //EnQueue() end

/*在顺序队列头删除元素*/
int DeQueue(P_SqQueue Q) { //DeQueue()
	QElemType e;

	if (Q->rear == Q->front) {
		printf("队列为空! \n");
		return (ERROR);
	}
	printf("出队元素为：%c\n", Q->base[Q->front]);
	Q->front = (Q->front + 1) % MAXQSIZE;
	printf("出队元素回收成功\n");
} //DeQueue() end

void display(SqQueue Q) {
	if (Q.front == Q.rear) {
		printf("队列为空!\n");
		return;
	}
	int i = Q.front;
	while (i % MAXQSIZE != Q.rear) {
		printf("<- %c", Q.base[i]);
		i++;
	}
	printf(" ^这里是入队方向\n");
}

int main() {
	QElemType e;
	int choice;
	SqQueue Q;
	printf("==============================\n");
	printf("0、退出\n");
	printf("1、初始化\n");
	printf("2、入队\n");
	printf("3、出队\n");
	printf("4、显示队列元素\n");
	printf("==============================\n");
	do {
		printf("你操作选择是(0-4):");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				InitQueue(&Q);
				break;
			case 2:
				fflush(stdin);//清除输入缓冲区
				printf("请输入要入队的字符或字符串,以'#'结束:");
				while ((e = getchar()) != '#') {
					EnQueue(&Q, e);
				}
				break;
			case 3:
				DeQueue(&Q);
				break;
			case 4:
				display(Q);
				break;
		}
	} while (choice > 0 && choice <= 4);
	return 0;
}
