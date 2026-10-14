#include <stdio.h>
#include <stdlib.h>

// A node holds a value and the address of the next node
struct Node
{
    int data;
    struct Node *next;
};

// The queue keeps the address of the first node (front) and the last node (rear)
struct Queue
{
    struct Node *front;
    struct Node *rear;
};

// Start with an empty queue
void initQueue(struct Queue *q)
{
    q->front = NULL;
    q->rear = NULL;
}

// Returns 1 if the queue is empty, otherwise 0
int isEmpty(struct Queue *q)
{
    return q->front == NULL;
}

// ENQUEUE: add a new node at the rear
void enqueue(struct Queue *q, int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if(newNode == NULL)
    {
        printf("Queue overflow! Memory allocation failed\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;           // the new node is the last node
    if(q->rear == NULL)             // empty queue: new node is both front and rear
    {
        q->front = newNode;
        q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;    // old last node points to the new node
        q->rear = newNode;          // rear moves to the new node
    }
}

// DEQUEUE: remove the node at the front
void dequeue(struct Queue *q)
{
    if(isEmpty(q))
    {
        printf("Queue underflow! Cannot dequeue.\n");
        return;
    }
    struct Node *temp = q->front;   // save the front node
    printf("Dequeued %d\n", temp->data);
    q->front = q->front->next;      // front moves to the second node
    if(q->front == NULL)            // queue became empty, so rear must be reset too
    {
        q->rear = NULL;
    }
    free(temp);                     // free the old front
}

// PEEK: show the front value without removing it
void peek(struct Queue *q)
{
    if(isEmpty(q))
    {
        printf("Queue is empty! Nothing to peek.\n");
        return;
    }
    printf("Front element: %d\n", q->front->data);
}

// SIZE: count the nodes
int size(struct Queue *q)
{
    int count = 0;
    struct Node *temp = q->front;
    while(temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

// DISPLAY: print from front to rear
void display(struct Queue *q)
{
    if(isEmpty(q))
    {
        printf("Queue is empty\n");
        return;
    }
    struct Node *temp = q->front;
    printf("Queue: Front ->");
    while(temp != NULL)
    {
        printf(" %d", temp->data);
        temp = temp->next;
    }
    printf(" <- Rear\n");
}

// ---------- MAIN ----------

int main(void)
{
    struct Queue q;
    struct Node *temp;
    int choice, value;

    initQueue(&q);

    while(1)                        // loop forever, so the menu keeps coming back
    {
        printf("\n1.Enqueue  2.Dequeue  3.Peek  4.Display\n");
        printf("5.Size     6.Is Empty 7.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);       // read the user's choice

        switch(choice)              // jump to the matching case
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                enqueue(&q, value);
                break;
            case 2:
                dequeue(&q);
                break;
            case 3:
                peek(&q);
                break;
            case 4:
                display(&q);
                break;
            case 5:
                printf("Queue size: %d\n", size(&q));
                break;
            case 6:
                if(isEmpty(&q))
                    printf("Queue is empty\n");
                else
                    printf("Queue is not empty\n");
                break;
            case 7:
                while(q.front != NULL)  // free the remaining nodes
                {
                    temp = q.front;
                    q.front = q.front->next;
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
Choice 4:   Queue: Front -> 10 20 30 <- Rear
Choice 3:   Front element: 10
Choice 5:   Queue size: 3
Choice 2:   Dequeued 10
Choice 4:   Queue: Front -> 20 30 <- Rear
Choice 6:   Queue is not empty
Choice 2:   Dequeued 20
Choice 2:   Dequeued 30
Choice 6:   Queue is empty
Choice 2:   Queue underflow! Cannot dequeue.
Choice 3:   Queue is empty! Nothing to peek.
Choice 4:   Queue is empty
Choice 5:   Queue size: 0
Choice 12:  Invalid choice
Choice 7:   (frees the list and exits)
