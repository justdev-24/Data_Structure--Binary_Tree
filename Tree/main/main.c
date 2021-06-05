#include "header.h"

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
