#include "stdio.h"
#include "malloc.h"
#define ListSize 100      //线性表的最大长度

typedef struct {
	int * elem; //用数组存储线性表中的元素
	int length; //顺序表中元素的个数
	int actural; //实际存储位置
} SeqList, * P_SeqList;

//初始化顺序表
P_SeqList Init_list(P_SeqList new, int num) {
	new->elem = (int *)malloc(num * sizeof(int));
	if (!new->elem) {
		printf("初始化失败\n");
	}
	new->length = num;
	new->actural=0;
	return new;
}

//返回数据表中第i个元素的值
int GetData(P_SeqList L, int i) {
	if (L->length < 1 || (L->length > LengthList(L))) {
		return 0;
	}
	//数据元素的序号从1开始，数组下表从0开始，第i个元素对应的数组下标为i-1;
	return L->data[i - 1];
}

//在L中第i个位置，插入新的数据元素e
P_SeqList add(SeqList t, int elem, int location){
	if (location > t.actural || location < 1) {
		printf("插入位置有问题\n");
	}
	if (t.length >= t.size) {
		t.head = (int *)realloc(t.head, (t.size + 1) * sizeof(int));
		if (!t.head) {
			printf("存储分配失败\n");
		}
		t.size += 1;
	}
	for (int i = t.length - 1; i >= add - 1; i--) {
		t.head[i + 1] = t.head[i];
	}
	t.head[add - 1] = elem;
	t.length++;
	return t;
}

//删除L的第i个数据元素
int DelList(P_SeqList L, int i, int* e) {
	if (L->length < 1) {
		printf("表为空！\n");
		return  0;
	}
	*e = L->data[i - 1];
	for (int k = i; k < L->length; k++) {
		L->data[k - 1] = L->data[k];
	}
	L->length--;
	return *e;
}

//查找e在表中的位置
int Locate(P_SeqList L, int e) {
	for (int k = 0; k < L->length; k++) {
		if (L->data[k] == e) {
			//k为e对应的数组下标，在表中对应序号应为k+1
			return k + 1;
		}
	}
	return 0;
}

//头插，在表头插入元素e
void PushFront(P_SeqList L, int e) {
	if (L->length == ListSize) {
		printf("顺序表已满，不能插入！\n");
	}
	//将表中元素依次后移一位
	for (int k = L->length; k > 0; k--) {
		L->data[k] = L->data[k - 1];
	}
	//插入元素
	L->data[0] = e;
	L->length++;
}
int EmptyList(P_SeqList L) {
	if (L->length == 0) {
		return 1;
	}
	return 0;
}

//头删,删除顺序表中的第一个元素，把顺序表中的元素依次往前移动一位
void PopFront(P_SeqList L) {
	if (EmptyList(L)) {
		printf("顺序表为空，不能插入！\n");
	}
	for (int k = 1; k <= L->length - 1; k++) {
		L->data[k - 1] = L->data[k];
	}
	L->length--;
}

//尾插
void PushBack(P_SeqList L, int e) {
	if (L->length == ListSize) {
		printf("顺序表已满，不能插入!\n");
	}
	L->data[L->length] = e;
	L->length++;
}


//尾删
void PopBack(P_SeqList L) {
	if (EmptyList(L)) {
		printf("表为空！\n");
	}
	L->length--;
}

//清空顺序表
void ClearList(P_SeqList L) {
	L->length = 0;
}

//打印表中元素
void PrintList(P_SeqList L) {
	if (EmptyList(L)) {
		printf("表为空！\n");
		return;
	}
	for (int k = 0; k < L->length; k++) {
		printf("%-3d", L->data[k]);
	}
	printf("\n");
}

int main() {
	int L, x, num, num1;
	SeqList list;	//定义一个表结点
	printf("1、初始化表\n");
	printf("2、查看表的详细信息\n");
	printf("3、对表进行存储\n");
	printf("！！！按任意键退出！！！\n");
	printf("\n请输入操作:\n");
	scanf("%d", &x);
	switch (x) {
		case 1:
			printf("开始创建顺序表......\n");
			printf("请输入表元素个数：\n");
			scanf("%d", &L);
			Init_list(&list, L);
			break;
		case 2:
			table_judge_print(&list);
			break;
		case 3:
			printf("请输入存储的个数：\n");
			scanf("%d", &num);
			for (int i = 0; i < num; i++) {
				printf("请输入该数：\n");
				scanf("%d", &num1);
				append_element(&list, num1);
			}
		default:
			return 0;
	}
}
