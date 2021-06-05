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

int main()
{
	Node *root = NULL;
	int rc, N = 7;
	const char *msgs[] = {"0. Quit","1. Add","2. Find","3. Find max","4. Delete","5. Show table","6. Show tree"};
	Node *(*fptr[])(Node*) = {NULL, T_Add, T_Find, T_MaxNode, T_Delete, T_ShowTable, T_ShowTree};
	while(rc = dialog(msgs, N))
	    root = fptr[rc](root);
	printf("Good Bye!\n");
	deltree(root);
	return 0;
}

Node *find (Node *root, int key) {
    Node *ptr = root;
    while (ptr != NULL){
        if (ptr->key == key)
            return ptr;
        else if (ptr->key > key)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    return 0;
}

Node *minNode (Node *ptr) {
    if (ptr == NULL)
        return 0;
    else 
        while (ptr->left != NULL)
                ptr = ptr->left;
    return ptr;
}

Node *maxNode (Node *ptr) {
    if (ptr == NULL)
        return 0;
    else 
        while (ptr->right != NULL)
                ptr = ptr->right;
    return ptr;
}

Node *nextNode (Node *x) {
    Node *ptr = NULL;
    if (x == NULL)
        return 0;
    if (x->right != NULL){
        ptr = minNode(x->right);
        return ptr;
    }
    ptr = x->parent;
    while (ptr != NULL && x == ptr->right){
        x = ptr;
        ptr = x->parent;
    }
    return ptr;
}

Node *insert (Node *root, int key) {
    Node *ptr, *x, *par;
    ptr = root;
    par  = 0;
    x = (Node *) calloc (1, sizeof(Node));
    if (ptr == NULL){
        x->key = key;
        ptr = x;
        return ptr;
    }
    while (ptr != NULL){
        par = ptr;
        if (ptr->key > key)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    if (par->key > key){
        par->left = x;
        x->key = key;
    }
    else {
        par->right = x;
        x->key = key;
    }
    return root;
}

Node* delete(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = delete(root->left, key);
    else if (key > root->key)
        root->right = delete(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = minNode(root->right);
        root->key = temp->key;
        root->right = delete(root->right, temp->key);
    }
    return root;
}


void deltree(Node *p)
{
	if (p != NULL) {
		deltree(p->left);
		deltree(p->right);
		free(p);
	}
}

int dialog (const char *msgs[], int N){
    const char *errmsg = "";
	int rc,i,n;
	do{
		puts(errmsg);
		errmsg = "Wrong input! Please, repeat!";
		for (i = 0; i < N; ++i)
            puts(msgs[i]);
		puts("Make your choice:-->");
		n = getInt(&rc);
		if(n==0)
            rc = 0;
	} while (rc < 0 || rc >= N);
	return rc;
}

Node *T_Add (Node *root){
	int k, n = 1;
	char *info;
	printf("Enter key:-->");
	n = getInt(&k);
	if (find(root, k) == 0) {
		root = insert(root, k);
		puts("ADD");
	}
	else puts("ERROR! KEY EXISTS");
	return root;
}

Node *T_Find (Node *root){
	Node *x = NULL;
	int k, n = 1;
	printf("Enter key:-->");
	n = getInt(&k);
	x = find(root, k);
	if (x != 0) {
		puts("FIND");
		printf("%d \n", x->key);
	}
	else  puts("KEY NOT FOUND");
	return root;
}

Node *T_Delete (Node *root){
	Node *x = NULL;
	int k, n = 1;
	printf("Enter key:-->");
	n = getInt(&k);
	x = find(root, k);
	if (x != 0) {
		root = delete(root, k);
		puts("DELETED");
	}
	else  puts("KEY NOT FOUND");
	return root;
}

Node *T_MaxNode (Node *root){
	Node *x;
    if (root == NULL)
        return 0;
	x = maxNode(root);
	puts("FIND MAX");
	printf("%d \n", x->key);
	return root;
}

Node *T_ShowTable (Node *root)
{   
	if (root == NULL)
        return 0;
    T_ShowTable(root->right);
    printf("\n");
    printf("  ");
    printf("%d\n", root->key);
    T_ShowTable(root->left);
    return root;
}

void ShowTree (Node *root, int flag) {
    flag += 5;
	if (root == NULL)
        return;
    ShowTree(root->right, flag);
    printf("\n");
    for(int i = 0; i < flag; ++i)
        printf(" ");
    printf("%d\n", root->key);
    ShowTree(root->left, flag);
}

Node *T_ShowTree (Node *root){
    ShowTree(root, 0);
    return root;
}

int getInt (int *a) {
    int n;
    do {
        n = scanf("%d", a);
        if (n < 0)
            return 0;
        else if (n == 0){
            printf("Wrong input! Please repeat!\n");
            scanf("%*c");
        }
    } while (n == 0);
    return 1;
}
