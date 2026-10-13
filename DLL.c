#include <stdio.h>
#include <stdlib.h>

// A node holds a value, the address of the previous node and the next node
struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
};

// Create one node (shared by all insert functions)
struct Node* createNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if(newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// ---------- INSERT ----------

struct Node* insertBeginning(struct Node *head, int value)
{
    struct Node *newNode = createNode(value);
    if(head != NULL)
    {
        newNode->next = head;       // new node points forward to the old first node
        head->prev = newNode;       // old first node points back to the new node
    }
    return newNode;                 // new node is the new head
}

struct Node* insertEnd(struct Node *head, int value)
{
    struct Node *newNode = createNode(value);
    if(head == NULL)                // empty list: new node becomes the first node
    {
        return newNode;
    }
    struct Node *temp = head;
    while(temp->next != NULL)       // walk to the last node
    {
        temp = temp->next;
    }
    temp->next = newNode;           // last node points forward to the new node
    newNode->prev = temp;           // new node points back to the old last node
    return head;
}

struct Node* insertPosition(struct Node *head, int value, int pos)
{
    if(pos < 1)
    {
        printf("Invalid position\n");
        return head;
    }
    if(pos == 1)                    // position 1 = insert at beginning
    {
        return insertBeginning(head, value);
    }
    struct Node *temp = head;
    for(int i = 1; i < pos - 1 && temp != NULL; i++)
    {
        temp = temp->next;          // walk to the node BEFORE the position
    }
    if(temp == NULL)
    {
        printf("Position out of range\n");
        return head;
    }
    struct Node *newNode = createNode(value);
    newNode->next = temp->next;     // step 1: new node points forward to the node after temp
    newNode->prev = temp;           // step 2: new node points back to temp
    if(temp->next != NULL)
    {
        temp->next->prev = newNode; // step 3: the node after temp points back to the new node
    }
    temp->next = newNode;           // step 4: temp points forward to the new node
    return head;
}

// ---------- DELETE ----------

struct Node* deleteBeginning(struct Node *head)
{
    if(head == NULL)
    {
        printf("List is empty\n");
        return head;
    }
    struct Node *temp = head;       // save the first node
    head = head->next;              // head moves to the second node
    if(head != NULL)
    {
        head->prev = NULL;          // the new first node has nothing before it
    }
    free(temp);                     // free the old first node
    return head;
}

struct Node* deleteEnd(struct Node *head)
{
    if(head == NULL)
    {
        printf("List is empty\n");
        return head;
    }
    if(head->next == NULL)          // only one node
    {
        free(head);
        return NULL;
    }
    struct Node *temp = head;
    while(temp->next != NULL)       // walk to the last node
    {
        temp = temp->next;
    }
    temp->prev->next = NULL;        // second-last node becomes the last
    free(temp);                     // delete the last node
    return head;
}

struct Node* deletePosition(struct Node *head, int pos)
{
    if(head == NULL)
    {
        printf("List is empty\n");
        return head;
    }
    if(pos < 1)
    {
        printf("Invalid position\n");
        return head;
    }
    if(pos == 1)                    // position 1 = delete first node
    {
        return deleteBeginning(head);
    }
    struct Node *temp = head;
    for(int i = 1; i < pos && temp != NULL; i++)
    {
        temp = temp->next;          // walk to the node to delete
    }
    if(temp == NULL)
    {
        printf("Position out of range\n");
        return head;
    }
    temp->prev->next = temp->next;  // node before skips over temp
    if(temp->next != NULL)
    {
        temp->next->prev = temp->prev;  // node after points back to the node before
    }
    free(temp);
    return head;
}

// ---------- SEARCH AND DISPLAY ----------

void search(struct Node *head, int key)
{
    int pos = 1;
    while(head != NULL)
    {
        if(head->data == key)
        {
            printf("%d found at position %d\n", key, pos);
            return;
        }
        head = head->next;
        pos++;
    }
    printf("%d not found\n", key);
}

void displayForward(struct Node *head)
{
    if(head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    printf("NULL <-> ");
    while(head != NULL)
    {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void displayBackward(struct Node *head)
{
    if(head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    while(head->next != NULL)       // go to the last node first
    {
        head = head->next;
    }
    printf("NULL <-> ");
    while(head != NULL)
    {
        printf("%d <-> ", head->data);
        head = head->prev;          // move backward
    }
    printf("NULL\n");
}

// ---------- MAIN ----------

int main(void)
{
    struct Node *head = NULL;
    struct Node *temp;
    int choice, value, pos;

    while(1)                        // loop forever, so the menu keeps coming back
    {
        printf("\n1.Insert Beginning  2.Insert End  3.Insert Position\n");
        printf("4.Delete Beginning  5.Delete End   6.Delete Position\n");
        printf("7.Search            8.Display Forward\n");
        printf("9.Display Backward  10.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);       // read the user's choice

        switch(choice)              // jump to the matching case
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                head = insertBeginning(head, value);
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                head = insertEnd(head, value);
                break;
            case 3:
                printf("Enter value and position: ");
                scanf("%d %d", &value, &pos);
                head = insertPosition(head, value, pos);
                break;
            case 4:
                head = deleteBeginning(head);
                break;
            case 5:
                head = deleteEnd(head);
                break;
            case 6:
                printf("Enter position: ");
                scanf("%d", &pos);
                head = deletePosition(head, pos);
                break;
            case 7:
                printf("Enter value to search: ");
                scanf("%d", &value);
                search(head, value);
                break;
            case 8:
                displayForward(head);
                break;
            case 9:
                displayBackward(head);
                break;
            case 10:
                while(head != NULL)     // free the remaining nodes
                {
                    temp = head;
                    head = head->next;
                    free(temp);
                }
                return 0;               // the only way out of the loop
            default:
                printf("Invalid choice\n");
        }
    }
}
