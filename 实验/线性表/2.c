#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//图书信息结构体
typedef struct Book{
    char id[50];
    char name[50];
    double price;
}Book;

//节点
typedef struct LNode
{
    Book data;
    struct LNode* next;
}LNode,*LinkList;

//初始化链表
void InitLinkList(LinkList* L){
    (*L)=(LNode*)malloc(sizeof(LNode));
    if((*L)==NULL){
        printf("初始化失败...,请重试");
        return;
    }
    (*L)->next=NULL;
}

//尾插法建立链表
int CreateLinkList(LinkList L){
    char B_id[50];
    char B_name[50];
    double B_price;
    int count=0;
    LNode* rear=L;

    while(scanf("%s %s %lf",B_id,B_name,&B_price)==3){
        if(strcmp(B_id,"0")==0&&strcmp(B_name,"0")==0&&B_price==0.0){
            break;
        }
        LNode* node=(LNode*)malloc(sizeof(LNode));
        //判空保护
        if(node==NULL){
            printf("内存分配失败，请重试~\n");
            break;
        }
        strcpy(node->data.id,B_id);
        strcpy(node->data.name,B_name);
        node->data.price=B_price;

        node->next=rear->next;
        rear->next=node;
        rear=node;

        count++;
    }
    return count;
}

//交换Book图书信息的函数(因为c语言是值传递 所以此处我们用指针 才可以达到交换的目的)
void SwapBook(Book *a,Book *b){
    Book temp=*a;
    *a=*b;
    *b=temp;
}

//按照价格降序对链表进行排序
// 优化冒泡排序算法
void OrderByPrice(LinkList L,int count){
    if (L == NULL || L->next == NULL || count <= 1) return;
    for(int i=0;i<count-1;i++){
        int swapped = 0;
        LNode* p=L->next;
        for(int j=0;j<count-i-1;j++){
            if (p->data.price < p->next->data.price) {
                SwapBook(&p->data, &p->next->data);
                swapped = 1;
            }
            p=p->next;
        }
       if (!swapped) break;
    }
} 
//打印链表中的内容
void ShowUp(LinkList L){
    LNode* p=L->next;
    if(p==NULL){
        printf("当前不包含任何图书信息 请先添加~");
        return;
    }
    while(p!=NULL){
       printf("%s %s %.2f\n",p->data.id,p->data.name,p->data.price);
        p=p->next; 
    }
}

//销毁链表 释放内存空间
void DestroyLinkList(LinkList *L){
    if(L==NULL||*L==NULL) return;

    LNode* p=(*L);
    while(p!=NULL){
        LNode* temp=p->next;
        free(p);
        p=temp;
    }
}

int main(){
    LinkList L=NULL;
    InitLinkList(&L);
    int count=CreateLinkList(L);
    OrderByPrice(L,count);
    ShowUp(L);
    DestroyLinkList(&L);
    return 0;
}

