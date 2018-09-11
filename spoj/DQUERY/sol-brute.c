#include <stdio.h>
#include <math.h>

#define MAX_N 30010
#define MAX_Q 200010
#define MAX_NUM 1000010

int inp() {
	int ch;
	do {
		ch = getchar_unlocked();
	}
	while(ch < '0' || ch > '9');

	int n=0;
	do{
		n *= 10;
		n += ch - '0';
		ch = getchar_unlocked();
	} while(ch >= '0' && ch <= '9');
	return n;
}

int fill(int A[], int size, int val){
	for (int i=0; i<size; i++){
		A[i] = val;
	}
}

struct query {
	int pos;
	int L;
	int R;
	int sol;
};


void main() {
	int A[MAX_N];
	int F[MAX_NUM];
	struct query Q[MAX_Q];

	// Read Array
	int n = inp();
	for(int i=0; i<n; i++) A[i] = inp();

	// Read Queries
	int q = inp();
	for(int i=0; i<q; i++){
		Q[i].L=inp()-1;
		Q[i].R=inp()-1;
	}

	// Process Queries
	for(int i=0; i<q; i++){
		fill(F, MAX_NUM, 0);
		int d=0;
		for(int j=Q[i].L; j<=Q[i].R; j++) if(F[A[j]]++ == 0) d++;
		printf("%d\n", d);
	}
}