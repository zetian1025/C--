#include <iostream>
using namespace std;

typedef int Elementtype;

struct BiTree
{
    BiTree* lchild;
    BiTree* rchild;
    Elementtype data;
};

void visit(BiTree* T){  
    cout<<T->data<<endl;
}

void Threading(BiTree* T){
    if(!T)  //若节点为空，直接返回空
    {
        return;
    }
    visit(T);   //先访问该节点
    Threading(T->lchild);   //访问左孩子
    visit(T);   //再次访问该节点
    Threading(T->rchild);   //访问右孩子
    return;
}
