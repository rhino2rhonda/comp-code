// https://practice.geeksforgeeks.org/problems/geek-collects-the-balls/0/?ref=self
// https://www.spoj.com/problems/ANARC05B/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NM 1000
#define EMPTY -123456

int inp() {
	char c;
	while (((c=getchar_unlocked()) < '0' || c > '9') && c!='-');
	int sign = c == '-' ? -1 : 1;
	int num = c == '-' ? 0 : c - '0';
	while ((c=getchar_unlocked()) >= '0' && c <= '9') num = (num*10) + (c - '0');
	return num*sign;
}

typedef struct ll_node {
	int val;
	struct ll_node* next;
	struct ll_node* prev;
} LLNode;

typedef struct {
	LLNode* head;
	LLNode* tail;
	int size;
} LL;

LL* addToLLTail(LL* list, int val) {
	// Create the tail node
	LLNode* node = (LLNode*) malloc(sizeof(LLNode));
	node->val = val;
	node->next = NULL;
	node->prev = NULL;

	// Create tree if required
	if (list == NULL) {
		list = (LL*) malloc(sizeof(LL));
		list->head = node;
		list->tail = node;
		list->size = 1;
		return list;
	}

	// Add to tail
	node->prev = list->tail;
	list->tail->next = node;
	list->tail = node;
	list->size += 1;
	return list;
}

void printLL(LL* list) {
	if (list == NULL) {
		printf("Empty List\n");
		return;
	}
	LLNode* node = list->head;
	while(node != NULL) {
		printf("%d ", node->val);
		node = node->next;
	}
	printf("\n");
}

typedef struct tree {
	int val;
	int res;
	struct tree* left;
	struct tree* right;
} Tree;

Tree* newTreeNode(int val) {
	Tree* node = (Tree*) malloc(sizeof(Tree));
	node->val = val;
	node->res = EMPTY;
	node->left = NULL;
	node->right = NULL;
	return node;
}

Tree* mergeLL(LL* lla, LL* llb) {
	// Create dummy root
	Tree* root = newTreeNode(0);

	LLNode* node_a = lla->head;
	LLNode* node_b = llb->head;
	Tree* tree_a = root;
	Tree* tree_b = root;
	while(node_a != NULL || node_b != NULL) {
		if (node_b == NULL || (node_a != NULL && node_a->val < node_b->val)) {
			tree_a->left = newTreeNode(node_a->val);
			tree_a = tree_a->left;
			node_a = node_a->next;
		} else if (node_a == NULL || node_a->val > node_b->val) {
			tree_b->right = newTreeNode(node_b->val);
			tree_b = tree_b->right;
			node_b = node_b->next;
		} else {
			tree_a->left = newTreeNode(node_a->val);
			tree_a = tree_a->left;
			tree_b->right = tree_a;
			tree_b = tree_a;
			node_a = node_a->next;
			node_b = node_b->next;
		}
	}

	return root;
}

void printTree(Tree* root, int tabs) {
	if (tabs == 1) printf("\t");
	if (tabs == 2) printf("\t\t");
	if (root == NULL) {
		printf("NULL\n");
	} else {
		printf("%d\n", root->val);
		printTree(root->left, 0);
		printTree(root->right, 2);
	}
}

int dp_max_gold(Tree* tree) {
	if (tree == NULL) return 0;
	if (tree->res != EMPTY) {
		return tree->res;
	}
	
	int lval = dp_max_gold(tree->left);
	int rval = dp_max_gold(tree->right);
	tree->res = tree->val + (lval > rval ? lval : rval);

	return tree->res;
}

int main() {
	while(1) {
		int n=inp();
		if (n==0) break;

		LL *lla = NULL, *llb = NULL;
		for(int i=0; i<n; i++) lla = addToLLTail(lla, inp());

		int m=inp();
		for(int i=0; i<m; i++) llb = addToLLTail(llb, inp());

		Tree* tree = mergeLL(lla, llb);
		printf("%d\n", dp_max_gold(tree));

	}
	return 0;
}