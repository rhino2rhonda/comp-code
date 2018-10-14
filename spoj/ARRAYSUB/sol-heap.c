#include <stdio.h>

int inp(){
	char c;
	while((c=getchar_unlocked()) < '0' || c > '9');
	int num = c - '0';
	while((c=getchar_unlocked()) >= '0' && c <= '9') num = num*10 + c - '0';
	return num;
}

struct node {
	int val;
	int i;
	int hi;
};

void correctNodeUp(struct node* H[], int k, int hi){
	while(1){
		int par = (hi-1)/2;
		if (par < 0 || H[par]->val >= H[hi]->val) break;
		struct node* temp = H[par];
		H[par] = H[hi];
		H[par]->hi = par;
		H[hi] = temp;
		H[hi]->hi = hi;
		hi = par;
	}
}

void correctNodeDown(struct node* H[], int k, int hi){
	while(1) {
		int childL = 2*hi + 1;
		if (childL >= k) break;
		int childMax = childL;
		int childR = childL + 1;
		if (childR < k) {
			childMax = H[childR]->val > H[childL]->val ? childR : childL;
		}
		if (H[hi]->val >= H[childMax]->val) break;
		struct node* temp = H[hi];
		H[hi] = H[childMax];
		H[hi]->hi = hi;
		H[childMax] = temp;
		H[childMax]->hi = childMax;
		hi = childMax;
	}
}

void correctNode(struct node* H[], int k, int hi) {
	int par = (hi - 1)/2;
	if (par >= 0 && H[par]->val < H[hi]->val) correctNodeUp(H, k, hi);
	else correctNodeDown(H, k, hi);
}

void heapify(struct node A[], struct node* H[], int k){
	for(int i=0; i<k; i++) H[i] = &A[i];
	for(int cur=k-1; cur >= 0; cur--) correctNodeDown(H, k, cur);
	for(int i=0; i<k; i++) H[i]->hi = i;
}

void delNode(struct node* H[], int k, int hi){
	H[hi] = H[--k];
	H[hi]->hi = hi;
	correctNode(H, k, hi);
}

void addNode(struct node* H[], int k, struct node* nd){
	H[k] = nd;
	H[k]->hi = k;
	correctNodeUp(H, k+1, k);
}

void printH(struct node* H[], int size){
	for(int i=0; i<size; i++) printf("%d ", H[i]->val);
	printf("\n");
}

int main(){
	struct node A[100000];
	struct node* H[100000];
	int n = inp();
	for(int i=0; i<n; i++) {
		A[i].val = inp();
		A[i].i = i;
		A[i].hi = -1;
	}
	int k = inp();
	heapify(A, H, k-1);
	for(int i=k-1; i<n; i++){
		addNode(H, k-1, &A[i]);
		printf("%d", H[0]->val);
		if(i<n-1) printf(" ");
		delNode(H, k, A[i-k+1].hi);
	}
	printf("\n");
	return 0;
}