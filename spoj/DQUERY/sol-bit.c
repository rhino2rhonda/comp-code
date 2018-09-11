// BIT solution for Dquery - NZEC

#include <stdio.h>

#define MAX_N 30010
#define MAX_Q 200010
#define MAX_NUM 1000010

int fill(int A[], int size, int val){
	for (int i=0; i<size; i++){
		A[i] = val;
	}
}

void print_bit(int BIT[], int size){
	for(int i=0; i<size; i++) {
		printf("%d %d\n", i, BIT[i]);
	}
}

void update_bit(int BIT[], int max, int idx, int val) {
	for (; idx<=max; idx += idx & -idx) {
		BIT[idx -1] += val;
	}
}

int query_bit(int BIT[], int idx) {
	int sum=0;
	for (; idx >= 1; idx -= idx & -idx) {
			sum += BIT[idx-1];
	}
	return sum;
}

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

struct query {
	int pos;
	int L;
	int R;
};

void sortQueries(struct query Q[], int lo, int hi) {
	if (hi - lo < 1) return;
	// Partition
	struct query pivot = Q[hi];
	int swap = lo;
	for (int i = lo; i < hi; i++){
		if (Q[i].R < pivot.R) {
			struct query temp = Q[i];
			Q[i] = Q[swap];
			Q[swap++] = temp;
		}
	}
	Q[hi] = Q[swap];
	Q[swap] = pivot;
	// D&Q
	sortQueries(Q, lo, swap-1);
	sortQueries(Q, swap+1, hi);
}

void printQueries(struct query Q[], int size){
	for (int i = 0; i < size; ++i){
		printf("pos: %d QL: %d QR: %d\n", Q[i].pos, Q[i].L, Q[i].R);
	}
}

void main() {
	int print = 0;

	int A[MAX_N];
	int BIT[MAX_N];
	fill(BIT, MAX_N, 0);
	
	int LI[MAX_NUM];
	fill(LI, MAX_NUM, -1);
	
	struct query Q[MAX_Q];
	int ans[MAX_Q];

	// Read Array
	int n = inp();
	if(print) printf("n:%d\n", n);
	for(int i=0; i<n; i++){
		A[i] = inp();
		if(print) printf("i:%d val:%d\n", i, A[i]);
	}

	// Read Queries
	int q = inp();
	if(print) printf("q:%d\n", q);
	for(int i=0; i<q; i++){
		Q[i].pos=i;
		Q[i].L=inp()-1;
		Q[i].R=inp()-1;
		if(print) printf("pos:%d Q.L:%d Q.R:%d\n", Q[i].pos, Q[i].L, Q[i].R);
	}


	// Sort Queries
	sortQueries(Q, 0, q-1);

	// Offline BIT
	int cq =0;
	for (int i=0; i<n; i++) {
		if (LI[A[i]] != -1) {
			update_bit(BIT, MAX_N, LI[A[i]]+1, -1);
		}
		LI[A[i]] = i;
		update_bit(BIT, MAX_N, i+1, 1);
		while (Q[cq].R == i) {
			ans[Q[cq].pos] = Q[cq].R < Q[cq].L ? 0: query_bit(BIT, Q[cq].R+1) - query_bit(BIT, Q[cq].L);
			cq++;
		}
	}

	for (int i = 0; i < q; ++i){
		printf("%d\n", ans[i]);
	}
}