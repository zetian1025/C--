#include <stdio.h>
#include <stdlib.h>

#define MAX 0x3f3f3f3f

int arr[2002];

void QSort(int begin, int end){
    if (begin >= end){  //若只有一个元素，直接返回
        return;
    }
    int i = begin;
    int j = end;
    int key = arr[begin];
    while (i < j){
        while (i<j && arr[j]>=key){ //从最后一个元素开始，向前找小于key的元素
            j--;
        }
        arr[i] = arr[j];    //将它放在数组开始处
        while (i<j && arr[i]<=key){ //从第一个元素开始，向前找大于key的元素
            i++;
        }
        arr[j] = arr[i];    //将它放在原数组j处
    }
    arr[i] = key;   //因为key值原来位置的值发生了改变，重新放置key
    QSort(begin,i-1);
    QSort(i+1,end);
}

void findClosestPair(int *arr, int num){
    int min = MAX;
    for (int i=1; i<num; i++){
        if (arr[i]-arr[i-1]<min){
            min = arr[i]-arr[i-1];  //找到最小的差
        }
    }
    for (int i = 1; i<num; i++){    //再次遍历，找到对应的数对
        if (arr[i]-arr[i-1] == min){
            printf("%d %d, ",arr[i-1],arr[i]);  
        }
    }
    printf("\b\b \n");
}

int main(){
    int num;
    int caseNum = 0;
    
    // 文件输入方式
    freopen("5_1_input.in", "r", stdin);
    while(scanf("%d",&num)!=EOF){
        caseNum++;
        printf("==== Case %d ====\n",caseNum);
        for(int i = 0; i < num; i++){
            scanf("%d",&arr[i]);
        }
        // resort(0,num-1);
        QSort(0,num-1);
        // for(int i = 0; i < num; i++){
        //     printf("%d",arr[i]);
        // }
        findClosestPair(arr, num);
    }
    fclose(stdin);
    
    /*
     终端输入方式
    while(scanf("%d",&num)!=EOF){
        caseNum++;
        printf("==== Case %d ====\n",caseNum);
        for(int i = 0; i < num; i++){
            scanf("%d",&arr[i]);
        }
        resort(arr, num);
        findClosestPair(arr, num);
    }
     */
    
    return 0;
}
