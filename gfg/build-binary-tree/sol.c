#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10000

int inp(){
	char c;
	while((c=getchar_unlocked())<'0' || c >'9');
	int num = c - '0';
	while((c=getchar_unlocked())>='0' && c<='9') num = num*10 + c - '0';
	return num;
}

struct btree {
	int val;
	struct btree* left;
	struct btree* right;
};

struct btree* newBtree(int val){
	struct btree* b = malloc(sizeof(struct btree));
	b->val = val;
	b->left = b->right = NULL;
	return b;
}

struct buildBtreeState {
	int preCur;
};

struct btree* buildBtree(int in[], int pre[], int inStrt, int inEnd, struct buildBtreeState* state){
	// printf("dbg: inStrt:%d inEnd:%d, preCur:%d\n", inStrt, inEnd, state->preCur);
	struct btree* b = newBtree(pre[state->preCur++]);
	if (inEnd <= inStrt) return b;
	int inCur;
	for(inCur=inStrt; inCur <= inEnd; inCur++) if(b->val == in[inCur]) break;
	if(inCur > inEnd) {
		printf("IN node not found: %d\n", b->val);
		exit(1);
	}
	if (inCur > inStrt) b->left = buildBtree(in, pre, inStrt, inCur-1, state);
	if (inCur < inEnd) b->right = buildBtree(in, pre, inCur+1, inEnd, state);
	return b;
}

int checkPostOrder(struct btree* b, int post[], int postCur){
	// printf("dbg: postCur:%d\n", postCur);
	if (b == NULL) return postCur;
	postCur = checkPostOrder(b->left, post, postCur);
	postCur = checkPostOrder(b->right, post, postCur);
	return b->val == post[postCur] ? postCur + 1: postCur;
}

int main(int argc, char const *argv[])
{
	int in[MAX_SIZE];
	int pre[MAX_SIZE];
	int post[MAX_SIZE];

	int t = inp();
	// printf("tc:%d\n", t);
	while(t--){
		int size = inp();
		// printf("size:%d\n", size);
		if(size > MAX_SIZE){
			printf("Max size exceeded: %d\n", size);
			exit(1);
		}
		for(int i=0; i<size; i++) in[i] = inp();
		// for(int i=0; i<size; i++) printf("%d ", in[i]);
		// printf("\n");
		for(int i=0; i<size; i++) pre[i] = inp();
		// for(int i=0; i<size; i++) printf("%d ", pre[i]);
		// printf("\n");
		for(int i=0; i<size; i++) post[i] = inp();
		// for(int i=0; i<size; i++) printf("%d ", post[i]);
		// printf("\n");
		struct buildBtreeState state = {.preCur=0};
		struct btree* b = buildBtree(in, pre, 0, size-1, &state);
		printf("%s\n", checkPostOrder(b, post, 0) == size ? "CORRECT": "INCORRECT");
	}
	return 0;
}