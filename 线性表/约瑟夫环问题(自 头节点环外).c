#include<stdio.h>
#include<stdlib.h>

typedef struct LNode{
    int data;
    struct LNode *next;
}LNode,*LinkList;

//建立循环链表
void CreateLink(LinkList*L,int n){
    *L=(LNode*)malloc(sizeof(LNode));
    LinkList s;
    LinkList r=(*L);
    for(int i=1;i<=n;i++){
        s=(LNode*)malloc(sizeof(LNode));
        s->data=i;
        r->next=s;
        s->next=NULL;
        r=s;
    }
    s->next=(*L)->next;
}

void Josephus(int n,int m){
    LinkList L=NULL;
    CreateLink(&L,n);
    if(L==NULL) return;
//要从第一个元素开始遍历
    LinkList p=L;
    for(int i=1;i<=n-1;i++){
        for(int j=0;j<m-1;j++){
            p=p->next;
        }
        LinkList d=p->next;
        p->next=d->next;
        int d_data=d->data;
        printf("%d ",d_data);
        free(d);
    }
    printf("%d",p->next->data);
    free(L);
}

int main(){
    int n,m;
    scanf("%d %d",&n,&m);

    Josephus(n,m);
    return 0;
}