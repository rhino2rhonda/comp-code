#include <stdio.h>
#include <stdlib.h>

struct node {
	int key;
	int count;
	int rightCount;
	int leftHeight;
	int rightHeight;
	struct node* parent;
	struct node* left;
	struct node* right;
};

int A[200000];
struct node nodes[200000];

int currNode = 0;
struct node* new_node(struct node* parent, int key) {
	struct node* nd = &nodes[currNode++];
	nd->key = key;
	nd->count = 1;
	nd->rightCount = 0;
	nd->leftHeight = 0;
	nd->rightHeight = 0;
	nd->parent = parent;
	nd->left = NULL;
	nd->right = NULL;
	return nd;
}

int getHeight(struct node* bst) {
	if (bst == NULL) return 0;
	return 1 + (bst->leftHeight > bst->rightHeight ? bst->leftHeight : bst->rightHeight);
}

struct node* rotate(struct node* bst) {
	int leftHeavy = bst->leftHeight - bst->rightHeight > 1 ? 1 : 0;

	struct node* temp1 = leftHeavy ? bst->left: bst->right;
	if(temp1 == NULL) {
		printf("subtree cannot be NULL here\n");
		exit(1);
	}
	struct node* temp2 = leftHeavy ? temp1->right: temp1->left;

	// Bring up temp2
	if (leftHeavy) {
		bst->left = temp2;
		bst->leftHeight = getHeight(temp2);
	} else {
		bst->right = temp2;
		bst->rightHeight = getHeight(temp2);
		bst->rightCount = temp2 == NULL ? 0 : temp2->count + temp2->rightCount;
	}
	if (temp2 != NULL){
		temp2->parent = bst;
	}

	// Bring up temp1
	if (leftHeavy) {
		temp1->right = bst;
		temp1->rightHeight = getHeight(bst);
		temp1->rightCount = bst->count + bst->rightCount;
	} else {
		temp1->left = bst;
		temp1->leftHeight = getHeight(bst);
	}

	temp1->parent = bst->parent;
	if (bst->parent != NULL) {
		struct node** childLink = bst->parent->left == bst ? &(bst->parent->left): &(bst->parent->right);
		int* childHeightLink = bst->parent->left == bst ? &(bst->parent->leftHeight): &(bst->parent->rightHeight);
		*childLink = temp1;
		*childHeightLink = getHeight(temp1);
	}
	bst->parent=temp1;

	return temp1;
}

void print_tree(struct node* bst, int depth) {
	if (bst == NULL) return;
	for(int i=0; i<depth; i++){
		printf("\t");
	}
	printf("k:%d  c:%d  rc:%d  lh:%d  rh:%d\n", bst->key, bst->count, bst->rightCount, bst->leftHeight, bst->rightHeight);
	for(int i=0; i<depth; i++){
		printf("\t");
	}
	printf("LEFT\n");
	print_tree(bst->left, depth+1);
	for(int i=0; i<depth; i++){
		printf("\t");
	}
	printf("RIGHT\n");
	print_tree(bst->right, depth+1);
}

long int add_node(struct node** bst, int key) {
	struct node* root = *bst;
	if(root == NULL) {
		printf("BST should never be NULL\n");
		exit(1);
	}

	long int inv=0;

	if(key == root->key) {
		root->count += 1;
	} else {
		// Choose subtree
		struct node** next;
		int* nextHeight;
		if (root->key > key) {
			next = &(root->left);
			nextHeight = &(root->leftHeight);
			inv += root->count + root->rightCount;
		}
		else {
			next = &(root->right);
			root->rightCount += 1;
			nextHeight = &(root->rightHeight);
		}

		// Add leaf or recurse into subtree
		if (*next == NULL) {
			*next = new_node(root, key);
		} else {
			inv += add_node(next, key);
		}

		// Update height of subtree
		*nextHeight = getHeight(*next);

		// Rotate imbalanced node
		int balance = abs(root->leftHeight - root->rightHeight);
		while(balance > 1) {
			*bst = rotate(*bst);
			balance--;
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
	currNode = 0;
	struct node* bst = new_node(NULL, A[0]);
	for (int i=1; i<size; i++) {
		inv += add_node(&bst, A[i]);
	}
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