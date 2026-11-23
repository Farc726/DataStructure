#include<iostream>
#include<queue>
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
    G.vecnum=8;
    G.arcnum=8;
    G.Vecs[0].data='A';
    G.Vecs[1].data='B';
    G.Vecs[2].data='C';
    G.Vecs[3].data='D';
    G.Vecs[4].data='E';
    G.Vecs[5].data='F';
    G.Vecs[6].data='G';
    G.Vecs[7].data='H';

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
    int g=LocateVecIndex(G,'G');
    int h=LocateVecIndex(G,'H');
    

    CreateArc(G,a,e);
    CreateArc(G,e,b);
    CreateArc(G,b,d);
    CreateArc(G,d,c);
    CreateArc(G,f,c);
    CreateArc(G,f,e);
    CreateArc(G,b,c);
    CreateArc(G,g,h);
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

void BFS(const ALGraph &G,int v,bool visited[]){
    //因为是BFS我们需要借助队列辅助实现
    queue<int> qu;
    //首先把第一个元素下标压入队列
    //注意！！ 压入队列的时候就是访问这个元素的时刻
    //而这个元素出队则代表着遍历这个跟元素有边相连的元素！！
    qu.push(v);
    visited[v]=true;
    cout<<G.Vecs[v].data<<" ";
    while(!qu.empty()){
        //弹出队首元素目的是遍历与这个元素相联的元素
        int cur=qu.front();
        qu.pop();
        ArcNode* p=G.Vecs[cur].firstarc;
        while(p!=NULL){
            //也是一样的逻辑入队代表访问（两者紧跟）
            if(visited[p->adjvex]==false){
                qu.push(p->adjvex);
                visited[p->adjvex]=true;
                cout<<G.Vecs[p->adjvex].data<<" ";
                
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
int main(){
    ALGraph G;
    CreateGraph(G);
    Print(G);
    BFSG(G,4);

    return 0;
}
