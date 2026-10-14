#include <stdio.h>
#include <stdlib.h>

// A node holds a value and the address of the node below it
struct Node
{
    int data;
    struct Node *next;
};

// Returns 1 if the stack is empty, otherwise 0
int isEmpty(struct Node *top)
{
    return top == NULL;
}

// PUSH: add a new node on top
struct Node* push(struct Node *top, int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if(newNode == NULL)
    {
        printf("Stack overflow! Memory allocation failed\n");
        return top;
    }
    newNode->data = value;
    newNode->next = top;            // new node points to the old top
    top = newNode;                  // new node becomes the top
    return top;
}

// POP: remove the top node
struct Node* pop(struct Node *top)
{
    if(isEmpty(top))
    {
        printf("Stack underflow! Cannot pop.\n");
        return top;
    }
    struct Node *temp = top;        // save the top node
    printf("Popped %d\n", temp->data);
    top = top->next;                // top moves to the node below
    free(temp);                     // free the old top
    return top;
}

// PEEK: show the top value without removing it
void peek(struct Node *top)
{
    if(isEmpty(top))
    {
        printf("Stack is empty! Nothing to peek.\n");
        return;
    }
    printf("Top element: %d\n", top->data);
}

// SIZE: count the nodes
int size(struct Node *top)
{
    int count = 0;
    while(top != NULL)
    {
        count++;
        top = top->next;
    }
    return count;
}

// DISPLAY: print from top to bottom
void display(struct Node *top)
{
    if(isEmpty(top))
    {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack (top to bottom):");
    while(top != NULL)
    {
        printf(" %d", top->data);
        top = top->next;
    }
    printf("\n");
}

// ---------- MAIN ----------

int main(void)
{
    struct Node *top = NULL;
    struct Node *temp;
    int choice, value;

    while(1)                        // loop forever, so the menu keeps coming back
    {
        printf("\n1.Push  2.Pop  3.Peek  4.Display\n");
        printf("5.Size  6.Is Empty  7.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);       // read the user's choice

        switch(choice)              // jump to the matching case
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                top = push(top, value);
                break;
            case 2:
                top = pop(top);
                break;
            case 3:
                peek(top);
                break;
            case 4:
                display(top);
                break;
            case 5:
                printf("Stack size: %d\n", size(top));
                break;
            case 6:
                if(isEmpty(top))
                    printf("Stack is empty\n");
                else
                    printf("Stack is not empty\n");
                break;
            case 7:
                while(top != NULL)      // free the remaining nodes
                {
                    temp = top;
                    top = top->next;
                    free(temp);
                }
                return 0;               // the only way out of the loop
            default:
                printf("Invalid choice\n");
        }
    }
}


Output :
Choice 1, value 10
Choice 1, value 20
Choice 1, value 30
Choice 4:   Stack (top to bottom): 30 20 10
Choice 3:   Top element: 30
Choice 5:   Stack size: 3
Choice 2:   Popped 30
Choice 4:   Stack (top to bottom): 20 10
Choice 6:   Stack is not empty
Choice 2:   Popped 20
Choice 2:   Popped 10
Choice 6:   Stack is empty
Choice 2:   Stack underflow! Cannot pop.
Choice 3:   Stack is empty! Nothing to peek.
Choice 4:   Stack is empty
Choice 5:   Stack size: 0
Choice 12:  Invalid choice
Choice 7:   (frees the list and exits)
