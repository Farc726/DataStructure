#include<iostream>
#include<cstring>
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
}AMGraph;

int LocatIndex(AMGraph G,VerTexType v){
    for(int i=0;i<G.vexnum;i++){
        if(G.vexs[i]==v) return i;
    }
    return -1;
}

//创建邻接矩阵--创建这个图
bool CreateGraph(AMGraph &G){

    //G.vexnum=6;
    //G.arcnum=7;

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

void DFS(const AMGraph &G,int v,bool visited[]){
    cout<<G.vexs[v]<<" ";
    visited[v]=true;
    for(int i=0;i<G.vexnum;i++){
        if(G.arcs[v][i]!=INF&&visited[i]==false){
            DFS(G,i,visited);
        }
    }
}

void DFSG(const AMGraph &G,int v){
    bool visited[MAXV];
    memset(visited,false,sizeof(visited));
    if(v>=0&&v<G.vexnum&&visited[v]==false){
        DFS(G,v,visited);
    }
    for(int i=0;i<G.vexnum;i++){
        if(visited[i]==false){
            DFS(G,i,visited);
        }
    }
}

int main(){
    AMGraph G;
    CreateGraph(G);
    Print(G);

    DFSG(G,4);
    return 0;
}