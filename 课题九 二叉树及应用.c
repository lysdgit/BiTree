//�ھ��� ��������Ӧ��
#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10
#define OK      1
#define ERROR   0 
typedef char ElemType;

//���ڵ�
typedef struct BiTNode{
    ElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//ջ
typedef struct{
    BiTree *base;
    BiTree *top;
    int stacksize;
}sqStack;

//���ṹ
typedef struct QNode{
    BiTree data;
    struct QNode * next;
}QNode, *QueuePtr;

//���нṹ
typedef struct{
    QueuePtr front;         //��ͷָ��
    QueuePtr rear;          //��βָ��
}LinkQueue;

//��ʼ������ 
int InitQueue(LinkQueue *Q){

    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
    if(!Q->front)
        return ERROR;
    Q->front->next = NULL;
    //printf("���г�ʼ���ɹ���\n");
    return OK;
}

//����
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

//ɾ����ͷ
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
    //printf("ɾ����ͷ�ɹ���\n");
    return OK;
}

//�����п� 
int QueueEmpty(LinkQueue *Q){
    if(Q->front == Q->rear){
        //printf("����Ϊ��\n");
        return ERROR;
    }
    //printf("���в�Ϊ��\n");
    return OK;
}

//��ʼ��ջ 
int InitStack(sqStack *S){
    S->base = (BiTree * )malloc(STACK_INIT_SIZE * sizeof(BiTree));
    if(!S->base){
        exit(0);
    }
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;

}

//��ջ
int Push(sqStack *S, BiTree e)
{
    if(S->top - S->base >= S->stacksize)           //ջ���� ׷�ӿռ�
    {
        S->base = (BiTree *)realloc(S->base, (S->stacksize + STACKINCREMENT)* sizeof(BiTree));
        if(!S->base){
            exit(0);                 //����ʧ��
        }
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }

    *(S->top) = e;
    S->top++;
    return OK;
}

//��ջ
int Pop(sqStack *S, BiTree *e){
    if(S->top == S->base){
        return ERROR;                  //�п�
    }
    *e = * --(S->top);
    return OK;
}

//ջ�п� 
int StackEmpty(sqStack S){
    if(S.top - S.base == 0){
        //printf("StackEmpty()��ǰջΪ�գ�\n");
        return ERROR;
    }
    return OK;
}

//ȡջ��Ԫ�� 
int GetTop(sqStack *S, BiTree *e){
    if(S->top == S->base){
        return ERROR;
    }
    *e = *(S->top-1);
    return OK;

}

//��ȡջ�ĳ��� 
int StackLength(sqStack s){
    return (s.top - s.base);
}

//����ջ 
int DestroyStack(sqStack *S){
    free(S);
    return OK;
}

//���¶���������� 
void print(ElemType e){
    printf("%c  ", e);
}

//��α���������
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

//���򴴽���
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

//��δ����� 
BiTNode *que[1000];
int s[1000],ss = 0;
int front = 0, rear = 0;
int num ;

BiTNode *CreateBiTree1(){
	char ch;			 //�����Ϣ����
	BiTNode *Q[100];	//����ָ���������������ɶ���
	int front, rear;	//��ͷ�Ͷ�βָ�����
	BiTNode *root, *s;	//���ڵ�ָ����м�ָ�����
	root = NULL;	    //�������ÿ�
	front = 1, rear = 0;	//���ö���ָ�������ֵ
	while((ch=getchar()) != '/'){
		//����һ���ַ��������ǽ�����ʱִ�����²���
		s = NULL;
		if(ch != '/'){
			s = (BiTNode*)malloc(sizeof(BiTNode));
			s->data = ch;
			s->lchild = NULL;
			s->rchild = NULL;
		}
		rear++;	//��βָ����1��ָ���½���ַ��ŵĵ�Ԫ
		Q[rear] = s;
		if(rear == 1)
			root = s;
		else{
			if(s && Q[front]){
				if(rear%2 == 0)
					//rearΪż�����½��������
					Q[front]->lchild = s;
				else
					//rearΪ�������½�����Һ���
					Q[front]->rchild = s;
			}
			if(rear%2 == 1)
				//���*Q[front]���������Ӵ�����ϣ�����
				front++;
		}
	}
	return root;
}

//�ݹ��������������
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

//�ݹ��������������
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
//�ݹ�������������
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

//�ǵݹ��������������
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

//�ǵݹ��������������
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

//�ǵݹ�������������
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
            if (p->rchild && p->rchild!=r)  // ���������ڣ���δ�����ʹ�
                p = p->rchild;
            else{
                Pop(&S,&p );
                print(p->data);
                r = p;
                p = NULL;    // ����pָ��
            }
        }
    }
}
}

//�ݹ���������ĸ߶�
int TreeHigh(BiTree T){
    int High = 0 ;
    if(T){
        int lchildhigh=TreeHigh(T->lchild);
        int rchildhigh=TreeHigh(T->rchild);
        High=(lchildhigh>=rchildhigh) ? lchildhigh+1 : rchildhigh+1;
    }
    return High;
}

//�ݹ���Ҷ�ӽڵ���� 
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

//�ǵݹ���������ĸ߶�
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

// �ǵݹ����������Ҷ�ӽڵ����
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

//	printf("��α�����ʽ����\n");
//	printf("�սڵ�����/��ʾ ��ABCD///\n");
//	T=CreateBiTree1(); 
 
	printf("���������ʽ����\n");
	printf("�սڵ�����/��ʾ ��ABD//E//CFG/H////\n");
 	CreateBiTree(&T);
    
    printf("-----�������ĵݹ��㷨���-----\n");
    printf("�ݹ�������������������\n");
	PreOrderTraverse(T);
    printf("\n");
    printf("�ݹ�������������������\n");
    InOrderTraverse(T);
    printf("\n");
    printf("�ݹ������������������\n");
    PostOrderTraverse(T);    
    printf("\n");   
	printf("��α��������������\n");
    NLevelOrderTraverse(T);
    printf("\n"); 
    printf("�ݹ���������ĸ߶ȣ�%d\n", TreeHigh(T));
    printf("�ݹ����������Ҷ�ӽڵ������%d\n", LeafCount(T));
    printf("\n");
    
	printf("-----�⿭���ķǵݹ��㷨���-----\n");
    printf("�ǵݹ�������������ǣ�\n");
    NoRePreOrderTraverse(T);
    printf("\n");
    printf("�ǵݹ������������Ϊ��\n");
    NoReInOrderTraverse(T);
    printf("\n");
    printf("�ǵݹ�ĺ���������Ϊ��\n");
    NoRePostOrderTraverse(T);
    printf("\n");
    printf("��α����������Ľ����\n");
    NLevelOrderTraverse(T);
    printf("\n");
    printf("�ǵݹ���������ĸ߶ȣ�%d\n", NoReTreehigh(T));
    printf("�ǵݹ����������Ҷ�ӽڵ������%d\n", NoReLeafCount(T));
    
    return 0;
}
