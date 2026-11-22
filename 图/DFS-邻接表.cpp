#include<iostream>
#include<cstring>
#define MAXV 100
using namespace std;

//为了更明确易读且更容易修改 我们给节点中数值的类型 以及 边的权值类型 起别名
typedef char VexTexType;
typedef int ArcType;

//下面是各种结构体的定义 一层一层来
//边结构体
typedef struct ArcNode
{
    int adjvex;//边所指向的顶点的位置（下标）
    ArcType w;//该边的权值
    struct ArcNode* nextarc;//指向下一个边节点的指针
}ArcNode;

//节点结构体
typedef struct VecNode{
    VexTexType data;//节点的值
    ArcNode* firstarc;//指向该节点的第一个边的指针
}VecNode;

//图结构体
typedef struct{
    VecNode Vecs[MAXV];//一个顶点的数组
    int vecnum;//顶点个数
    int arcnum;//边个数
}ALGraph;

//查找节点在数组中的位置
int LocateVecIndex(ALGraph G,VexTexType v){
    for(int i=0;i<G.vecnum;i++){
        if(G.Vecs[i].data==v) return i;
    }
    return -1;
}



//在两节点之间添加边
void CreateArc(ALGraph &G,int i,int j){
    //对于无向图来说加一条边 要在邻接图中加入两个边结点
    ArcNode* p1=new ArcNode;
    ArcNode* p2=new ArcNode;

    //头插法建立
    p1->adjvex=j;
    p1->nextarc=G.Vecs[i].firstarc;
    G.Vecs[i].firstarc=p1;

    p2->adjvex=i;
    p2->nextarc=G.Vecs[j].firstarc;
    G.Vecs[j].firstarc=p2;
}

//创建表
bool CreateGraph(ALGraph &G){
    G.vecnum=6;
    G.arcnum=7;
    G.Vecs[0].data='A';
    G.Vecs[1].data='B';
    G.Vecs[2].data='C';
    G.Vecs[3].data='D';
    G.Vecs[4].data='E';
    G.Vecs[5].data='F';

    //先将指针置空
    for(int i=0;i<G.vecnum;i++){
        G.Vecs[i].firstarc=NULL;
    }

    int a=LocateVecIndex(G,'A');
    int b=LocateVecIndex(G,'B');
    int c=LocateVecIndex(G,'C');
    int d=LocateVecIndex(G,'D');
    int e=LocateVecIndex(G,'E');
    int f=LocateVecIndex(G,'F');

    CreateArc(G,a,e);
    CreateArc(G,e,b);
    CreateArc(G,b,d);
    CreateArc(G,d,c);
    CreateArc(G,f,c);
    CreateArc(G,f,e);
    CreateArc(G,b,c);
    return true;
}

//打印这个邻接表
void Print(ALGraph G){
    for(int i=0;i<G.vecnum;i++){
        if(G.Vecs[i].firstarc==NULL){
            cout<<G.Vecs[i].data;
        }else{
            cout<<G.Vecs[i].data;
            ArcNode* p=G.Vecs[i].firstarc;
            while(p!=NULL){
                cout<<"->";
                cout<<p->adjvex;
                p=p->nextarc;
            }
    }
    cout<<endl;
}
}

void DFS(const ALGraph &G,int v,bool visited[]){
    cout<<G.Vecs[v].data<<" ";
    visited[v]=true;
    ArcNode* p=G.Vecs[v].firstarc;
    while (p!=NULL)
    {
        int cur=p->adjvex;
        if(visited[cur]==false){
            DFS(G,cur,visited);
        }
        p=p->nextarc;
    }
}

void DFSG(const ALGraph &G,int v){
    //将visited数组独立出来 防止多次遍历的时候要重复初始化
    bool visited[MAXV];
    //初始化为false
    memset(visited,false,sizeof(visited));
    DFS(G,v,visited);
    for(int i=0;i<G.vecnum;i++){
        if(visited[i]==false){
            DFS(G,i,visited);
        }
    }
}
int main(){
    ALGraph G;
    CreateGraph(G);
    Print(G);
    DFSG(G,4);
    return 0;
}
