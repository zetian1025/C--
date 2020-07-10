#include <stdio.h>
#include <string.h>

// 以字符串的形式表示数字
typedef struct nString{
   char strNum[1002];
   int length;
}nString;
// 也可自行决定存储结构

nString arr[1002];

// 比较两个字符串，可自定义参数或自定义函数
int cmpStr(nString fir,nString sec){
    if (fir.length != sec.length){  //首先判断长度是否相等。
        return fir.length>sec.length?1:-1;  //长度较长的数较大
    }
    else{   //否则，从最高位开始比较。
        for (int i=0; i<fir.length; i++){ 
            if (fir.strNum[i] != sec.strNum[i]){
                return fir.strNum[i]>sec.strNum[i]?1:-1;
            }
        }
    }
    return 0;
}

void QSort(int begin, int end){
    if (begin >= end){  //若只有一个元素，直接返回
        return;
    }
    int i = begin;
    int j = end;
    nString key = arr[begin];
    while (i < j){
        while (i<j && cmpStr(arr[j],key)!=-1){ //从最后一个元素开始，向前找小于key的元素
            j--;
        }
        arr[i] = arr[j];    //将它放在数组开始处
        while (i<j && cmpStr(arr[i],key)!=1){ //从第一个元素开始，向前找大于key的元素
            i++;
        }
        arr[j] = arr[i];    //将它放在原数组j处
    }
    arr[i] = key;   //因为key值原来位置的值发生了改变，重新放置key
    QSort(begin,i-1);
    QSort(i+1,end);
}

int main(void){
   int num;
   int caseNum = 0;
   
   // 文件输入方式
   freopen("5_2_input.in", "r", stdin);
   while(scanf("%d",&num)!=EOF){
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < num; i++){
           scanf("%s",arr[i].strNum);
           arr[i].length = strlen(arr[i].strNum);
       }
       QSort(0,num-1);
       for(int i = 0; i < num; i++){
           printf("%s\n",arr[i].strNum);
       }
   }
   fclose(stdin);

    /* 终端输入方式
   while(scanf("%d",&num)!=EOF){
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < num; i++){
           scanf("%s",arr[i].strNum);
           arr[i].length = strlen(arr[i].strNum);
       }
       resort(arr, num);
       for(int i = 0; i < num; i++){
           printf("%s\n",arr[i].strNum);
       }
   }
   */
}


