#include<iostream>
#include<string>
using namespace std;

const int MAXSIZE=100;
//定义学生类
class Student{
public:
    string id;
    string name;
    double score;

};

class Sqlist{
private:
    Student *data;
    int length;
    int listsize;
public:
    Sqlist();
    ~Sqlist();
    void InfoStudent(int n);
    void ShowStudents();
};

//用构造函数来初始化空列表
Sqlist::Sqlist(){
    data=new Student[MAXSIZE];
    length=0;
    listsize=MAXSIZE;
}
//用析构函数来释放内存
Sqlist::~Sqlist(){
    delete []data;
}
void Sqlist::InfoStudent(int n){
    if (n<1||n>MAXSIZE){
        cout<<"人数输入无意义"<<endl;
        return;
    }else{
        length=n;
        for(int i=0;i<length;i++){
            cout<<"请输入学生学号：";
            cin>>data[i].id;
            cout<<"请输入学生姓名：";
            cin>>data[i].name;
            cout<<"请输入学生成绩:";
            cin>>data[i].score;
        }
    }
}

void Sqlist::ShowStudents(){
    cout<<"学号  姓名  成绩"<<endl;
    for(int i=0;i<length;i++){
        cout<<data[i].id<<"\t"<<data[i].name<<"\t"<<data[i].score<<endl;
    }
}


int main(){
    Sqlist L;
    int n;
    cout<<"请输入学生人数：";
    cin>>n;

    L.InfoStudent(n);
    L.ShowStudents();

    return 0;
}