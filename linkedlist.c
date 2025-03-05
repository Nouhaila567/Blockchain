#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

node *createNode(int data) {
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

node *insertNode(node *head, int data) {
    node *newNode = createNode(data);
    if (!newNode) return head;
    newNode->next = head;
    return newNode;
}

node *deleteNode(node *head, int data) {
    if (!head) return NULL;

    if (head->data == data) {
        node *temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    node *current = head;
    while (current->next && current->next->data != data) {
        current = current->next;
    }

    if (current->next && current->next->data == data) {
        node *temp = current->next;
        current->next = current->next->next;
        free(temp);
        return head;
    }

    return head;
}

void displayList(node *head) {
    node *current = head;
    while (current) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}