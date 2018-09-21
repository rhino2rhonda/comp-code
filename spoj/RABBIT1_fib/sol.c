#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct calc {
	int pos;
	int m;
	int n;
	int mod;
};

struct fib_res {
	int i;
	int a;
	int b;
	int c;
};

int inp(){
	char c;
	while((c=getchar_unlocked()) < '0' || c > '9');
	int n=c-'0';
	while((c=getchar_unlocked()) >= '0' && c <= '9') n = (n*10)+(c-'0');
	return n;
}

int get_reps(int mod){
	return (mod * 3) / 2;
}

struct fib_res* fibn(int n, struct fib_res* fib){
	int mod = (int) pow(2, 20);
	if (fib == NULL){
		fib = malloc(sizeof(struct fib_res));
		fib->i = 2;
		fib->a = fib->b = fib->c = 1;
	}
	for(; fib->i<= n; fib->i++){
		fib->c = (fib->a+fib->b) % mod;
		fib->a = fib->b;
		fib->b = fib->c;
	}
	return fib;
}

void sort(struct calc C[], int lo, int hi){
	if (hi<=lo) return;
	struct calc pivot = C[hi], temp;
	int mid = lo;
	for(int i=lo; i<hi; i++){
		if(C[i].n < pivot.n){
			temp = C[mid];
			C[mid++] = C[i];
			C[i] = temp;
		}
	}
	C[hi] = C[mid];
	C[mid] = pivot;

	sort(C, lo,  mid-1);
	sort(C, mid+1, hi);
}

int main(){
	struct calc C[1000];
	int res[1000];
	int t = inp();
	for(int i=0; i<t; i++){
		C[i].pos = i;
		C[i].n = inp();
		C[i].m = inp();
		C[i].mod = (int)pow(2, C[i].m);
		C[i].n = C[i].n % get_reps(C[i].mod);
	}
	sort(C, 0, t-1);
	struct fib_res* fib = NULL;
	for(int i=0; i<t; i++){
		fib = fibn(C[i].n, fib);
		res[C[i].pos] = fib->c % C[i].mod;
	}
	for(int i=0; i<t; i++){
		printf("%d\n", res[i]);
	}

	return 0;
}