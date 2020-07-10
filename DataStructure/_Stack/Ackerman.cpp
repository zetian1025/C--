int akm(int m, int n)
{
  if (m == 0)
  {
    return n + 1;
  }
  else if (n == 0)
  {
    return akm(m - 1, 1);
  }
  else
  {
    return akm(m - 1, akm(m, n - 1));
  }
}

#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef struct
{
  int *base;
  int *top;
  int stacksize;
} Stack;

void InitStack(Stack &S)
{
  S.base = (int *)malloc(STACK_INIT_SIZE * sizeof(int));
  if (!S.base)
    exit(-1);
  S.top = S.base;
  S.stacksize = STACK_INIT_SIZE;
  return;
}
int GetTop(Stack S)
{
  if (S.top == S.base)
    return NULL;
  return *(S.top - 1);
}

int isEmpty(Stack S)
{
  if (S.top == S.base)
    return 1;
  else
    return 0;
}
void push(Stack &S, int e)
{
  if (S.top - S.base >= S.stacksize)
  {
    S.base =
        (int *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(int));
    if (!S.base)
      exit(-1);
    S.top = S.base + S.stacksize;
    S.stacksize += STACKINCREMENT;
  }
  *S.top++ = e;
  return;
}
int pop(Stack &S) { return *--S.top; }

int akm(int m, int n)
{
  Stack mStack, nStack;   //构造两个栈
  InitStack(mStack);    //用于存放Ackerman函数的两个参数
  InitStack(nStack);
  push(mStack, m);  //把初始的mn分别压入对应的栈中
  push(nStack, n);

  while (!isEmpty(mStack))  //出口条件：m栈为空栈
  {
    if (GetTop(mStack) == 0)  //先看m栈：若栈顶元素为0
    {
      pop(mStack);    //akm(m,n) = n+1
      int N = pop(nStack);  //取出m，n，放入n+1（n栈）
      push(nStack, N + 1);
    }
    else if (GetTop(nStack) == 0) //在m栈栈顶元素不为0的情况下，看n栈栈顶元素
    {
      int M = pop(mStack);  //akm(m,n) = akm(m-1,1)
      pop(nStack);    //取出m，n，放入m-1（m栈），1（n栈）
      push(mStack, M - 1);
      push(nStack, 1);
    }
    else  //若mn都不为0
    {
      int M = pop(mStack);  //akm(m,n) = akm(m-1,akm(m,n-1))
      int N = pop(nStack);  //取出m，n，放入m-1，m（m栈），n-1（n栈）
      push(mStack, M - 1);
      push(mStack, M);
      push(nStack, N - 1);
    }
  }

  return pop(nStack); //此时n栈中的唯一元素必为结果
}