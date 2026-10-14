#include <stdio.h>
#include <stdlib.h>

// A node holds a value and the address of the next node
struct Node
{
    int data;
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
    newNode->next = NULL;
    return newNode;
}

// ---------- INSERT ----------

struct Node* insertBeginning(struct Node *head, int value)
{
    struct Node *newNode = createNode(value);
    newNode->next = head;           // new node points to the old first node
    head = newNode;                 // head now points to the new node
    return head;
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
    temp->next = newNode;           // last node points to the new node
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
    newNode->next = temp->next;     // step 1: new node points to the node after temp
    temp->next = newNode;           // step 2: temp points to the new node
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
    while(temp->next->next != NULL) // stop at the second-last node
    {
        temp = temp->next;
    }
    free(temp->next);               // delete the last node
    temp->next = NULL;              // second-last node becomes the last
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
    for(int i = 1; i < pos - 1 && temp->next != NULL; i++)
    {
        temp = temp->next;          // walk to the node BEFORE the one to delete
    }
    if(temp->next == NULL)
    {
        printf("Position out of range\n");
        return head;
    }
    struct Node *del = temp->next;  // node to remove
    temp->next = del->next;         // skip over it
    free(del);
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

void display(struct Node *head)
{
    if(head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    while(head != NULL)
    {
        printf("%d -> ", head->data);
        head = head->next;
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
        printf("7.Search            8.Display      9.Exit\n");
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
                display(head);
                break;
            case 9:
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


Output:
Choice 1, value 10      (list: 10)
Choice 2, value 20      (list: 10 20)
Choice 2, value 30      (list: 10 20 30)
Choice 3, value 25, position 3
Choice 8:   10 -> 20 -> 25 -> 30 -> NULL
Choice 4:   (deletes 10)
Choice 5:   (deletes 30)
Choice 6, position 2:   (deletes 25)
Choice 8:   20 -> NULL
Choice 7, value 30:   30 not found
Choice 6, position 6:   Position out of range
Choice 3, value 0, position 0:   Invalid position
Choice 12:   Invalid choice
Choice 9:   (frees the list and exits)
