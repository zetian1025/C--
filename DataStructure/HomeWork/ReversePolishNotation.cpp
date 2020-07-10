#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef struct {
  char *base;
  char *top;
  int stacksize;
} Stack;

void InitStack(Stack &S) {
  S.base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));
  if (!S.base) exit(-1);
  S.top = S.base;
  S.stacksize = STACK_INIT_SIZE;
  return;
}
char GetTop(Stack S) {
  if (S.top == S.base) return NULL;
  return *(S.top - 1);
}

int isEmpty(Stack S) {
  if (S.top == S.base)
    return 1;
  else
    return 0;
}
void push(Stack &S, char e) {
  if (S.top - S.base >= S.stacksize) {
    S.base =
        (char *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(char));
    if (!S.base) exit(-1);
    S.top = S.base + S.stacksize;
    S.stacksize += STACKINCREMENT;
  }
  *S.top++ = e;
  return;
}
char pop(Stack &S) { return *--S.top; }

int prior(char a, char b) {
  if ((a == '*' || a == '/') && (b == '+' || b == '-'))
    return 1;
  else
    return 0;
}

void Reverse_Polish_notation(char notation[]) {
  Stack operation;
  InitStack(operation);        //构造空栈operation，用于存放运算符
  int len = strlen(notation);  //设置表达式总长度为len
  for (int i = 0; i < len; i++) {  //对表达式数组进行遍历
    if (notation[i] >= 'A' && notation[i] <= 'z') {  //若为字母，直接输出。
      printf("%c", notation[i]);
    } else if (isEmpty(operation)) {  //若此时栈中没有运算符，放入第一个运算符。
      push(operation, notation[i]);
    } else {  //否则，比较待入栈的运算符与此时栈顶运算符的优先级。
      if (prior(GetTop(operation),
                notation[i])) {  //若栈顶运算符优先级高于待入栈运算符
        while (!isEmpty(operation)) {  //在栈不为空的情况下,取出栈顶元素并输出
          char ch = pop(operation);
          printf("%c", ch);
          if (!prior(GetTop(operation), notation[i]))
            break;  //直到栈顶的优先级低于（或等于）待入栈运算符
        }
        push(operation, notation[i]);  //运算符入栈
      } else {
        push(operation,
             notation[i]);  //若栈顶的优先级低于（或等于）待入栈运算符，直接入栈
      }
    }
  }
  while (!isEmpty(operation)) {  //栈中剩余元素依次出栈
    char ch = pop(operation);
    printf("%c", ch);
  }
  return;
}