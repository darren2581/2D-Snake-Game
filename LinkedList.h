#include <stddef.h>
#include <stdlib.h>

#ifndef LINKEDLIST_H /* Include guard to prevent double inclusion of the header file */
#define LINKEDLIST_H /* Define the header file if it has not been defined */
#define LIST LinkedList /* Define an alias for the LinkedList structure */
#define NODE Node /* Define an alias for the Node structure */ 
#define HEAD head /* Define an alias for the head pointer */
#define TAIL tail /* Define an alias for the tail pointer */
#define DATA data /* Define an alias for the data field */

typedef struct 
{
    int row; /* Row of the move */
    int column; /* Column of the move */
} Move; /* Define the Move structure */

/* Node structure to represent each element in the linked list*/
typedef struct Node 
{
    int row; /* Data stored in the node */
    int column; /* Data stored in the node */
    struct Node* next; /* Pointer to the next node in the list*/
} Node; /* Define the Node structure */

/* LinkedList structure to represent the linked list itself*/
typedef struct 
{
    Node* head; /* Pointer to the first node in the list*/
    Node* tail; /* Pointer to the last node in the list*/
} LinkedList; /* Define the LinkedList structure */

LinkedList* createLinkedList(); /* Create a new linked list */
void insertPlayer(LIST* list, int row, int column); /* Insert a new node at the end of the list */
void insertSnake(LinkedList* list, int row, int column); /* Insert a new node at the end of the list */
Node* removeLastPlayer(LinkedList* list); /* Remove the last node from the list */
Node* removeLastSnake(LinkedList* list); /* Remove the last node from the list */

#endif
