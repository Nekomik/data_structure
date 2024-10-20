#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct node  
{   int         data;  
    struct node * next;  
} NODE;  

int arr[100000] = {0};

void output( NODE *, int );  
void change( int, int, NODE * );  
  
void output( NODE * head, int kk )  
{   int k=0;  
  
    printf("0.");  
    while ( head->next != NULL && k<kk )  
    {   printf("%d", head->next->data );  
        head = head->next;  
        k ++;  
    }  
    printf("\n");  
}  

NODE * find( int x,int y, NODE * head ){
       NODE * p;
       p = head->next;
       int i= 0;
       while( p!= NULL && ( arr[i]!= x || p->data != y )){
          p = p->next;
          i++;
       } 
       if(p == NULL){
          return NULL;  
       }
       else{
          return p;
       }
}

void change(int n, int m, NODE * head) {
    int lock = 1;
    int i = 0;
    int quo, rem;
    NODE * p = head; // p 从头节点开始
    while (lock) {
        quo = n * 10 / m;
        rem = n * 10 % m;

        NODE * q = (NODE *)malloc(sizeof(NODE));
        if (q == NULL) {
            // 处理内存分配失败
            return;
        }

        if (rem == 0) {
            lock = 0;
            q->data = quo;
            q->next = NULL;
            p->next = q; // 链接链表
        } else {
            arr[i++] = rem;
            if (find(rem, quo, head) == NULL) {
                q->data = quo;
                q->next = NULL;
                p->next = q; // 链接链表
            } else {
                lock = 0;
                NODE * foundNode = find(rem, quo, head); // 保持找到的节点
                if (foundNode != NULL) {
                    p->next = foundNode; // 链接已存在节点
                }
            }
        }
        p = p->next; // 只在新节点链接后再移动
        n = rem;
    }
}



int main()  
{   int n, m,k;  
    NODE * head;  
  
    scanf("%d%d%d", &n, &m, &k);  
    head = (NODE *)malloc( sizeof(NODE) );  
    head->next = NULL;  
    head->data = -1;  
    change( n, m, head );  
    output( head,k );  
    return 0;  
}  
  