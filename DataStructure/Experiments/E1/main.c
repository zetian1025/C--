#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int ClassID;
  int StuID;
  int Grade;
  struct node *next;
} StudentLinkedListNode;

/** 打印单个节点 */
void printLinkedListNode(StudentLinkedListNode *node) {
  printf("{class:%d, ID:%d, Grade:%d}", node->ClassID, node->StuID,
         node->Grade);
  if (node->next != NULL) {
    printf("->");
  } else {
    printf("\n");
  }
}

/** 输出该表的成绩情况 */
void outputStudentLinkedList(StudentLinkedListNode *head) {
  if (head == NULL) { /** 1.若头指针为空（即此时还未创建该表），则直接返回。*/
    return;
  }
  StudentLinkedListNode *node = head->next; /** 2.若正常，顺序输出即可。*/
  while (node != NULL) {
    printLinkedListNode(node);
    node = node->next;
  }
  return;
}

/** 新建一个链表node并返回 */
StudentLinkedListNode *studentLinkedListCreate(int class_id, int student_id,
                                               int grade) {
  StudentLinkedListNode *node =
      (StudentLinkedListNode *)malloc(sizeof(StudentLinkedListNode));
  node->ClassID = class_id;
  node->StuID = student_id;
  node->Grade = grade;
  node->next = NULL; /**将指向的下一个地址记为NULL。*/
  return node;
}

/** copy一个已有的node */
StudentLinkedListNode *studentLinkedListCopy(StudentLinkedListNode *src) {
  StudentLinkedListNode *tempNode =
      studentLinkedListCreate(src->ClassID, src->StuID, src->Grade);
  return tempNode;
}

/** 按照降序插入学生的成绩情况,并返回链表头指针 */
StudentLinkedListNode *studentLinkedListAdd(StudentLinkedListNode *head,
                                            StudentLinkedListNode *node) {
  if (head ==
      NULL) { /** 0.若头指针为空（即此时的node为该表的第一个元素），则新建头指针。*/
    head = (StudentLinkedListNode *)malloc(sizeof(StudentLinkedListNode));
    head->next = NULL;
  }
  StudentLinkedListNode *p =
      head; /**头指针（被确保）已存在，顺次比较节点的Grade值。*/
  StudentLinkedListNode *pNext =
      head->next; /**新建两个指针，作为待插入节点的前节点和后节点。*/
  while (
      pNext) { /**若后节点不为NULL（说明此时尚未遍历完整个链表），继续循环顺次遍历链表。*/
    if (pNext->Grade > node->Grade) {
      p = pNext;
      pNext = pNext->next;
    } else {
      break; /**出口条件一：到达表尾（node为最小元素）；出口条件二：找到适合位置。*/
    }
  }
  /**无论何种情况，此时待插入节点的位置都已经确定。*/
  p->next = node;
  node->next = pNext;
  return head;
}
/** 根据学号搜索某个学生的成绩情况 如果没有,请printf("this class  has no such
 * student as id=%d",id)； */
void searchByID(StudentLinkedListNode *head, int id) {
  StudentLinkedListNode *node = head;
  while (node && (node->StuID != id)) { /**遍历链表，确定所求节点的位置。*/
    node = node->next;
  }
  if (node == NULL) {
    printf("this class has no such student as id=%d", id);
  } else {
    printf("{class:%d, ID:%d, Grade:%d}\n", node->ClassID, node->StuID,
           node->Grade);
  }
  return;
}

/**函数功能：根据学号确定某个学生的数据是否已经存在。*/
bool searchExistenceByID(StudentLinkedListNode *head, int id) {
  StudentLinkedListNode *node = head;
  while (node && (node->StuID != id)) { /**遍历链表，确定所求节点的位置。*/
    node = node->next;
  }
  if (node == NULL) { /**若此时已经遍历完所有的节点（即该数据不存在）*/
    return false;
  } else { /**否则，说明该数据存在。*/
    return true;
  }
}

/**函数功能：根据学号搜索某个已经存在的学生，并更新其Grade值。*/
void searchChangeByID(StudentLinkedListNode *head, int id, int grade) {
  StudentLinkedListNode *node = head;
  while (node && (node->StuID != id)) {
    node = node->next;
  }
  node->Grade = grade;
}

/** 根据学号删除某个学生的成绩情况 如果没有,请printf("this class has no such
 * student as id=%d",id);*/
StudentLinkedListNode *deleteByID(StudentLinkedListNode *head, int id) {
  StudentLinkedListNode *node = head;
  while (node->next &&
         node->next->StuID != id) { /**判断下一个节点是否是待删除节点*/
    node = node->next;
  }
  if (node->next == NULL) { /**若已经到达表尾（不存在该节点）*/
    printf("this class has no such student as id=%d", id);
  } else {
    StudentLinkedListNode *temp = node->next; /**删除指定节点*/
    node->next = temp->next;
    free(temp);
    if (head->next == NULL) {
      head = NULL;
    }
  }
  return head;
}

/** 合并两个班级的成绩情况 */
StudentLinkedListNode *mergeLinkedList(StudentLinkedListNode *heads[]) {
  StudentLinkedListNode *NewHead = (StudentLinkedListNode *)malloc(
      sizeof(StudentLinkedListNode));            /**新建一个链表*/
  StudentLinkedListNode *head0 = heads[0]->next; /**两个链表的头指针*/
  StudentLinkedListNode *head1 = heads[1]->next;
  StudentLinkedListNode *head = NewHead; /**合并链表的头指针*/
  while (head0 && head1) {               /**若两个链表都未到达表尾*/
    if (head0->Grade > head1->Grade) {   /**比较当前指针指向值的大小*/
      head->next = studentLinkedListCopy(head0);
      head0 = head0->next;
    } else {
      head->next = studentLinkedListCopy(head1);
      head1 = head1->next;
    }
    head = head->next; /**合并链表的指针向后一个位置*/
  }
  /**若某个链表尚未到达表尾，则剩下的元素均为该表的元素，遍历复制即可。*/
  while (head0 != NULL) {
    head->next = studentLinkedListCopy(head0);
    head0 = head0->next;
    head = head->next;
  }
  while (head1 != NULL) {
    head->next = studentLinkedListCopy(head1);
    head1 = head1->next;
    head = head->next;
  }
  return NewHead; /**返回合并链表的头指针*/
}

/**链表的逆向存储*/
StudentLinkedListNode *reverseLinkedList(StudentLinkedListNode *head) {
  StudentLinkedListNode *node = head->next;
  StudentLinkedListNode *nodeNext;
  head->next = NULL;
  while (node) { /**每次对顺序链表的下一项（node）操作。*/
    nodeNext = node->next;
    node->next =
        head->next; /**使node的下一项为倒序链表的第一项（即原来的前一项）*/
    head->next = node; /**使node成为倒序链表的第一项*/
    node = nodeNext;   /**顺序表指针向后移动一个位置*/
  }
  return head;
}

int main() {
  StudentLinkedListNode *Class[2] = {NULL};
  StudentLinkedListNode *All = NULL;
  StudentLinkedListNode *reAll = NULL;
  printf("1.insert 2.search by StuID 3.delete by StuID 4.merge 5.reverse "
         "6.output q/Q.quit\n");
  int op;
  int i;
  int sign; /**[标记]用于判断是否输入正确*/

  int tempClass;
  int tempStuId;
  int tempGrade;
  StudentLinkedListNode *tempNode;
  while (printf("~> "),scanf("%d", &op)) { /**若无非法输入（即输入的是数字），进入循环*/
    switch (op) {
    case 1:
      printf("How many rows of data do you need to input?\n");
      fflush(stdin);
      while (printf("~> "),!scanf("%d", &i)) { /**防止非法输入*/
        fflush(stdin);
      }
      printf("input the i row data format as:class_id,student_id,grade\n");
      while (i != 0) {
        if (printf("~> "),!(sign = scanf("%d,%d,%d", &tempClass, &tempStuId, &tempGrade)) ||
            sign != 3) { /**防止非法输入*/
          fflush(stdin);
          continue;
        }
        if (tempClass >= 2 || tempClass <= -1) { /**防止数组越界（空指针）*/
          printf("class input error.(0/1 valid.)\n");
          continue;
        }
        if (searchExistenceByID(
                Class[tempClass],
                tempStuId)) { /** 1.若出现重复StuId（即同一个学生两个或以上不同成绩）*/
          printf(
              "We have had the student's record. Do you want to cover " /**用户选择保留原来或是覆盖Grade*/
              "it?\nY/N\n");
          getchar(); /**读取buffer里面的回车。防止对下面取choice的值产生影响。*/
          char choice;
          printf("~> ");
          scanf("%c", &choice);
          fflush(stdin); /**清空buffer，防止对接下来的输入产生影响。*/
          switch (choice) {
          case 'y':
          case 'Y': {
            searchChangeByID(Class[tempClass], tempStuId,
                             tempGrade); /**新Grade覆盖原Grade*/
            printf("Change completed.\n");
            break;
          }
          case 'n':
          case 'N': {
            printf("Skip completed.\n");
            break;
          }
          default:
            printf("Input error.\n"); /**输入错误处理，默认跳过覆盖*/
            printf("[Default] Skip completed.\n");
            break;
          }
        } else { /** 2.若确实为新的信息录入，将该信息加入链表*/
          tempNode = studentLinkedListCreate(tempClass, tempStuId, tempGrade);
          Class[tempClass] = studentLinkedListAdd(Class[tempClass], tempNode);
        }
        i--;
      }
      break;
    case 2:
    case 3:
      fflush(stdin);
      printf("input the data format as: ClassID, StuID\n");
      do {
        if (printf("~> "),!(sign = scanf("%d,%d", &tempClass, &tempStuId)) ||
            sign != 2) { /**防止非法输入*/
          fflush(stdin);
          continue;
        }
      } while (tempClass <= -1 || tempClass >= 2); /**防止数组越界（空指针）*/
      if (Class[tempClass] == NULL) { /**防止数组越界（空指针）*/
        printf("There's nothing in this class.\n");
        break;
      } else {
          if (op == 2){
            searchByID(Class[tempClass], tempStuId);
          }
          else{
            Class[tempClass] = deleteByID(Class[tempClass], tempStuId);
            printf("Finished.\n");
          }
          break;
      }
    case 4:
      fflush(stdin);
      if (Class[0] == NULL ||
          Class[1] == NULL) { /**若某个Class为空，则头指针为NULL；无法进行merge.*/
        printf("Some class(es) has no data yet.\n");
        break;
      }
      All = mergeLinkedList(Class);
      outputStudentLinkedList(All);
      break;
    case 5:
      fflush(stdin);
      if (All == NULL) { /**防止空指针异常*/
        printf("You haven't merge yet.\n");
        break;
      }
      reAll = reverseLinkedList(All);
      outputStudentLinkedList(reAll);
      break;
    case 6:
      fflush(stdin);
      printf("Class 0:\n");
      outputStudentLinkedList(Class[0]);
      printf("\nClass 1:\n");
      outputStudentLinkedList(Class[1]);
      break;
    default: /**输入错误处理*/
      printf("Input error! Please input again.\n");
      fflush(stdin);
      break;
    }
    printf("\n###################################\n");
    printf("1.insert 2.search by studentID 3.delete by studentID 4.merge 5. "
           "reverse 6.output q/Q.quit\n");
  }
  /**出循环条件：进行了非法输入。*/
  fflush(stdin);
  printf("Oops! Program has ended.\n");
  return 0;
}