//使用链表进行学生信息管理
//学生类 包含学生的姓名 年龄 
//使用尾插法建立链表
//输出整个链表中的数据
//查询链表中的第i个并输出
//在链表的第i个位置插入数据
//删除链表中某个位置的数据
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
//定义学生结构体
typedef struct Student{
    char name[10];
    int age;
}Student;

//定义链表节点
typedef struct  LNode
{
    Student data;
    struct LNode *next;
}LNode,*Linklist;

//声明并实现实现各种方法的函数
void CreateLink_w(Linklist*L,int n);
void ShowList(Linklist L);
void Insert(Linklist*L,int i,Student m);
void DeleteList(Linklist*L,char name[]);
void DestroyList(Linklist *L);

void CreateLink_w(Linklist*L,int n){
    //初始化链表
    (*L)=(LNode*)malloc(sizeof(LNode));
    (*L)->next=NULL;
    //总是指向尾部的尾指针
    LNode*r=(*L);
    //指向临时节点的指针（临时节点用于储存新插入的元素）
    LNode *s;
    for(int i=0;i<n;i++){
        s=(LNode*)malloc(sizeof(LNode));
        printf("please input name and age of the student:");
        scanf("%s %d",s->data.name,&s->data.age);
        r->next=s;
        s->next=NULL;
        r=s;
    }
}

void ShowList(Linklist L){
    Linklist p=L->next;
    if(p==NULL){
        printf("no student");
    }
    while(p!=NULL){
        printf("name:%s  age:%d\n",p->data.name,p->data.age);
        p=p->next;
    }
}

void Insert(Linklist*L,int i,Student m){
    Linklist p=(*L);
//找到第i-1个数据节点
    /*for(int j=0;j<i;j++){
        p=p->next;
    }*/
   int j=0;
   while(p!=NULL&&j<i-1){
    p=p->next;
    j++;
   }
   if(p==NULL){
    printf("false");
    return;
   }else{
//用类似尾插的方法进行插入
    Linklist s=(LNode*) malloc(sizeof(LNode));
    s->data=m;
    s->next=p->next;
    p->next=s;
   }
}

void DeleteList(Linklist*L,char name[]){
    Linklist p=(*L);
//寻找要删除的数据节点以及他的前一个
    Linklist d;
    while(p!=NULL&&p->next!=NULL&&(strcmp(p->next->data.name,name)!=0)){
        p=p->next;
    }
    if(p==NULL||p->next==NULL){
        printf("no this student");
    }else{
        d=p->next;
        p->next=d->next;
        free(d);
    }
}

void DestroyList(Linklist *L){
    Linklist p,q;
    p=(*L);
    while(p!=NULL){
        q=p;
        p=p->next;
        free(q);
    }
    (*L)=NULL;
}

int main(){
    Linklist L;
    int n;
    printf("please input the number of students:");
    scanf("%d",&n);
    CreateLink_w(&L,n);
    ShowList(L);

    printf("please input the information of new students:");
    Student m;
    scanf("%s %d",m.name,&m.age);
    Insert(&L,2,m);
    ShowList(L);    
    char name_d[10];
    printf("please input the name of the student you will delete:");
    scanf("%s",name_d);
    DeleteList(&L,name_d);
    ShowList(L);
    return 0;
}
