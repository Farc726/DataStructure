#include<iostream>
#include<queue>
using namespace std;
//正无穷
#define INF 0x3f3f3f3f
//最大节点数
#define MAXV 100

//定义顶点与边权值的类型（易读且易更换）
typedef char VerTexType;
typedef int AtcType;

//定义邻接矩阵结构体
typedef struct{
    //顶点数
    int vexnum;
    //边数
    int arcnum;
    //顶点数组
    VerTexType vexs[MAXV];
    //边二维数组
    AtcType arcs[MAXV][MAXV];
    //遍历标志
    bool visited[MAXV];
}AMGraph;

int LocatIndex(AMGraph G,VerTexType v){
    for(int i=0;i<G.vexnum;i++){
        if(G.vexs[i]==v) return i;
    }
    return -1;
}

//创建邻接矩阵--创建这个图
bool CreateGraph(AMGraph &G){
    G.vexnum=8;
    G.arcnum=8;
    //给各个顶点赋值
    G.vexs[0]='A';
    G.vexs[1]='B';
    G.vexs[2]='C';
    G.vexs[3]='D';
    G.vexs[4]='E';
    G.vexs[5]='F';
    G.vexs[6]='G';
    G.vexs[7]='H';


    //矩阵初始化 边的权值初始化为INF，visited初始化为false
    for(int i=0;i<G.vexnum;i++){
        for(int j=0;j<G.vexnum;j++){
            G.arcs[i][j]=INF;
        }
        G.visited[i]=false;
    }
    //这里没有用到定位函数
    //先自己画出矩阵后置予权值
    G.arcs[0][4]=G.arcs[4][0]=1;
    G.arcs[5][4]=G.arcs[4][5]=1;
    G.arcs[1][4]=G.arcs[4][1]=1;
    G.arcs[2][5]=G.arcs[5][2]=1;
    G.arcs[1][2]=G.arcs[2][1]=1;
    G.arcs[3][2]=G.arcs[2][3]=1;
    G.arcs[1][3]=G.arcs[3][1]=1;
    G.arcs[6][7]=G.arcs[7][6]=1;

    
    return true;
}

//打印邻接矩阵看一下
void Print(AMGraph G){
    for(int i=0;i<G.vexnum;i++){
        for(int j=0;j<G.vexnum;j++){
            if(j!=G.vexnum-1){
                if(G.arcs[i][j]!=INF){
                    cout<<G.arcs[i][j]<<"\t";
                }else{
                    cout<<"INF"<<"\t";
                }
            }else{
                if(G.arcs[i][j]!=INF){
                    cout<<G.arcs[i][j]<<endl;
                }else{
                    cout<<"INF"<<endl;
                }
            }
        }
    }
}
//接下来先写连通图的BFS邻接矩阵版
//参数为  1.遍历哪个图  2.从这个图的哪个节点开始遍历
void BFS(AMGraph &G,int v){
    //广度优先遍历需要借助一个队列（参考树的广度优先遍历）
    queue<int> q;
    //先将开始节点的下标入队
    q.push(v);
    G.visited[v]=true;
    cout<<G.vexs[v]<<" ";
    while(!q.empty()){
        //如果不是空的就取出队首节点
        int cur=q.front();
        q.pop();
        for(int i=0;i<G.vexnum;i++){
            if(G.arcs[cur][i]!=INF&&G.visited[i]==false){
                cout<<G.vexs[i]<<" ";
                q.push(i);
                G.visited[i]=true;
            }
        }
    }

}

//若可能为非连通图
void BFSG(AMGraph &G,int v){
    BFS(G,v);
    for(int i=0;i<G.vexnum;i++){
        if(G.visited[i]==false){
            BFS(G,i);
        }
    }
}
int main(){
    AMGraph G;
    CreateGraph(G);
    Print(G);
    BFSG(G,4);
    return 0;
}