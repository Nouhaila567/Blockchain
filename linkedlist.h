#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node {
    int data;
    struct Node *next;
} node;

node *createNode(int data);
node *insertNode(node *head, int data);
node *deleteNode(node *head, int data);
void displayList(node *head);

#endif