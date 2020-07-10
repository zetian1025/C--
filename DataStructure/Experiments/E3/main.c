#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int FLAG = 0;  //标识是否能由后序中序建立二叉树

typedef struct Node
{
    char data;
    struct Node *lchild, *rchild;
} TreeNode, *BiTree; //定义树节点的结构体

BiTree createBiTree()//建立二叉树
{
    char data;
    BiTree bt;
    // fflush(stdin);
    scanf("%c",&data);  //读入一个字符
    if (data == '#'){   //若为'#'，则说明为空节点
        bt = NULL;
    }
    else{
        bt = (BiTree)malloc(sizeof(TreeNode));
        bt->data = data;
        bt->lchild = createBiTree();    //先序建立二叉树
        bt->rchild = createBiTree();
    }
    return bt;
}

void visit(BiTree p){
    printf("%c",p->data);
}

void preOrderTraverse(BiTree p)//函数功能：前序遍历
{
    //若该节点不为空（不是叶子节点），则前序遍历这个节点及其子树
    if (p){
        visit(p);
        preOrderTraverse(p->lchild);
        preOrderTraverse(p->rchild);
    }
}
void inOrderTraverse(BiTree p)//函数功能：中序遍历
{
    //若该节点不为空（不是叶子节点），则中序遍历这个节点及其子树
    if (p){
        inOrderTraverse(p->lchild);
        visit(p);
        inOrderTraverse(p->rchild);
    }
}
void postOrderTraverse(BiTree p)//函数功能：后序遍历
{
    //若该节点不为空（不是叶子节点），则后序遍历这个节点及其子树
    if (p){
        postOrderTraverse(p->lchild);
        postOrderTraverse(p->rchild);
        visit(p);
    }
}

BiTree PostInCreate(char post[],int s1,int e1,char in[],int s2,int e2)
{
//函数功能：根据后序与中序序列构造二叉树，并返回根节点
//参数说明：post[]为后序序列，s1,e1为后序的第一和最后一个节点下标，in[]为中序序列，s2,e2为中序的第一和最后一个节点下标。

    if (s1-e1 != s2-e2){    //若序列长度不相等，必定无法构造二叉树。
        FLAG = 1;
    }
    if (FLAG == 1){     //标志为1，直接退出（无法构造二叉树）
        return NULL;
    }

    //新建头节点，把根节点元素的值赋为后序队列的最后一个元素（即根节点的值）
    BiTree bt = (BiTree)malloc(sizeof(TreeNode));
    bt->data = post[e1];

    //记录中序第一个下标，遍历中序序列；
    //目的：找到后序序列最后一个元素在中序序列中的位置（即树根节点的值在中序序列中的位置）
    //对于中序序列：全为左子树元素（中序）->根节点->全为右子树元素（中序）
    //对于后序序列：全为左子树元素（后序）->全为右子树元素（后序）->根节点
    int i = s2;
    while (in[i]!=post[e1] && i<=e2){
        i++;
    }
    if (i>e2){  //若没找到，说明无法构造二叉树。
        FLAG = 1;
        return NULL;
    }

    //为保证递归的进行，还需要找到后序序列中左子树和右子树的分界点。
    //根据构成二叉树的必要条件，后序序列、中序序列对应子树节点的数量相等。
    int Le1 = s1+(i-s2)-1;  //根据节点数量判断左子树最后一个元素在后序序列中的位置
    int Rs1 = Le1+1;    //以此推断出右子树第一个元素在后序序列中的位置

    if (i==s2 && i==e2){    //若 ①中序元素唯一 ②该元素为此时的根节点 ->叶子节点
        bt->rchild = NULL;
        bt->lchild = NULL;
    }
    else if (i==s2){    //若根节点位于中序序列开头->左子树为空
        bt->lchild = NULL;
        bt->rchild = PostInCreate(post,Rs1,e1-1,in,i+1,e2);
    }
    else if (i==e2){    //若根节点位于中序序列末尾->右子树为空
        bt->lchild = PostInCreate(post,s1,Le1,in,s2,i-1);
        bt->rchild = NULL;
    }
    else{   //若左右子树均不为空，正常递归。
        bt->lchild = PostInCreate(post,s1,Le1,in,s2,i-1);
        bt->rchild = PostInCreate(post,Rs1,e1-1,in,i+1,e2);
    }
    return bt;
}

int countLeafSum(BiTree root)
{
    //函数功能：计算叶子节点数

    if (root == NULL){  //若节点为空，说明没有该节点。
        return 0;
    }
    if (root->lchild == NULL && root->rchild == NULL){  //若该节点存在且左右节点均为空->节点为叶子节点
        return 1;
    }
    return countLeafSum(root->lchild)+countLeafSum(root->rchild);   //若不是叶子节点，递归。
}

int countHeight(BiTree root)
{
//函数功能：计算二叉树的高度,二叉树的高度是其左子树或右子树中较高的一个子树的高度再加1
    if (root == NULL){  //若节点不存在，增加高度为0。
        return 0;
    }
    int Lh = countHeight(root->lchild); //递归求得左子树高度
    int Rh = countHeight(root->rchild); //递归求得右子树高度
    return (Lh>Rh?Lh:Rh)+1; //选择其中较高的，并高度+1
}

void getwidth(BiTree root,int *count,int counter)
{
//函数功能：得到一个二叉树每层的节点数目。
//参数说明：counter记录层数,数组count记录每一层的节点数

    if (root){  //若节点存在，正常递归即可。
        count[counter]++;   //该层宽度+1
        getwidth(root->lchild,count,counter+1); //子树为下一层。
        getwidth(root->rchild,count,counter+1);
    }
}

bool isEmpty(BiTree T){
    return T==NULL;
}

int isEquivalent(BiTree bt1,BiTree bt2)
{
   //函数功能：判断两树是否等价
    //参数说明：bt1:第一个二叉树，bt2:第二个二叉树
    int ans = 0;
    if (isEmpty(bt1) && isEmpty(bt2)){  //若节点都为空，该节点等价
        ans = 1;
    }
    else if (!isEmpty(bt1) && !isEmpty(bt2)){     //若两节点都不为空
        if (bt1->data == bt2->data){    //条件1：根节点的值相等。
            if (isEquivalent(bt1->lchild,bt2->lchild)){ //条件2：左子树等价。
                if (isEquivalent(bt1->rchild,bt2->rchild)){ //条件3：右子树等价
                    ans = 1;
                }
            }
        }
    }
    //其余情况，均为不等价。
    return ans;
}
void task1(BiTree bt){
    //任务1：实现二叉树先序、中序、后序遍历
    printf("start task (1) Create Tree in PreOrder\n");
    printf("preOrderTraverse\n");
    preOrderTraverse(bt);
    printf("\n");
    printf("inOrderTraverse\n");
    inOrderTraverse(bt);
    printf("\n");
    printf("postOrderTraverse\n");
    postOrderTraverse(bt);
    printf("\n");
}

void task2(BiTree* bt){
    //任务2：请利用PostInCreate函数根据后序与中序序列构造二叉树
    //使用函数：PostInCreate
    printf("start task (2) Input the postOrder and inOrder Sequence ,Then build the tree\n");
    char post[20];  //后序序列
    char in[20];    //中序序列
    int postlen;    //后序序列长度
    int inlen;      //中序序列长度
    printf("please input the postorder sequence\n");
    scanf("%s",post);
    printf("please input the inorder sequence\n");
    scanf("%s",in);
    
    //分别得到两个序列的长度。
    postlen = strlen(post); 
    inlen = strlen(in);
    //请完善函数
    *bt = PostInCreate(post,0,postlen-1,in,0,inlen-1);  //数组从0开始
    if (FLAG == 1){
        printf("Unable to build a binary tree.\n");
        *bt = NULL;
    }
    else {
        printf("preOrderTraverse:\n");
        preOrderTraverse(*bt);
    }
    printf("\n");
}

void task3(BiTree bt){
    //任务3：计算二叉树的叶节点个数和宽度。（注：计算宽度所需的函数是出题者所设计，若你能有更好的办法得到宽度，自己设计亦可。）
    //使用函数：countLeafSum、countHeight、getwidth
    printf("start task (3) ------------------------------\n");
    if (bt == NULL){
        printf("Tree hasn't been built.\n");
        return;
    }

    int height;     //树的高度
    int maxwidth=-1;     //树的宽度，预设为-1。（宽度：二叉树每一层节点数的最大值）
    printf("The number of leaf nodes of the tree is:\n");
    printf("%d\n",countLeafSum(bt));

    height = countHeight(bt);   //得到树的高度
    int count[height];  //数组长度为树的高度
    for (int i = 0; i < height; i++){
        count[i] = 0;   //将初始值全赋为0（空树）
    }
    getwidth(bt,count,0);
    maxwidth = count[0];
    for (int i = 0;i < height;i++){ //遍历宽度数组，得到其中最大的一个元素
        maxwidth = maxwidth<count[i]?count[i]:maxwidth;
    }