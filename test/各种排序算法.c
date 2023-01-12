#include<malloc.h>
#include<stdio.h>
#include<process.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
typedef int Status; // Status是函数的类型,其值是函数结果状态代码，如OK等
typedef int Boolean; // Boolean是布尔类型,其值是TRUE或FALSE
typedef int InfoType; // 定义其它数据项的类型
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))
#define MAX_SIZE 20 // 一个用作示例的小顺序表的最大长度
typedef int KeyType; // 定义关键字类型为整型

typedef struct RedType { // 记录类型
	KeyType key; // 关键字项
	InfoType otherinfo; // 其它数据项，具体类型在主程中定义
}RedType;

typedef struct SqList { // 顺序表类型
	RedType r[MAX_SIZE + 1]; // r[0]闲置或用作哨兵单元
	int length; // 顺序表长度
}SqList;

void InsertSort(SqList *L) {
	// 对顺序表L作直接插入排序。
	int i, j;
	for (i = 2; i <= L->length; ++i)
		if LT(L->r[i].key, L->r[i - 1].key) { // "<",需将L->r[i]插入有序子表
			L->r[0] = L->r[i]; // 复制为哨兵
			for (j = i - 1; LT(L->r[0].key, L->r[j].key); --j)
				L->r[j + 1] = L->r[j]; // 记录后移
			L->r[j + 1] = L->r[0]; // 插入到正确位置
		}
}

void BInsertSort(SqList *L) {
	// 对顺序表L作折半插入排序。
	int i, j, m, low, high;
	for (i = 2; i <= L->length; ++i) {
		L->r[0] = L->r[i]; // 将L->r[i]暂存到L->r[0]
		low = 1;
		high = i - 1;
		while (low <= high) {
			// 在r[low->->high]中折半查找有序插入的位置
			m = (low + high) / 2; // 折半
			if LT(L->r[0].key, L->r[m].key)
				high = m - 1; // 插入点在低半区
			else
				low = m + 1; // 插入点在高半区
		}
		for (j = i - 1; j >= high + 1; --j)
			L->r[j + 1] = L->r[j]; // 记录后移
		L->r[high + 1] = L->r[0]; // 插入
	}
}




//* =====编写快速排序算法======


int Partition_1(SqList *L,int low,int high)
{
    RedType temp;
    int pivotkey = L->r[low].key;
    while(low < high){
        while(low < high && L->r[high].key >= pivotkey)
            --high;
        temp = L->r[low];
        L->r[low] = L->r[high];
        L->r[high] = temp;
        while(low < high && L->r[low].key <= pivotkey)
            ++low;
        temp = L->r[low];
        L->r[low] = L->r[high];
        L->r[high] = temp;
    }
    return low;
}


void QuickSort(SqList *L,int low,int high)
{
    int pivoloc;
    if(low < high){
        pivoloc = Partition_1(L,low,high);
        QuickSort(L,low,pivoloc-1);
        QuickSort(L,pivoloc+1,high);
    }
}


void print(SqList L) {
	int i;
	for (i = 1; i <= L.length; i++)
		printf("(%d,%d)", L.r[i].key, L.r[i].otherinfo);
	printf("\n");
}


#define N 8

int main() {
	RedType d[N] = {{4, 1}, {38, 2}, {85, 3}, {97, 4}, {56, 5}, {13, 6}, {27, 7}, {29, 8}};
	SqList l1, l2, l3;
	int i;
	for (i = 0; i < N; i++) // 给l1->r赋值
		l1.r[i + 1] = d[i];
	l1.length = N;
	l2 = l3 = l1; // 复制顺序表l2、l3与l1相同
	printf("排序前:\n");
	print(l1);
	InsertSort(&l1);
	printf("直接插入排序后:\n");
	print(l1);
	BInsertSort(&l2);
	printf("折半插入排序后:\n");
	print(l2);
	//快速排序算法调用（快速排序算法须自己编写）
	QuickSort(&l3,1,l3.length);
	printf("快速排序后:\n");
	print(l3);
	return 0;
}
