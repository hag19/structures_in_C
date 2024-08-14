#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int value;
    struct node *next;
} node;

typedef struct queue {
    node *tail;
    node *head;
} queue;

void create(queue *q);
int enqueue(queue *q, int value);
int dequeue(queue *q);
void display(queue *q);
void destroy(queue *q);
int main() {
    queue q;
    create(&q);
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    display(&q);
    dequeue(&q);
    dequeue(&q);
    dequeue(&q);
    destroy(&q);
    return 0;
}

void create(queue *q) {
    q->head = NULL;
    q->tail = NULL;
}

int enqueue(queue *q, int value) {
    node *new_node = (node *)malloc(sizeof(node));
    if (!new_node) return 0;  // Ошибка выделения памяти
    new_node->value = value;
    new_node->next = NULL;  // Новый узел всегда имеет `next` равный NULL

    if (q->tail) {  // Если очередь не пуста
        q->tail->next = new_node;  // Текущий хвост указывает на новый узел
    }
    q->tail = new_node;  // Обновляем хвост
    if (!q->head) {  // Если очередь была пуста
        q->head = new_node;  // Обновляем голову
    }
    return 1;
}

int dequeue(queue *q) {
    if (q->head == NULL) {
        printf("Queue underflow\n");
        return 0;
    }
    node *tmp = q->head;
    int value = tmp->value;
    q->head = q->head->next;

    if (q->head == NULL) {
        q->tail = NULL;
    }

    printf("%d deleted\n", value);
    free(tmp);
    return value;
}

void display(queue *q){
    node *tmp = q->head;
    while(tmp){
    printf("%d ",tmp->value);
    tmp=tmp->next;
    }
    printf("\n");
}
void destroy(queue *q){
    while(q->head){
    node *tmp=q->head;
    printf("%d ", tmp->value);
    q->head= q->head->next;
    free(tmp);
    }
        q->tail=NULL;
        printf("eleminated");
}