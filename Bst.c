#include <stdio.h>
#include <stdlib.h>

// A node holds a value and the addresses of its left and right children
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

// Create one node
struct Node* createNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if(newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// INSERT: smaller values go left, larger values go right
struct Node* insert(struct Node *root, int value)
{
    if(root == NULL)                    // found the empty place: create the node here
    {
        return createNode(value);
    }
    if(value < root->data)
    {
        root->left = insert(root->left, value);
    }
    else if(value > root->data)
    {
        root->right = insert(root->right, value);
    }
    else
    {
        printf("Duplicate value %d ignored.\n", value);
    }
    return root;
}

// FIND MIN: keep going left until there is no left child
struct Node* findMin(struct Node *root)
{
    while(root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

// DELETE: three cases (no child, one child, two children)
struct Node* deleteNode(struct Node *root, int value)
{
    if(root == NULL)
    {
        printf("Value %d not found!\n", value);
        return NULL;
    }
    if(value < root->data)
    {
        root->left = deleteNode(root->left, value);
    }
    else if(value > root->data)
    {
        root->right = deleteNode(root->right, value);
    }
    else                                // this is the node to delete
    {
        if(root->left == NULL)          // no left child (covers leaf and right-child-only)
        {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        if(root->right == NULL)         // only a left child
        {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }
        struct Node *succ = findMin(root->right);   // two children: find inorder successor
        root->data = succ->data;                    // copy its value here
        root->right = deleteNode(root->right, succ->data);  // delete the successor
    }
    return root;
}

// SEARCH: go left or right until found or NULL
int search(struct Node *root, int value)
{
    while(root != NULL)
    {
        if(value == root->data)
        {
            return 1;
        }
        if(value < root->data)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return 0;
}

// ---------- TRAVERSALS ----------

void inorder(struct Node *root)         // Left, Root, Right (gives sorted order)
{
    if(root == NULL)
    {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(struct Node *root)        // Root, Left, Right
{
    if(root == NULL)
    {
        return;
    }
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct Node *root)       // Left, Right, Root
{
    if(root == NULL)
    {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

// ---------- MAIN ----------

int main(void)
{
    struct Node *root = NULL;
    int choice, value;

    while(1)                            // loop forever, so the menu keeps coming back
    {
        printf("\n1.Insert  2.Delete  3.Search  4.Inorder\n");
        printf("5.Preorder  6.Postorder  7.Find Min  8.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);           // read the user's choice

        switch(choice)                  // jump to the matching case
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if(search(root, value))
                    printf("%d found in tree.\n", value);
                else
                    printf("%d not found in tree.\n", value);
                break;
            case 4:
                if(root == NULL)
                    printf("Tree is empty\n");
                else
                {
                    printf("Inorder   : ");
                    inorder(root);
                    printf("\n");
                }
                break;
            case 5:
                if(root == NULL)
                    printf("Tree is empty\n");
                else
                {
                    printf("Preorder  : ");
                    preorder(root);
                    printf("\n");
                }
                break;
            case 6:
                if(root == NULL)
                    printf("Tree is empty\n");
                else
                {
                    printf("Postorder : ");
                    postorder(root);
                    printf("\n");
                }
                break;
            case 7:
                if(root == NULL)
                    printf("Tree is empty\n");
                else
                    printf("Minimum value: %d\n", findMin(root)->data);
                break;
            case 8:
                return 0;               // the only way out of the loop
            default:
                printf("Invalid choice\n");
        }
    }
}


Output:
Choices 1 with values 50, 30, 70, 20, 40, 60, 80
Choice 4:   Inorder   : 20 30 40 50 60 70 80
Choice 5:   Preorder  : 50 30 20 40 70 60 80
Choice 6:   Postorder : 20 40 30 60 80 70 50
Choice 7:   Minimum value: 20
Choice 1, value 65
Choice 1, value 65:   Duplicate value 65 ignored.
Choice 3, value 60:   60 found in tree.
Choice 3, value 99:   99 not found in tree.
Choice 2, value 50:   (deletes the root, replaced by its successor 60)
Choice 4:   Inorder   : 20 30 40 60 65 70 80
Choice 5:   Preorder  : 60 30 20 40 70 65 80
Choice 2, value 999:  Value 999 not found!
Choice 12:  Invalid choice
Choice 8:   (exits)
