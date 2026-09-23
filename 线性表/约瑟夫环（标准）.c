#include<stdio.h>
#include<stdlib.h>

typedef struct LNode{
    int data;
    struct LNode *next;
}LNode,*LinkList;

//建立没有头结点的单向循环链表
void CreateList(LinkList *head,int n){
    if(n<1) return;
    *head=NULL;
    LNode *tail=NULL;
    for(int i=1;i<=n;i++){
        LNode *s=(LNode*)malloc(sizeof(LNode));
        s->data=i;
        s->next=NULL;

        if(*head==NULL){
            *head=s;
            tail=s;
        }else{
        tail->next=s;
        tail=s;
        }
    }
    tail->next=*head;
}

void Josephus(int n, int m){
    LinkList head;
    CreateList(&head,n);
    if(head==NULL) return;
    LNode* pre=head;
    LNode* cur=NULL;

    while(pre->next!=head){
        pre=pre->next;
    }
    cur=pre->next;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<m-1;j++){
            pre=pre->next;
        }
        cur=pre->next;
        printf("%d ",cur->data);
        pre->next=cur->next;
        free(cur);
        cur=pre->next;
    }
    printf("%d",cur->data);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    Josephus(n,m);
    return 0;
}