#define _CTR_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 2

typedef struct tree {
	char* value;
	unsigned int size;
	struct tree** child;
} TREE;

TREE* CreateNode(const char* val, unsigned int size)
{
	TREE* new_node = (TREE*)malloc(sizeof(TREE));
	new_node->value = (char*)malloc(sizeof(char) * (strlen(val) + 1));
	//strcpy(new_node->value, value);
	for (int i = 0; i < strlen(val); i++) {
		char s = val[i];
		new_node->value[i] = s;
	}
	new_node->value[strlen(val)] = '\0';
	new_node->size = size;
	new_node->child = (TREE**)malloc(sizeof(TREE) * new_node->size);
	for (unsigned int i = 0; i < new_node->size; i++)
		*(new_node->child + i) = NULL;
	return (new_node);
}

TREE* found_node;

void ScanTree(TREE* node)
{
	if (node == NULL)
		return;
	for (unsigned int i = 0; i < node->size; i++)
		if (node->child[i] == NULL) {
			if (found_node == NULL) {
				found_node = node;
				break;
			}
			else {
				if (node->size < found_node->size) {
					found_node = node;
					break;
				}
			}
		}
	for (unsigned int i = 0; i < node->size; i++)
		ScanTree(node->child[i]);
	return;
}

TREE* InsertNode(TREE* root, const char* value)
{
	TREE* new_node = NULL;
	if (root == NULL) {
		root = CreateNode(value, N);
		return root;
	}
	found_node = NULL;
	ScanTree(root);
	new_node = CreateNode(value, found_node->size * 2);
	for (unsigned int i = 0; i < found_node->size; i++)
		if (found_node->child[i] == NULL) {
			found_node->child[i] = new_node;
			break;
		}
	return new_node;
}


void print(TREE* root, int lvl) {
	if (root == NULL) return;
	printf("%s, %d\n", root->value, lvl);
	for (int i = 0; i < root->size; i++)
		print(root->child[i], lvl + 1);

}

int main(void)
{
	int lvl = 0;
	TREE* root = NULL;
	root = InsertNode(root, "root");
	InsertNode(root, "child_1");
	InsertNode(root, "child_2");
	InsertNode(root, "child_3");
	InsertNode(root, "child_4");
	InsertNode(root, "child_5");
	InsertNode(root, "child_6");
	print(root, lvl);
}
