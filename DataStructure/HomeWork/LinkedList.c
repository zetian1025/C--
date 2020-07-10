#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

char cmd;

int main(){
    FILE* fp;
    char filename[30];
    printf("Input the file name $.txt\n");
    gets(filename);
    if ((fp=fopen(filename,"r")) == NULL){
        printf("Unable to open file %s",filename);
        exit(0);
    }

    DoubleLinkedList L = (DoubleLinkedList)malloc(sizeof(List));
    if (!L){
        printf("Not enough space.");
        exit(0);
    }

    printf("Command:( h to get help)\nFor the first time, click 'C' to make a list.\n");
    for (int flag = 1;flag != 0;){
        scanf(" %c",&cmd);
        switch (cmd)
        {
        case 'H':
        case 'h':{
            printf("******************************\n\n");
            printf("Make a list : C\n");
            printf("Insert an element: I\n");
            printf("Delete an element: D\n");
            printf("Show the length of the list: L\n");
            printf("Show the list: O\n");
            printf("Search for an element by its value: S\n");
            printf("Reverse the list: R\n");
            printf("Search for an element by its position: N\n");
            printf("Search for the middle-position element: M\n");
            printf("Search for an element by its position from the last: B\n");
            printf("Quit the program: E\n\n");
            printf("Warning: for the first time, you should click 'C' to make a list.\n");
            printf("*******************************\n");
            break;
        }

        case 'c':
        case 'C':{
            if(MakeList(fp,L)){
                printf("Succeed.'O' to show the list.\n");
            }
            break;
        }

        case 'i':
        case 'I':{
            ElemType elem;
            printf("What element do you want to insert?\n");
            scanf("%d",&elem);

            bool result = InsertElem(L,elem);
            if (result){
                printf("Succeed.'O' to show the list.");
            }
            else{
                printf("Oops! Not enough space!\n");
                exit(0);
            }
            break;
        }

        case 'd':
        case 'D':{
            ElemType elem;
            printf("Which element do you want to delete?\n");
            scanf("%d",&elem);
            bool result = DeleteElem(L,elem);
             if (result){
                printf("Succeed.'O' to show the list.\n");
            }
            else{
                printf("Oops! No such element in the list!\n");
            }
            break;
        }

        case 'l':
        case 'L':{
            printf("%d",ListLength(L));
            break;
        }

        case 'o':
        case 'O':{
            ShowList(L);
            break;
        }

        case 's':
        case 'S':{
            ElemType elem;
            printf("Which element do you want to search for?\n");
            scanf("%d",&elem);

            int pos = SearchElem(L,elem);
            if (pos == 0){
                printf("Oops! No such element in the list!\n");
            }else{
                printf("The element is at position #%d\n",pos);
            }
            break;
        }

        case 'r':
        case 'R':{
            ReverseList(L);
            printf("Succeed.\n");
            break;
        }

        case 'n':
        case 'N':{
            int pos;
            printf("Which position do you want to search?\n");
            scanf("%d",&pos);
            if (pos <= 0 || pos > ListLength(L)){
                printf("Invalid position.");
            }
            else{
                printf("%d\n",LocateElem(L,pos));
            }
            break;
       }

        case 'm':
        case 'M':{
            printf("%d\n",LocateMiddleElem(L));
            break;
        }

        case 'b':
        case 'B':{
            int pos;
            printf("Which position do you want to search?\n(From the last element)\n");
            scanf("%d",&pos);
            if (pos <= 0 || pos > ListLength(L)){
                printf("Invalid position.\n");
            }
            else{
                printf("%d\n",LocateElemFromLast(L,pos));
            }
            break;
        }

        case 'e':
        case 'E':{
            flag = 0;
            break;
        }
        
        default:{
            printf("Command invalid.Input h to get help.\n");
            break;
        }
        }
    }

    fclose(fp);

    return 0;
}