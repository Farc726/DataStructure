#include<stdio.h>
#include<stdlib.h>


typedef struct LNode
{
    int data;
    struct LNode *next;
}LNode,*LinkList;

//函数声明
void CreateList(LinkList*head);
void MergeList();
void ShowLink(LinkList head);

//利用尾插法建立链表
void CreateList(LinkList*head){
    *head=(LNode*)malloc(sizeof(LNode));
    if(*head==NULL) return;

    int n;
    scanf("%d",&n);
    LNode*r=*head;
    while(n!=-1){
        LNode *s=(LNode*)malloc(sizeof(LNode));
        s->data=n;
        s->next=NULL;
        r->next=s;
        r=s;
        scanf("%d",&n);
    }
}
void ShowLink(LinkList head){
    if(head==NULL) return;
    LNode* p=head->next;
    int is_first=1;
    while(p!=NULL){
        if(is_first){
            printf("%d",p->data);
            is_first=0;
        }else{
            printf(" %d",p->data);
        }
        p=p->next;
    }
}

void MergeList(){
//建立两个链表
    LinkList s1=NULL,s2=NULL;
    CreateList(&s1);
    CreateList(&s2);

//进行链表的合并
    LNode* p=s1->next;
    LNode* q=s2->next;
    LinkList s3=(LNode*)malloc(sizeof(LNode));
    if(s3==NULL) return;
    LNode* r3=s3;
    while(p!=NULL&&q!=NULL){
        if(p->data<q->data){
            r3->next=p;
            r3=p;
            p=p->next;
        }else{
            r3->next=q;
            r3=q;
            q=q->next;
        }
    }
    if(p==NULL){
        r3->next=q;
    }else{
        r3->next=p;
    }
    ShowLink(s3);
}

int main(){
MergeList();
    return 0;
}