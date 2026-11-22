#include<iostream>
using namespace std;

#define MaxInt 32767
#define MVNum 100

//首先 规定顶点类型以及边的权重类型
//方便统一修改
typedef char VerTexType;
typedef int ArcType;

//定义邻接矩阵结构体
typedef struct {
    VerTexType vexs[MVNum];
    ArcType arcs[MVNum][MVNum];
    int vexnum, arcnum;
    bool visited[MVNum];
} AMGraph;


//根据顶点定位顶点下标
int LocateVex(AMGraph G,VerTexType v){
    for(int i=0;i<G.vexnum;i++){
        if(G.vexs[i]==v)
        return i;
    }
    return -1;
}

//创建邻接矩阵
bool CreateGraph(AMGraph& G){
    //输入总顶点数与总边数
    cout<<"please input vexnum and arcnum:"<<endl;
    cin>>G.vexnum>>G.arcnum;
    if(G.vexnum<=0||G.arcnum<0||G.vexnum>MVNum){
        cout << "Invalid vexnum or arcnum!" << endl;
        return false;
    }

    //明确所加边的顶点 以及 权值
    VerTexType end_a,end_b;
    ArcType w;

    //首先初始化整个矩阵
    //1.顶点
    cout << "Please input " << G.vexnum << " vertices: ";
    for(int i=0;i<G.vexnum;i++){
        cin>>G.vexs[i];
    }
    //2.各个边的初始权重
    for(int i=0;i<G.vexnum;i++){
        for(int j=0;j<G.vexnum;j++){
            G.arcs[i][j]=MaxInt;
        }
    }

    //处理有权重的边
    cout << "Please input " << G.arcnum << " edges (u v weight):" << endl;
    for(int m=0;m<G.arcnum;m++){
        cin>>end_a>>end_b;
        cin>>w;
        int i=LocateVex(G,end_a);
        int j=LocateVex(G,end_b);

        if(i>=0&&j>=0){
            G.arcs[i][j]=w;
            G.arcs[j][i]=w;
        }else{
            cout<<"Vertex not found, skipped edge: " << end_a << " " << end_b << endl;
        }
            
    }
    return true;
}

//打印整个邻接矩阵
void PrintMatrix(AMGraph G){
    for(int i=0;i<G.vexnum;i++){
        for(int j=0;j<G.vexnum;j++){
            if(j!=G.vexnum-1){
                if(G.arcs[i][j]!=MaxInt){
                    cout<<G.arcs[i][j]<<"\t";
                }else{
                    cout<<"INF"<<"\t";
                }
            }else{
                if(G.arcs[i][j]!=MaxInt){
                    cout<<G.arcs[i][j]<<endl;
                }else{
                    cout<<"INF"<<endl;
                }
            }
        }
    }
}

int main(){
    AMGraph G;
    CreateGraph(G);
    PrintMatrix(G);
    return 0;
}
