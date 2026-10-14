#include <stdio.h>
#include <stdlib.h>

// A node holds a value and the address of the next node
// In a circular list the last node points back to the first node (head)
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
    newNode->next = newNode;        // a single node points to itself
    return newNode;
}

// ---------- INSERT ----------

struct Node* insertBeginning(struct Node *head, int value)
{
    struct Node *newNode = createNode(value);
    if(head == NULL)                // empty list: the node points to itself
    {
        return newNode;
    }
    struct Node *last = head;
    while(last->next != head)       // walk to the last node
    {
        last = last->next;
    }
    newNode->next = head;           // new node points to the old first node
    last->next = newNode;           // last node points to the new node (keeps the circle)
    return newNode;                 // new node is the new head
}

struct Node* insertEnd(struct Node *head, int value)
{
    struct Node *newNode = createNode(value);
    if(head == NULL)                // empty list: the node points to itself
    {
        return newNode;
    }
    struct Node *last = head;
    while(last->next != head)       // walk to the last node
    {
        last = last->next;
    }
    last->next = newNode;           // old last node points to the new node
    newNode->next = head;           // new node points back to head (keeps the circle)
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
    if(head == NULL)                // empty list: only position 1 is possible
    {
        printf("Position out of range\n");
        return head;
    }
    struct Node *temp = head;
    int i = 1;
    while(i < pos - 1 && temp->next != head)
    {
        temp = temp->next;          // walk to the node BEFORE the position
        i++;
    }
    if(i < pos - 1)                 // ran out of nodes before reaching the position
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
    if(head->next == head)          // only one node
    {
        free(head);
        return NULL;
    }
    struct Node *last = head;
    while(last->next != head)       // walk to the last node
    {
        last = last->next;
    }
    struct Node *temp = head;       // save the first node
    head = head->next;              // head moves to the second node
    last->next = head;              // last node points to the new head (keeps the circle)
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
    if(head->next == head)          // only one node
    {
        free(head);
        return NULL;
    }
    struct Node *temp = head;
    while(temp->next->next != head) // stop at the second-last node
    {
        temp = temp->next;
    }
    free(temp->next);               // delete the last node
    temp->next = head;              // second-last node points back to head
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
    int i = 1;
    while(i < pos - 1 && temp->next != head)
    {
        temp = temp->next;          // walk to the node BEFORE the one to delete
        i++;
    }
    if(i < pos - 1 || temp->next == head)   // no node at that position
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
    if(head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    struct Node *temp = head;
    int pos = 1;
    do
    {
        if(temp->data == key)
        {
            printf("%d found at position %d\n", key, pos);
            return;
        }
        temp = temp->next;
        pos++;
    } while(temp != head);          // stop when we are back at head
    printf("%d not found\n", key);
}

void display(struct Node *head)
{
    if(head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    struct Node *temp = head;
    do
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while(temp != head);          // stop when we are back at head
    printf("(back to head)\n");
}

// Free every node (break the circle first so the loop can stop at NULL)
void freeList(struct Node *head)
{
    if(head == NULL)
    {
        return;
    }
    struct Node *last = head;
    while(last->next != head)
    {
        last = last->next;
    }
    last->next = NULL;              // break the circle
    while(head != NULL)
    {
        struct Node *temp = head;
        head = head->next;
        free(temp);
    }
}

// ---------- MAIN ----------

int main(void)
{
    struct Node *head = NULL;
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
                freeList(head);         // free all nodes before leaving
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
Choice 8:   10 -> 20 -> 25 -> 30 -> (back to head)
Choice 4:   (deletes 10)
Choice 5:   (deletes 30)
Choice 6, position 2:   (deletes 25)
Choice 8:   20 -> (back to head)
Choice 7, value 20:   20 found at position 1
Choice 7, value 99:   99 not found
Choice 6, position 6:   Position out of range
Choice 3, value 0, position 0:   Invalid position
Choice 12:   Invalid choice
Choice 9:   (frees the list and exits)
