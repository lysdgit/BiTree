//第九题 二叉树及应用
#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10
#define OK      1
#define ERROR   0 
typedef char ElemType;

//树节点
typedef struct BiTNode{
    ElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//栈
typedef struct{
    BiTree *base;
    BiTree *top;
    int stacksize;
}sqStack;

//结点结构
typedef struct QNode{
    BiTree data;
    struct QNode * next;
}QNode, *QueuePtr;

//队列结构
typedef struct{
    QueuePtr front;         //队头指针
    QueuePtr rear;          //队尾指针
}LinkQueue;

//初始化队列 
int InitQueue(LinkQueue *Q){

    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
    if(!Q->front)
        return ERROR;
    Q->front->next = NULL;
    //printf("队列初始化成功！\n");
    return OK;
}

//进队
int EnQueue(LinkQueue *Q, BiTree e){
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof(QNode));
    if(!p)
        return ERROR;
    p->data = e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return OK;
}

//删除队头
int DeQueue(LinkQueue *Q, BiTree *e){

    QueuePtr p;

    if(Q->front == Q->rear)
        return ERROR;
    p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if(Q->rear == p)
        Q->rear = Q->front;
    free(p);
    //printf("删除队头成功！\n");
    return OK;
}

//队列判空 
int QueueEmpty(LinkQueue *Q){
    if(Q->front == Q->rear){
        //printf("队列为空\n");
        return ERROR;
    }
    //printf("队列不为空\n");
    return OK;
}

//初始化栈 
int InitStack(sqStack *S){
    S->base = (BiTree * )malloc(STACK_INIT_SIZE * sizeof(BiTree));
    if(!S->base){
        exit(0);
    }
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;

}

//入栈
int Push(sqStack *S, BiTree e)
{
    if(S->top - S->base >= S->stacksize)           //栈满， 追加空间
    {
        S->base = (BiTree *)realloc(S->base, (S->stacksize + STACKINCREMENT)* sizeof(BiTree));
        if(!S->base){
            exit(0);                 //分配失败
        }
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }

    *(S->top) = e;
    S->top++;
    return OK;
}

//出栈
int Pop(sqStack *S, BiTree *e){
    if(S->top == S->base){
        return ERROR;                  //判空
    }
    *e = * --(S->top);
    return OK;
}

//栈判空 
int StackEmpty(sqStack S){
    if(S.top - S.base == 0){
        //printf("StackEmpty()当前栈为空！\n");
        return ERROR;
    }
    return OK;
}

//取栈顶元素 
int GetTop(sqStack *S, BiTree *e){
    if(S->top == S->base){
        return ERROR;
    }
    *e = *(S->top-1);
    return OK;

}

//获取栈的长度 
int StackLength(sqStack s){
    return (s.top - s.base);
}

//销毁栈 
int DestroyStack(sqStack *S){
    free(S);
    return OK;
}

//重新定义输出函数 
void print(ElemType e){
    printf("%c  ", e);
}

//层次遍历二叉树
int NLevelOrderTraverse(BiTree T){

    LinkQueue Q;
    InitQueue(&Q);
    BiTree p;
    p = T;
    EnQueue(&Q, p);
    while(QueueEmpty(&Q) == 1){
        DeQueue(&Q, &p);
        if(p->lchild != NULL){
            EnQueue(&Q,p->lchild);
        }
        if(p->rchild != NULL){
            EnQueue(&Q, p->rchild);
        }
        print(p->data);
    }
    return OK;
}

//先序创建树
int CreateBiTree(BiTree *T){
    ElemType c;
    scanf("%c", &c);
    if('/' == c ){
        *T = NULL;
    }
    else{
        if(!((*T) = (BiTNode *)malloc(sizeof(BiTNode)))) 
			return ERROR;
        (*T)->data = c;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
    return OK;
}

//层次创建树 
BiTNode *que[1000];
int s[1000],ss = 0;
int front = 0, rear = 0;
int num ;

BiTNode *CreateBiTree1(){
	char ch;			 //结点信息变量
	BiTNode *Q[100];	//设置指针类型数组来构成队列
	int front, rear;	//队头和队尾指针变量
	BiTNode *root, *s;	//根节点指针和中间指针变量
	root = NULL;	    //二叉树置空
	front = 1, rear = 0;	//设置队列指针变量初值
	while((ch=getchar()) != '/'){
		//输入一个字符，当不是结束符时执行以下操作
		s = NULL;
		if(ch != '/'){
			s = (BiTNode*)malloc(sizeof(BiTNode));
			s->data = ch;
			s->lchild = NULL;
			s->rchild = NULL;
		}
		rear++;	//队尾指针增1，指向新结点地址存放的单元
		Q[rear] = s;
		if(rear == 1)
			root = s;
		else{
			if(s && Q[front]){
				if(rear%2 == 0)
					//rear为偶数，新结点是左孩子
					Q[front]->lchild = s;
				else
					//rear为奇数，新结点是右孩子
					Q[front]->rchild = s;
			}
			if(rear%2 == 1)
				//结点*Q[front]的两个孩子处理完毕，出队
				front++;
		}
	}
	return root;
}

//递归先序遍历二叉树
int PreOrderTraverse(BiTree T){
	if(T==NULL){
    	return 0;
	}
	else{
		print(T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild); 
    }
    return OK;
}

//递归中序遍历二叉树
int InOrderTraverse(BiTree T){

    if(T == NULL){
        return ERROR;
    }
    else{
        InOrderTraverse(T->lchild);
        print(T->data);
        InOrderTraverse(T->rchild);
    }
    return OK;
}
//递归后序遍历二叉树
int PostOrderTraverse(BiTree T){

    if(T == NULL){
        return 0;
    }
    else{
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        print(T->data);
    }
    return OK;
}

//非递归先序遍历二叉树
int NoRePreOrderTraverse(BiTree T){

    BiTree p;
    sqStack S;
    InitStack(&S);
    p = T;
    while(p != NULL || StackEmpty(S) == 1){
        while(p != NULL){
            print(p->data);
            Push(&S, p);
            p = p->lchild;
        }
        if(StackEmpty(S) == 1){
            Pop(&S, &p);
            p = p->rchild;
        }
    }

    return OK;
}

//非递归中序遍历二叉树
int NoReInOrderTraverse(BiTree T){

    BiTree p;
    sqStack S;
    InitStack(&S);
    Push(&S, T);
    while(StackEmpty(S) == 1){
       while(GetTop(&S, &p) && p) {
            Push(&S, p->lchild);
        }
      
       Pop(&S, &p);
        if(StackEmpty(S) == 1){
            Pop(&S, &p);
            print(p->data);
            Push(&S, p->rchild);
        }
    }
    return OK;
}

//非递归后序遍历二叉树
int NoRePostOrderTraverse(BiTree T){
{
  sqStack S;
    InitStack(&S);
    BiTree p = T;
    BiTree r;
    while (p || StackEmpty(S)==1)
    {
        if (p){
            Push(&S, p);
            p = p->lchild;
        } else{
           GetTop(&S, &p);
            if (p->rchild && p->rchild!=r)  // 右子树存在，且未被访问过
                p = p->rchild;
            else{
                Pop(&S,&p );
                print(p->data);
                r = p;
                p = NULL;    // 重制p指针
            }
        }
    }
}
}

//递归求二叉树的高度
int TreeHigh(BiTree T){
    int High = 0 ;
    if(T){
        int lchildhigh=TreeHigh(T->lchild);
        int rchildhigh=TreeHigh(T->rchild);
        High=(lchildhigh>=rchildhigh) ? lchildhigh+1 : rchildhigh+1;
    }
    return High;
}

//递归求叶子节点个数 
int LeafCount(BiTree T){
	int Count = 0;
	if(T==NULL){
		return 0;
	}
	if(T->lchild==NULL && T->rchild == NULL)
		return 1;
	else
		Count=LeafCount(T->lchild) + LeafCount(T->rchild); 
		return Count;
}

//非递归求二叉树的高度
int NoReTreehigh(BiTree T){
       	int high = 0;

    	sqStack S, Tag;
    	InitStack(&S);
    	InitStack(&Tag);
    	BiTree q, p;
   		 p = T;
    	while(p != NULL || StackEmpty(S) == 1){
        	while(p != NULL){
            	Push(&S, p);
            	Push(&Tag, NULL);
           		 p = p->lchild;
        	}
        	GetTop(&Tag, &q);
        	if(q != NULL){
           	 	high = high>StackLength(S)?high:StackLength(S);
            	Pop(&S, &p);
            	Pop(&Tag, &p);
            	p = NULL;
        	}
       		 else{
           		GetTop(&S,&p);
           		p = p->rchild;
            	Pop(&Tag, &q);
            	Push(&Tag, T);
        	}
    	}

    	return high;
	}

// 非递归求二叉树的叶子节点个数
int NoReLeafCount(BiTree T){

    int Count = 0;
    BiTree p;
    sqStack S;
    InitStack(&S);
    Push(&S,T);
    while(StackEmpty(S) == 1){
		while(GetTop(&S, &p) && p){
            Push(&S, p->lchild);
        }
        Pop(&S, &p);
        if(StackEmpty(S) == 1){
            Pop(&S, &p);
            if(p->lchild == NULL && p->rchild == NULL){
                Count++;
            }
            Push(&S, p->rchild);
        }
    }
    return Count;
}

int main()
{
    BiTree T = NULL;

//	printf("层次遍历方式输入\n");
//	printf("空节点请用/表示 如ABCD///\n");
//	T=CreateBiTree1(); 
 
	printf("先序遍历方式输入\n");
	printf("空节点请用/表示 如ABD//E//CFG/H////\n");
 	CreateBiTree(&T);
    
    printf("-----李永燊的递归算法结果-----\n");
    printf("递归先序遍历二叉树结果：\n");
	PreOrderTraverse(T);
    printf("\n");
    printf("递归中序遍历二叉树结果：\n");
    InOrderTraverse(T);
    printf("\n");
    printf("递归后序遍历二叉树结果：\n");
    PostOrderTraverse(T);    
    printf("\n");   
	printf("层次遍历二叉树结果：\n");
    NLevelOrderTraverse(T);
    printf("\n"); 
    printf("递归求二叉树的高度：%d\n", TreeHigh(T));
    printf("递归求二叉树的叶子节点个数：%d\n", LeafCount(T));
    printf("\n");
    
	printf("-----吴凯进的非递归算法结果-----\n");
    printf("非递归的先序遍历结果是：\n");
    NoRePreOrderTraverse(T);
    printf("\n");
    printf("非递归的中序遍历结果为：\n");
    NoReInOrderTraverse(T);
    printf("\n");
    printf("非递归的后序遍历结果为：\n");
    NoRePostOrderTraverse(T);
    printf("\n");
    printf("层次遍历二叉树的结果：\n");
    NLevelOrderTraverse(T);
    printf("\n");
    printf("非递归求二叉树的高度：%d\n", NoReTreehigh(T));
    printf("非递归求二叉树的叶子节点个数：%d\n", NoReLeafCount(T));
    
    return 0;
}
