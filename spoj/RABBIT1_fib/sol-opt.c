#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int M1[2][2] = {{1,1},{1,0}};

struct calc {
	int pos;
	int m;
	int n;
	int mod;
};

struct fib_res {
	int n;
	int res[2][2];
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

int modmul(int a, int b, int mod){
	int prod = 0;
	while(b>0){
		if (b%2 == 1) prod = (prod + a) % mod;
		a = (a*2) % mod;
		b = b/2;
	}
	return prod;
}

void matmul(int A[2][2], int B[2][2], int mod){
	int temp[2][2];
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			temp[i][j] = (modmul(A[i][0], B[0][j], mod) + modmul(A[i][1], B[1][j], mod)) % mod;
		}
	}
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			A[i][j] = temp[i][j];
		}
	}
}

void power(int A[2][2], int n, int mod){
	if (n<=1) return;
	power(A, n/2, mod);
	matmul(A,A,mod);
	if(n % 2 == 1) matmul(A, M1, mod);
}

void copy(int A[2][2], int B[2][2]) {
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 2; j++){
			A[i][j] = B[i][j];
		}
	}
}

struct fib_res* fibn(int n, struct fib_res* fib, int mod){
	if (fib == NULL){
		fib = malloc(sizeof(struct fib_res));
		fib->n = 1;
		copy(fib->res, M1);
	}
	if(n > fib->n) {
		int mat[2][2];
		copy(mat, M1);
		power(mat, n-fib->n, mod);
		matmul(fib->res, mat, mod);
		fib->n = n;
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
		int rep = get_reps(C[i].mod);
		C[i].n = C[i].n % rep;
		if (C[i].n == 0) C[i].n = rep; 
	}
	sort(C, 0, t-1);
	struct fib_res* fib = NULL;
	int mod_max = (int) pow(2, 20);
	for(int i=0; i<t; i++){
		fib = fibn(C[i].n, fib, mod_max);
		res[C[i].pos] = fib->res[0][0] % C[i].mod;
	}
	for(int i=0; i<t; i++){
		printf("%d\n", res[i]);
	}

	return 0;
}