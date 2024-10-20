#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct node  
{   int    coef, exp;  
    struct node  *next;  
} NODE;  
  
void multiplication( NODE *, NODE * , NODE * );  
void input( NODE * );  
void output( NODE * );  


void addnode(NODE *head, int coef, int exp) {
    // 创建新节点
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode->coef = coef;
    newNode->exp = exp;
    newNode->next = NULL;

    NODE *current = head;
    // 寻找插入位置 (从小到大)
    while (current->next != NULL && current->next->exp < exp) {
        current = current->next;
    }

    // 如果已有相同的指数，则合并
    if (current->next != NULL && current->next->exp == exp) {
        current->next->coef += coef;
        // 如果合并后系数变为0，删除该节点
        if (current->next->coef == 0) {
            NODE *temp = current->next; // 保存当前节点
            current->next = current->next->next; // 删除当前节点
            free(temp); // 释放内存
        }
        free(newNode); // 释放新节点内存（因为没有插入）
    } else {
        // 进行插入
        newNode->next = current->next;
        current->next = newNode; // 插入新节点
    }
}

void clear_coef_equal_zero(NODE *head) {
    NODE *current = head->next;
    NODE *prev = head;  // 使用 prev 指向当前节点的前一个节点

    while (current != NULL) {
        if (current->coef == 0) {  // 如果系数为0
            prev->next = current->next;  // 跳过当前节点
            NODE *temp = current;  // 保存当前节点以释放内存
            current = current->next; // 移动到下一个节点
            free(temp);  // 释放内存
        } else {
            prev = current;  // 继续在链表中向前移动
            current = current->next;
        }
    }
}

void multiplication(NODE *head1, NODE *head2, NODE *head3) {
    NODE *p3 = head3; // 指向头节点
    NODE *p1 = head1->next; // 从第一个有效节点开始
    int coef, exp;

    while (p1 != NULL) {
        NODE *p2 = head2->next; // 每次外层循环时重置p2
        while (p2 != NULL) {
            coef = p1->coef * p2->coef;
            exp = p1->exp + p2->exp;
            addnode(p3, coef, exp); // 调用addnode插入项
            p2 = p2->next; // 移动到下一个节点
        }
        p1 = p1->next; // 移动到下一个节点
    }
    clear_coef_equal_zero(head3); // 清除系数为0的项
    if (head3->next == NULL) { // 如果结果为空，则输出0
        printf("<0,0>,\n");
    }
}



void input( NODE * head )  
{   int flag, sign, sum, x;  
    char c;  
  
    NODE * p = head;  
  
    while ( (c=getchar()) !='\n' )  
    {  
        if ( c == '<' )  
        {    sum = 0;  
             sign = 1;  
             flag = 1;  
        }  
        else if ( c =='-' )  
             sign = -1;  
        else if( c >='0'&& c <='9' )  
        {    sum = sum*10 + c - '0';  
        }  
        else if ( c == ',' )  
        {    if ( flag == 1 )  
             {    x = sign * sum;  
                  sum = 0;  
                  flag = 2;  
          sign = 1;  
             }  
        }  
        else if ( c == '>' )  
        {    p->next = ( NODE * ) malloc( sizeof(NODE) );  
             p->next->coef = x;  
             p->next->exp  = sign * sum;  
             p = p->next;  
             p->next = NULL;  
             flag = 0;  
        }  
    }  
}  
  
void output( NODE * head )  
{  
    while ( head->next != NULL )  
    {   head = head->next;  
        printf("<%d,%d>,", head->coef, head->exp );  
    }  
    printf("\n");  
}  
  
int main()  
{   NODE * head1, * head2, * head3;  
  
    head1 = ( NODE * ) malloc( sizeof(NODE) );  
    input( head1 );  
  
    head2 = ( NODE * ) malloc( sizeof(NODE) );  
    input( head2 );  
  
    head3 = ( NODE * ) malloc( sizeof(NODE) );  
    head3->next = NULL;  
    multiplication( head1, head2, head3 );  
  
    output( head3 );  
    return 0;  
}  