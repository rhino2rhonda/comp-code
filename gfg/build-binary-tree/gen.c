#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int genRandInt(int start, int end, int* hash){
	while (1){
		int val = start + (((float) rand())*(end-start)/RAND_MAX);
		if (hash == NULL) return val;
		if (hash[val] == 0) {
			hash[val] = 1;
			return val;
		}
	}
}

int* newHash(){
	int* hash = malloc(sizeof(int)*1000001);
	for(int i=0; i<1000001; i++) hash[i] = 0;
	return hash;
}

struct btree {
	int val;
	int size;
	struct btree* left;
	struct btree* right;
};

struct btree* newBtree(int val){
	struct btree* b = malloc(sizeof(struct btree));
	b->val = val;
	b->size = 1;
	b->left = b->right = NULL;
	return b;
}

struct btree* genFullBtree(int h, int* hash){
	if (h == 0) return NULL;
	struct btree* b = newBtree(genRandInt(1, 1000000, hash));
	b->left = genFullBtree(h-1, hash);
	b->size += b->left == NULL ? 0 : b->left->size;
	b->right = genFullBtree(h-1, hash);
	b->size += b->right == NULL ? 0 : b->right->size;
	return b;
}

struct btree* genIncompleteBtree(int h, int* hash){
	if (h == 0) return NULL;
	struct btree* b = newBtree(genRandInt(1, 1000000, hash));
	b->left = genRandInt(1, 10, NULL) > 3 ? genFullBtree(h-1, hash) : NULL;
	b->size += b->left == NULL ? 0 : b->left->size;
	b->right = genRandInt(1, 10, NULL) > 3 ? genFullBtree(h-1, hash): NULL;
	b->size += b->right == NULL ? 0 : b->right->size;
	return b;
}

void postOrder(struct btree* b){
	if(b == NULL) return;
	postOrder(b->left);
	postOrder(b->right);
	printf("%d ", b->val);
}

void preOrder(struct btree* b){
	if(b == NULL) return;
	printf("%d ", b->val);
	preOrder(b->left);
	preOrder(b->right);
}

void inOrder(struct btree* b){
	if(b == NULL) return;
	inOrder(b->left);
	printf("%d ", b->val);
	inOrder(b->right);
}

void main() {
	srand(time(NULL));
	int tc = 20;
	printf("%d\n", tc);
	while(tc--){
		int h = genRandInt(6, 12, NULL);
		// int size = pow(2,h)-1;
		int* hash = newHash();
		// struct btree* b = genFullBtree(h, hash);
		struct btree* b = genIncompleteBtree(h, hash);
		free(hash);
		printf("%d\n", b->size);
		inOrder(b);
		printf("\n");
		preOrder(b);
		printf("\n");
		postOrder(b);
		printf("\n");
	}
	
}