#include <stdlib.h>
#include <stdio.h>
int count=0;
typedef struct stack {
    int *item;
    int top;
    int size;
} st;
void create(st *s,int size);
int isfull(st *s);
int isempty(st *s);
void push(st *s,int value);
void pop(st *s);
void print(st *s);
int peek(st *s);
void freestack(st *s);
int main(){
    int size;
    st s;
    printf("printf the size");
    scanf("%d",&size);
    create(&s,size);
for(int i =0;i<size;i++){
    push(&s,i*i);
}
    print(&s);
    pop(&s);
    pop(&s);
    peek(&s);
    print(&s);
    freestack(&s);
}
void create(st *s,int size){
    s->item=(int *)malloc(size*sizeof(size));
    if(s->item==NULL){
        printf("failed to allocate memory");
        return;
    }
    s->top=-1;
    s->size=size;
}
int isfull(st *s){
return s->top== s->size-1;
}
int isempty(st *s){
return s->top==-1;
}
void push(st *s,int value){
    if(isfull(s)){
        printf("stack is full");
    }else{
        s->top++;
        s->item[s->top]= value;
        printf("%d ",value);
        count++;
    }
    printf("\n");
}
void pop(st *s){
    if(isempty(s)){
        printf("stack is empty");
    }else{
        printf("%d is popped from the stack",s->item[s->top]);
        s->top--;
        count--;
    }
       printf("\n"); 
}
void print(st *s){
    if(isempty(s)){
        printf("stack is empty");
    }else{
        for(int i = 0;i<count;i++){
            printf("%d ",s->item[i]);
        }
    }
    printf("\n");
}
int peek(st *s){
    if(isempty(s)){
        printf("empty stack");
        return -1;
    }
    return s->item[s->top];
}
void freestack(st *s){
    free(s->item);
}