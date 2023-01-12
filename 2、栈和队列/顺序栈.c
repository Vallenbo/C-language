#include "stdio.h"
#include "malloc.h"
#include "stdbool.h"

typedef struct {
	int * head;
	int length;
	int actual;
} table ;

void Init_list(table * p, int L) {	//对p这个表进行初始化
	p->head = (int * )malloc(sizeof(int) * L) ;	//定义表所需的动态空间
	if (!p->head) {
		printf("初始化失败\n");
		exit(-1);
	}
	p->length = L;	//内存分配好之后初始化长度
	p->actual = 0;	//初始化实际元素个数
	return ;
}

bool table_judge(table * list) { //判断表是否可用
	if ( 0 <= list->actual && 1 <= list->length && list->actual < list->length)
		return true;
	else
		return false;
}

void table_judge_print(table * list) { //输出表储存的详细信息
	if (1 == table_judge(list)) {
		printf("顺序表可用：head= %p, length = %d, actual = %d\n", list->head, list->length, list->actual);
		for (int i = 0; i < list->actual ; i++) {
			printf("%d\t", list->head[i]);
		}
	} else
		printf("顺序表不可用！");
}

void append_element(table * list, int num1) { //单个元素进行存储
	if (table_judge(list)) {
		list->head[list->actual] = num1;
		(list->actual) ++;
		printf("存储成功\n");
	} else
		printf("存储失败\n");
}

int main() {
	int L, x, num, num1;
	table list;	//定义一个表结点

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
