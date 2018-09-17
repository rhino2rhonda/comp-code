#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MX 'M'
#define MN 'm'
#define X 'x'
#define MAX_POLY 50

// DS

struct expression {
	int val;
	long long poly[MAX_POLY];
	struct expression* left;
	struct expression* right;
};

void fill(long long A[], int size, int val){
	for (int i = 0; i < size; ++i) A[i] = val;
}

// Input

int inp_num(){
	char c;
	while((c=getchar_unlocked()) < '0' || c > '9');
	int num = c - '0';
	while((c=getchar_unlocked()) >= '0' && c <= '9') {
		num = (num*10) + (c-'0');
	}
	return num;
}

struct expression* inp_exp() {
	int c;
	while((c=getchar_unlocked()) != MX && c != MN && c!= X);
	struct expression* node = (struct expression*) malloc(sizeof(struct expression));
	node->val=c;
	fill(node->poly, MAX_POLY, 0);
	if(c != X){
		node->left = inp_exp();
		node->right = inp_exp();
	}
	return node;
}

void destroy_exp(struct expression* root) {
	if(root->val != X) {
		destroy_exp(root->left);	
		destroy_exp(root->right);	
	}
	free(root);
}

void print_exp(struct expression* root) {
	printf("%c\n", root->val);
	if(root->val == X) return;
	print_exp(root->left);
	print_exp(root->right);
}

// Evaluate

void print_poly(long long poly[]){
	printf("Poly:");
	for(int i=0; i<MAX_POLY; i++){
		if(poly[i] == 0) continue;
		else printf(" %dX%d", poly[i], i+1);
	}
	printf("\n");
}

void gen_poly(struct expression* root) {
	if(root->val == X) root->poly[0] = 1;
	else {
		gen_poly(root->left);
		gen_poly(root->right);
		// for(int i=0; i<MAX_POLY; i++){
		// 	for(int j=0; j<MAX_POLY; j++){
		// 		if(i+j >= MAX_POLY) continue;
		// 		// printf("%d %d %d %d\n", i, j, root->left->poly[i], root->right->poly[j]);
		// 		root->poly[i+j+1] += root->left->poly[i] * root->right->poly[j];
		// 		// printf("%d %d %d\n", i, j, root->poly[i+j+1]);
		// 	}			
		// }
		int idx_left[MAX_POLY], idx_right[MAX_POLY];
		int size_left=0, size_right=0;
		for (int i=0; i<MAX_POLY; i++) if(root->left->poly[i] != 0) idx_left[size_left++]=i;
		for (int i=0; i<MAX_POLY; i++) if(root->right->poly[i] != 0) idx_right[size_right++]=i;
		for(int i=0; i<size_left; i++){
			for(int j=0; j<size_right; j++){
				root->poly[idx_left[i]+idx_right[j]+1] += root->left->poly[idx_left[i]] * root->right->poly[idx_right[j]];
			}			
		}
		if(root->val == MN) {
			for(int i=0; i<MAX_POLY; i++){
				root->poly[i] = root->left->poly[i] + root->right->poly[i] - root->poly[i];
			}
		}
	}
}

long double expectation(long long poly[]){
	long double res = 0;
	for(int i=0; i<MAX_POLY; i++){
		if(poly[i] == 0) continue;
		res += ((long double) poly[i]) / (i+2);
	}
	return 1-res;
}

// Main

int main() {

	int T = inp_num();
	for(int i=0; i<T; i++){
		struct expression* e = inp_exp();
		gen_poly(e);
		printf("%0.20Lf\n", expectation(e->poly));
		destroy_exp(e);
	}

	return 0;
}