#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
typedef char TElemType;

/* 二叉树节点的存储类型 */
typedef struct BiTNode {	//define stricture BiTree
	TElemType data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

/*按先序序列建立一棵二叉树*/
void CreatBiTree(BiTree T) {
	TElemType ch;
	//scanf("%c",&ch); //也可以运行
	ch = getchar();
	if (ch == ' ')
		T = NULL;
	else {
		T = (BiTree)malloc(sizeof(BiTNode));
		if (!T)
			exit(0);
		(T)->data = ch;  //生成根结点
		CreatBiTree((T)->lchild);  //构造左子树
		CreatBiTree((T)->rchild);  //构造右子树
	}
}
void  PrintData(TElemType x) {
	printf("%c", x);
}

void Visit(TElemType e) {
	printf("%c\t", e);
}

void PreOrder(BiTree T, void (*Visit)( TElemType e))   /*将Visit函数的首地址赋给指针变量p*/
{  /*前序遍历二叉树T，访问操作为Visit()函数*/
	if (T != NULL) {
		Visit(T->data);
		PreOrder(T->lchild, Visit);
		PreOrder(T->rchild, Visit);
	}
}

void InOrder(BiTree T, void (*Visit)( TElemType e)) { /*中序t */
	if (T != NULL) {
		InOrder(T->lchild, Visit);
		Visit(T->data);
		InOrder(T->rchild, Visit);
	}
}

void PostOrder(BiTree T, void (*Visit)( TElemType e)) { /*后序 */
	if (T != NULL) {
		PostOrder(T->lchild, Visit);
		PostOrder(T->rchild, Visit);
		Visit(T->data);
	}
}


int BTreeDepth(BiTree BT) {
	int leftdep, rightdep;
	if (BT == NULL)
		return (0);
	else {
		leftdep = BTreeDepth(BT->lchild);
		rightdep = BTreeDepth(BT->rchild);
		if (leftdep > rightdep)
			return (leftdep + 1);
		else
			return (rightdep + 1);
	}
}
int NodeCount(BiTree BT) {
	if (BT == NULL)
		return (0);
	else
		return (NodeCount (BT-> lchild) + NodeCount (BT-> rchild) + 1);
}
int LeafCount(BiTree BT) {
	if (BT == NULL)
		return (0);
	else if (BT-> lchild == NULL && BT-> rchild == NULL)
		return (1);
	else
		return (LeafCount (BT-> lchild) + LeafCount (BT-> rchild));
}
int NotLeafCount(BiTree BT) {
	if (BT == NULL)
		return (0);
	else if (BT-> lchild == NULL && BT-> rchild == NULL)
		return (0);
	else
		return (NotLeafCount (BT-> lchild) + NotLeafCount (BT-> rchild) + 1);
}
int OneChildCount(BiTree BT) {
	if (BT == NULL)
		return (0);
	else if ((BT-> lchild == NULL && BT-> rchild != NULL) || (BT-> lchild != NULL && BT-> rchild == NULL))
		return (OneChildCount (BT-> lchild) + OneChildCount (BT-> rchild) + 1);
	else
		return (OneChildCount (BT-> lchild) + OneChildCount (BT-> rchild));
}
int TwoChildCount(BiTree BT) {
	if (BT == NULL)
		return (0);
	else if (BT-> lchild == NULL || BT-> rchild == NULL)
		return (TwoChildCount (BT-> lchild) + TwoChildCount (BT-> rchild));
	else if (BT-> lchild != NULL && BT-> rchild != NULL)
		return (TwoChildCount (BT-> lchild) + TwoChildCount (BT-> rchild) + 1);
}

int  main() {
	int choice;
	BiTree root;

	printf("下面建立一棵二叉树，结点数据输入按先序次序。\n");
	printf("输入数据请注意，每一个非空结点的所有孩子数据都要给出\n");
	printf("若孩子为空，请用空格符表示。\n");
	printf("请输入二叉树结点的数据，这里设定为字符:\n");
	CreatBiTree(root);

	printf("================================\n");
	printf("1：先序序列：\n");
	printf("2：中序序列：\n");
	printf("3：后序序列：\n");
	printf("4：二叉树的深（高）度：\n");
	printf("5：二叉树的结点数：\n");
	printf("6：二叉树的叶子结点数：\n");
	printf("7：二叉树的度为2的结点数：\n");
	printf("8：二叉树的度为1的结点数：\n");
	printf("其它值则退出：\n");
	printf("================================\n");


	do {
		printf("请输入对应的操作码：");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				printf("\n先序序列为：");
				PreOrder(root, PrintData);
				printf("\n");
				break;
			case 2:
				printf("\n中序序列为：");
				InOrder(root, PrintData);
				printf("\n");
				break;
			case 3:
				printf("\n后序序列为：");
				PostOrder(root, PrintData);
				printf("\n");
				break;
			case 4:
				printf("二叉树的深度是：%d\n", BTreeDepth(root));
				break;
			case 5:
				printf("二叉树的结点数是：%d\n", NodeCount(root));
				break;
			case 6:
				printf("二叉树的叶子数是：%d\n", LeafCount(root));
				break;
			case 7:
				printf("二叉树的度为2的结点数是：%d\n", TwoChildCount(root));
				break;
			case 8:
				printf("二叉树的度为1的结点数是：%d\n", OneChildCount(root));
				break;
		}
	} while (choice > 0 && choice < 9);
	return 0;
}
