// Program to print binary tree in 2D 
#include<stdio.h> 
#include<malloc.h> 
#include <string.h>
#define COUNT 10 
  
// A binary tree node 
struct Node 
{ 
    char *data; 
    struct Node* left, *right; 
}; 
  
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
    if(token[0] == '-' && token[1] == 0){
        return 1;
    }
    if(token[0] == '+' && token[1] == 0){
        return 1;
    }
    if(token[0] == '/' && token[1] == 0){
        return 1;
    }
    if(token[0] == '*' && token[1] == 0){
        return 1;
    }
    return 0;
}

struct Node* construct_tree(char *token, int *index){
    if(token[*index] == 0){
        return NULL;
    }
    char *data = token + *index;
    while(token[*index] != ' ' && token[*index] != 0){
        (*index)++;
    }
    token[*index] = 0;
    (*index)++;

    struct Node *node = newNode(data);
    
    if(isOperator(data)) {
        node->left = construct_tree(token, index);
        node->right = construct_tree(token, index);
    }


    return node;
}

// Driver program to test above functions 
int main() 
{  
    char *token = malloc(20);
    strcpy(token, "+ + -659597 -949003 158677");
    int index = 0;
    struct Node *root = construct_tree(token, &index);
    print2D(root); 
  
    return 0; 
} 