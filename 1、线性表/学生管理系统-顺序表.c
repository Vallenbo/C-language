#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define  LIST_INIT_SIZE 100
#define  LISTINCREMENT 10

typedef struct {
	char xuehao[14];//学号
	char name[20];  //姓名
	int sex;        //性别
	char tel[14];  //联系电话
	char qq[12];   //QQ号
} ElemType;

typedef struct {
	ElemType  * elem; //顺序表的存储空间基址，相当于一个一维的数组名
	int        length; //表的实际元素个数，即表的长度
	int        listsize; //最大可存储的元素个数，表的长度的上限
} SqList, * P_SqList;

void InitSeqList(P_SqList L) { //初始化表
	int i, n;
	ElemType *p;
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	L->length = 0;
	L->listsize = LIST_INIT_SIZE;

	printf("请输入初始化数据的个数:");
	scanf("%d", &n);

	if (n > L->listsize) {
		printf("数据太多，不足以存储！");
		return;
	}

	p = L->elem;
	L->length = n;

	for (i = 0; i < n; i++) {
		printf("请输入第%d个数据(学号  姓名  性别（0或1） 联系电话  QQ号)：\n", i + 1);
		scanf("%s%s%d%s%s", p->xuehao, p->name, &p->sex, p->tel, p->qq);
		p++;
	}
	return;
}

void PrintSeqList(P_SqList L) {
	int i;
	printf("学号        姓名         性别      联系电话      QQ号\n");

	for (i = 0; i < L->length; i++) {
		printf("%-14s%-14s", L->elem[i].xuehao, L->elem[i].name);
		if (L->elem[i].sex)   printf("  男  ");
		else   printf("  女  ");
		printf("%-14s%-10s\n", L->elem[i].tel, L->elem[i].qq);
	}
	printf("表中实际长度为：%d", L->length);
}

int InsertSeqList(P_SqList L, int i, ElemType e) {
	ElemType *q, *p;

	if (L->length + 1 > L->listsize )  {
		printf("表满，失败！");
		return 0;
	}

	if (i < 1 || i > L->length + 1)   {
		printf("插入位置错误，失败！");
		return 0;
	}
	q = &(L->elem[i - 1]);

	for (p = &(L->elem[L->length - 1]); p >= q; --p) {
		strcpy((p + 1)->xuehao, p->xuehao);
		strcpy((p + 1)->name, p->name);
		(p + 1)->sex = p->sex ;
		strcpy((p + 1)->tel, p->tel);
		strcpy((p + 1)->qq, p->qq);
	}
	strcpy(q->xuehao, e.xuehao);
	strcpy(q->name, e.name);
	q->sex = e.sex ;
	strcpy(q->tel, e.tel);
	strcpy(q->qq, e.qq);
	L->length++;
	return 1;
}

int LocateList(P_SqList L, char *x) {
	int i = 0;

	while (i < L->length ) {
		if (0==strcmp(L->elem[i].xuehao, x )) {
			printf("学号        姓名         性别      联系电话      QQ号\n");
			printf("%-14s%-14s", L->elem[i].xuehao, L->elem[i].name);
			if (L->elem[i].sex)   printf("  男  ");
			else   printf("  女  ");
			printf("%-14s%-10s\n", L->elem[i].tel, L->elem[i].qq);
			return i;
		}
		++i;
	}
	return 0;
}

int DeleteList(P_SqList L, int i) { //删除元素
	if (!L->length) {
		printf("表空，删除失败！\n");
		return 0;
	}

	if (i < 1 || i > L->length)   {
		printf("删除位置错，失败！\n");
		return 0;
	}

	for (int j = i; j <= L->length - 1; j++) {
		strcpy(L->elem[j - 1].xuehao, L->elem [j].xuehao );
		strcpy(L->elem [j - 1].name, L->elem [j].name );
		L->elem [j - 1].sex = L->elem [j].sex ;
		strcpy(L->elem [j - 1].tel, L->elem [j].tel  );
		strcpy(L->elem [j - 1].qq, L->elem [j].qq  );
	}
	L->length --;
	return 1;
}

int main() {
	int i, n, k, x;
	SqList L;
	ElemType e;

	while (1) {
		printf("\n---欢迎来到学生管理系统v1.0---\n");
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
				printf("开始创建顺序表......\n");
				InitSeqList(&L);
				break;
			case 2:
				PrintSeqList(&L);
				break;
			case 3:
				printf("请输入要追加的数据个数:");  //下面代码为表当前最后一个数据（记录）的后面插入数据，如果要在表的已有数据之间插入数据应怎样写代码？
				scanf("%d", &n);
				k = L.length;
				if (k + n > L.listsize )  {
					printf("要追加的数据太多表满，失败！");
					return 0;
				}
				for (i = k + 1; i <= k + n; i++) {
					printf("请输入要追加的第%d个数据(学号  姓名  性别（0或1） 联系电话  QQ号)：\n", i - k);
					scanf("%s%s%d%s%s", e.xuehao, e.name, &e.sex, e.tel, e.qq);
					InsertSeqList(&L, i, e);
				}
				break;
			case 4:
				printf("请输入要删除的元素位置:");
				scanf("%d", &n);
				DeleteList(&L, n);
				break;
			case 5:
				printf("请输入要查找的元素学号:");
				scanf("%s", &e.xuehao);
				LocateList(&L, &e.xuehao);
				break;
			default:
				return 0;
		}
	}
}
