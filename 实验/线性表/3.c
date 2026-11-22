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
void CreateLinkList(LinkList L,int count){
    char B_id[50];
    char B_name[50];
    double B_price;
    LNode* rear=L;

    for(int i=0;i<count;i++){
        scanf("%s %s %lf",B_id,B_name,&B_price);
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
    }
}

//去重
int UniqueLinkList(LinkList L){
    if (L == NULL || L->next == NULL ) return 0;

    int count=0;
    LNode* p=L->next;
    while(p!=NULL){
        count++;
        LNode* d=p->next;
        LNode* pre_d=p;
        while(d!=NULL){
            if(strcmp(p->data.id, d->data.id) == 0){
                LNode* temp=d;
                pre_d->next=d->next;
                d=d->next;
                free(temp);

            }else{
                pre_d=d;
                d=d->next;
            }
        }
        p=p->next;
    }
    return count;
}



//打印链表中的内容
void ShowUp(LinkList L,int count){
    LNode* p=L->next;
    if(p==NULL){
        printf("当前不包含任何图书信息 请先添加~");
        return;
    }
    printf("%d\n",count);
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
    *L=NULL;
}

int main(){
    LinkList L=NULL;
    InitLinkList(&L);
    int count;
    scanf("%d",&count);
    CreateLinkList(L,count);
    int new_count=UniqueLinkList(L);

    ShowUp(L,new_count);
    DestroyLinkList(&L);
    return 0;
}