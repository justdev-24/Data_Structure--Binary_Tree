#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

int getInt (int *);
Node *find (Node *, int);
Node *minNode (Node *);
Node *maxNode (Node *);
Node *nextNode (Node *);
Node *insert (Node *, int);
Node *delete (Node *, Node *);
void deltree(Node *);
int dialog (const char **, int);
Node *T_Add (Node *);
Node *T_Find (Node *);
Node *T_Delete (Node *);
Node *T_ShowTable (Node *);
Node *T_ShowTree (Node *);
void ShowTree (Node *, int);
Node *T_MaxNode (Node *);
