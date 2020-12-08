// Program to print binary tree in 2D 
#include<stdio.h> 
#include<malloc.h> 
#include <string.h>
#define COUNT 10 
  
char delim[] = " \n";

struct Node 
{ 
    char *data; 
    struct Node* left, *right; 
}; 
  
// A structure to represent a stack
struct Stack {
    int top;
    unsigned capacity;
    struct Node** array;
};
 
// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct Node**)malloc(stack->capacity * sizeof(struct Node*));
    return stack;
}
 
// Stack is full when top is equal to the last index
int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}
 
// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}
 
// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, struct Node* item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}
 
// Function to remove an item from stack.  It decreases top by 1
struct Node *pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return 0;
    return stack->array[stack->top--];
}
 
// Function to return the top from stack without removing it
struct Node *peek(struct Stack* stack)
{
    if (isEmpty(stack))
        return 0;
    return stack->array[stack->top];
}

// A binary tree node 
// Helper function to allocates a new node 
struct Node* newNode(char *data) 
{ 
    struct Node* node = malloc(sizeof(struct Node)); 
    node->data = data; 
    node->left = node->right = NULL; 
    return node; 
} 
  
// Function to print binary tree in 2D 
// It does reverse inorder traversal 
void print2DUtil(struct Node *root, int space) 
{ 
    // Base case 
    if (root == NULL) 
        return; 
  
    // Increase distance between levels 
    space += COUNT; 
  
    // Process right child first 
    print2DUtil(root->right, space); 
  
    // Print current node after space 
    // count 
    printf("\n"); 
    for (int i = COUNT; i < space; i++) 
        printf(" "); 
    printf("%s\n", root->data); 
  
    // Process left child 
    print2DUtil(root->left, space); 
} 
  
// Wrapper over print2DUtil() 
void print2D(struct Node *root) 
{ 
   // Pass initial space count as 0 
   print2DUtil(root, 0); 
} 
  

int isOperator(char *token){
    if(token[0] <= '/' && token[1] == 0){
        return 1;
    }
    return 0;
}

struct Node* construct_tree(char *token, int *index){
    struct Stack *stack = createStack(100);
    
    char *p = strtok(token, delim);

    struct Node *root = newNode(p);
    push(stack, root);
    p = strtok(NULL, delim);

    while(p){
        struct Node *last = pop(stack);
        struct Node *new_node = newNode(p);

        if(last->left == NULL){
            last->left = new_node;
            push(stack, last);
        } else {
            last->right = new_node;
        }

        if(isOperator(p)){
            push(stack, new_node);
        }
        
        p = strtok(NULL, delim);
    }
    return root;
}

// Driver program to test above functions 
int main() 
{  
    char *token = malloc(20);
    strcpy(token, "1");
    int index = 0;
    struct Node *root = construct_tree(token, &index);
    print2D(root); 
  
    return 0; 
} 