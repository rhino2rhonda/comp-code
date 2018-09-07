#include <stdio.h>
#include <stdlib.h>

int A[200000];

struct node {
	int key;
	int count;
	int rightCount;
	struct node* left;
	struct node* right;
};

struct node* new_node(int key) {
	struct node* nd = (struct node*) malloc(sizeof(struct node));
	nd->key = key;
	nd->count = 1;
	nd->rightCount = 0;
	nd->left = NULL;
	nd->right = NULL;
	return nd;
}

long int add_node(struct node* bst, int key) {
	//printf("DEBUG: adding key=%d\n", key);
	struct node* root = bst;
	long int inv = 0;
	while(1) {
		//printf("DEBUG: loop begin\n");
		if (root == NULL) {
			printf("Root is NULL! [should not happen ever]\n");
			exit(1);
		}
		//printf("DEBUG: curr root: key=%d, count=%d, rightCount=%d\n", root->key, root->count, root->rightCount);
		//printf("DEBUG: right subtree is NULL:%s\n", root->right == NULL ? "true": "false");
		//printf("DEBUG: left subtree is NULL:%s\n", root->left == NULL ? "true": "false");
		// Key matches
		if (root->key == key) {
			//printf("DEBUG: key matched\n");
			root->count += 1;
			break;
		}
		
		// Select subtree and count inversions
		struct node** next;
		if (root->key > key) {
			next = &(root->left);
			inv += root->count + root->rightCount;
			//printf("DEBUG: inv updated=%d\n", inv);
		} else {
			next = &(root->right);
			root->rightCount += 1;
			//printf("DEBUG: rightCount updated=%d\n", root->rightCount);
		}
		
		// Add leaf or recurse
		if (*next == NULL) {
			//printf("DEBUG: adding leaf\n");
			*next = new_node(key);
			//printf("DEBUG: next is NULL:%s\n", *next == NULL ? "true": "false");
			//printf("DEBUG: right subtree is NULL:%s\n", root->right == NULL ? "true": "false");
			//printf("DEBUG: left subtree is NULL:%s\n", root->left == NULL ? "true": "false");
			break;
		} else {
			//printf("DEBUG: check subtree\n");
			root = *next;
		}
	}
	return inv;
}

void destroy_BST(struct node* bst) {
	if (bst == NULL) return;
	if (bst->left != NULL) destroy_BST(bst->left);
	if (bst->right != NULL) destroy_BST(bst->right);
	free(bst);
}

long int count_inversions(int A[], int size) {
	if (size <= 0) return 0;
	long int inv = 0;
	struct node* bst = new_node(A[0]);
	for (int i=1; i<size; i++) {
		inv += add_node(bst, A[i]);
	}
	destroy_BST(bst);
	return inv;
}

int main() {
	int T, N;
	scanf("%d", &T);
	for (int t=0; t<T; t++){
		scanf("\n%d", &N);
		for (int i=0; i<N; i++){
			scanf("%d", &A[i]);
		}
		printf("%ld\n", count_inversions(A, N));
	}
	return 0;
}