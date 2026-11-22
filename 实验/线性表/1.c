#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//定义图书类
typedef struct Book{
    char id[50];
    char name[50];
    double price;
}Book;

//节点
typedef struct LNode{
    Book data;
    struct LNode* next;
}LNode,*LinkList;

//初始化链表，创建头节点
void InitList(LinkList *L){
    *L=(LNode*)malloc(sizeof(LNode));
    if(*L==NULL){
        printf("初始化失败...,请重试");
        return;
    }
    (*L)->next=NULL;
}

//尾插法建立链表
int CreatLinklist(LinkList L){
    char B_id[50];
    char B_name[50];
    double B_price;
    int count=0;
    LNode* rear=L;

    while(scanf("%s %s %lf",B_id,B_name,&B_price)==3){
        if(strcmp(B_id, "0") == 0 && strcmp(B_name, "0") == 0 && B_price == 0.0){
            break;
        }
        count++;
        LNode* node=(LNode*)malloc(sizeof(LNode));
        //判空保护
        if(node==NULL){
            printf("内存分配失败，请重试~\n");
            break;
        }
        strcpy((*node).data.id,B_id);
        strcpy((*node).data.name,B_name);
        (*node).data.price=B_price;
        
        (*node).next=rear->next;
        rear->next=node;
        rear=node;

    }

    return count;
}

//输出链表中的图书信息
void ShowUp(LinkList L,int count){
    printf("%d\n",count);
    LNode* p=L->next;
    while (p!=NULL)
    {
        printf("%s %s %.2f\n",p->data.id,p->data.name,p->data.price);
        p=p->next;
    }
}

//销毁链表
void DestroyLinkList(LinkList* L){
    //1.若L本身就为空 解引用空指针会崩溃
    //2.若该链表已经被销毁置空了，就直接return
    if(L==NULL||*L==NULL) return;

    LNode*p=(*L);
    while(p!=NULL){
        LNode* temp=p->next;
        free(p);
        p=temp;
    }
    //释放所有结点内存后，将外部头指针置为 NULL，避免成为指向已释放内存的悬空指针
    //（防止后续误用或重复 free）
    *L=NULL;
}


int main(){
    LinkList L=NULL;
    InitList(&L);

    int count=CreatLinklist(L);
    
    ShowUp(L,count);

    DestroyLinkList(&L);

    return 0;
}
