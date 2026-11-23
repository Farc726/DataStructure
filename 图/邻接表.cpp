#include<iostream>
#include<cstring>
#include<queue>
#define MAXV 100
using namespace std;

typedef char VexTexType;
typedef int ArcType;

typedef struct ArcNode{
    int adjvex;
    ArcType w;
    struct ArcNode* nextarc;
}ArcNode;

typedef struct VNode{
    VexTexType data;
    ArcNode* firstarc;
}VNode;

typedef struct{
    int vecnum;
    int arcnum;
    VNode vecs[MAXV];
}ALGraph;

int LocateVecIndex(ALGraph G,VexTexType v){
    for(int i=0;i<G.vecnum;i++){
        if(G.vecs[i].data==v) return i;
    }
    return -1;
}

void CreateArc(ALGraph &G,int i,int j){
    ArcNode*p1=new ArcNode;
    p1->nextarc=G.vecs[i].firstarc;
    G.vecs[i].firstarc=p1;
    p1->adjvex=j;

    ArcNode*p2=new ArcNode;
    p2->nextarc=G.vecs[j].firstarc;
    G.vecs[j].firstarc=p2;
    p2->adjvex=i;
}

bool CreateGraph(ALGraph &G){
    G.vecnum=4;
    G.arcnum=4;
    G.vecs[0].data='A';
    G.vecs[1].data='B';
    G.vecs[2].data='C';
    G.vecs[3].data='D';

    for(int i=0;i<G.vecnum;i++){
        G.vecs[i].firstarc=NULL;
    }

    int a=LocateVecIndex(G,'A');
    int b=LocateVecIndex(G,'B');
    int c=LocateVecIndex(G,'C');
    int d=LocateVecIndex(G,'D');

    CreateArc(G,a,b);
    CreateArc(G,b,c);
    CreateArc(G,c,d);
    CreateArc(G,b,d);
    return true;
}

void BFS(const ALGraph &G,int v,bool visited[]){
    //因为是BFS我们需要借助队列辅助实现
    queue<int> qu;
    //首先把第一个元素下标压入队列
    //注意！！ 压入队列的时候就是访问这个元素的时刻
    //而这个元素出队则代表着遍历这个跟元素有边相连的元素！！
    qu.push(v);
    visited[v]=true;
    cout<<G.vecs[v].data<<" ";
    while(!qu.empty()){
        //弹出队首元素目的是遍历与这个元素相联的元素
        int cur=qu.front();
        qu.pop();
        ArcNode* p=G.vecs[cur].firstarc;
        while(p!=NULL){
            //也是一样的逻辑入队代表访问（入队访问置true输出三者紧跟）
            if(visited[p->adjvex]==false){
                qu.push(p->adjvex);
                visited[p->adjvex]=true;
                cout<<G.vecs[p->adjvex].data<<" ";
                
            }
            p=p->nextarc;
        }
    }
}

void BFSG(const ALGraph &G,int v){
    //将visited数组独立出来 防止多次遍历的时候要重复初始化
    bool visited[MAXV];
    //初始化为false
    memset(visited,false,sizeof(visited));  
    
    BFS(G,v,visited);
    for(int i=0;i<G.vecnum;i++){
        if(visited[i]==false){
            BFS(G,i,visited);
        }
    }
}

void DFS(const ALGraph& G,int v,bool visited[]){
    //所谓DFS就是沿着这个节点依次向后 如果未曾访问就对其进行DFS
    cout<<G.vecs[v].data<<" ";
    visited[v]=true;
    ArcNode* p=G.vecs[v].firstarc;
    while(p!=NULL){
        if(visited[p->adjvex]==false){
            DFS(G,p->adjvex,visited);
        }
        p=p->nextarc;
    }
}
void DFSG (const ALGraph&G,int v){
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

    BFSG(G,1);
    cout<<endl;
    DFSG(G,0);
    return 0;
}