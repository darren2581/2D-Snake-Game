#include "LinkedList.h"
#include <stdio.h>

#define LIST LinkedList
#define NODE Node
#define HEAD head
#define TAIL tail
#define DATA data

LinkedList* createLinkedList()  /* Create a new linked list*/
{
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList)); /* Allocate memory for the list*/
    if (list != NULL)  /* Check if memory allocation was successful*/
    {
        list->head = NULL; /* Initialize the head pointer to NULL*/
        list->tail = NULL; /* Initialize the pointer to NULL*/
    }
    return list;
}

void insertPlayer(LinkedList* list, int row, int column)  /* Insert a new node at the end of the list*/
{
    Node* newNode = (Node*)malloc(sizeof(Node)); /* Allocate memory for the new node*/
    if (newNode == NULL)  /* Check if memory allocation was successful*/
    {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->row = row; /* Set the row of the new node*/
    newNode->column = column; /* Set the column of the new node*/
    newNode->next = NULL; /* Set the next pointer of the new node to NULL*/

    if (list->head == NULL)  /*Check if the list is empty*/
    {
        /* If the list is empty, set the new node as the head*/
        list->head = newNode; 
    } 
    else 
    {
        /* Otherwise, find the last node and append the new node to it*/
        Node* current = list->head; /* Start from the head of the list*/
        while (current->next != NULL)  /* Traverse the list until the last node*/
        {
            current = current->next; /* Move to the next node*/
        }
        current->next = newNode; /* Append the new node to the last node*/
    }
}

void insertSnake(LinkedList* list, int row, int column) /* Insert a new node at the end of the list*/
{
    Node* newNode = (Node*)malloc(sizeof(Node)); /* Allocate memory for the new node*/
    if (newNode == NULL)  /* Check if memory allocation was successful*/
    {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->row = row; /* Set the row of the new node*/
    newNode->column = column; /* Set the column of the new node*/
    newNode->next = NULL; /* Set the next pointer of the new node to NULL*/

    if (list->head == NULL) 
    {
        /* If the list is empty, set the new node as the head*/
        list->head = newNode;
    } 
    else 
    {
        /* Otherwise, find the last node and append the new node to it*/
        Node* current = list->head; /* Start from the head of the list*/
        while (current->next != NULL)  /* Traverse the list until the last node*/
        {
            current = current->next; /* Move to the next node*/
        }
        current->next = newNode; /* Append the new node to the last node*/
    }
}

Node* removeLastPlayer(LinkedList* list)  /*Remove the last node from the list*/
{
    if (list->head == NULL || list->head->next == NULL)  /*Check is the list empty or only have one node*/
    {
        return NULL; /* Nothing to remove or only one node in the list*/
    }

    Node* current = list->head; /* Start from the head of the list*/
    Node* previous = NULL; /* Pointer to the previous node*/

    /* Traverse the list until the second last node*/
    while (current->next != NULL)  /* Traverse the list until the last node*/
    {
        previous = current; /* Update the previous pointer*/
        current = current->next; /* Move to the next node*/
    }

    /* Now 'current' points to the last node*/
    free(current); /* Free the memory of the last node*/
    previous->next = NULL; /* Update the 'next' pointer of the previous node to NULL*/
    return previous; /* Return the new last node*/
}

Node* removeLastSnake(LinkedList* list) 
{
    if (list->head == NULL) 
    {
        return NULL; /* Nothing to remove if the list is empty*/
    }
    
    Node* current = list->head; /* Start from the head of the list*/
    Node* previous = NULL; /* Pointer to the previous node*/
    
    /* Traverse the list until the last node*/
    while (current->next != NULL) 
    {
        previous = current; /* Update the previous pointer*/
        current = current->next; /* Move to the next node*/
    }
    
    /* Now 'current' points to the last node*/
    if (previous != NULL)  /* Check if the list has more than one node*/
    {
        previous->next = NULL; /* Update the 'next' pointer of the previous node to NULL*/
    } 
    else {

        list->head = NULL; /* If 'previous' is NULL, it means the list only had one node*/
    }

    return current; /* Return the removed node*/
}



