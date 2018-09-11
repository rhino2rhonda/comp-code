// MO's algo based solution for DQUERY - AC

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

void printQueries(struct query Q[], int size){
	for (int i = 0; i < size; ++i){
		printf("pos: %d QL: %d QR: %d\n", Q[i].pos, Q[i].L, Q[i].R);
	}
}

int compareQueries(struct query q1, struct query q2, int blockSize, int byPos){
	if (byPos == 1) return q1.pos < q2.pos ? -1 : 1;
	int q1b = q1.L/blockSize, q2b = q2.L/blockSize;
	if (q1b == q2b) {
		if (q1.R == q2.R) return 0;
		else return q1.R < q2.R ? -1 : 1;
	} else return q1b < q2b ? -1 : 1;
}

void testCompareQueries() {
	int blockSize = 8;

	// Test 1
	struct query Q1 = {.L=1, .R=2, .pos=0};
	struct query Q2 = {.L=1, .R=2, .pos=1};
	if(compareQueries(Q1, Q2, blockSize, 0) != 0) {
		printf("testCompareQueries: Test 1.1 failed\n");
		exit(1);
	}
	if(compareQueries(Q1, Q2, blockSize, 1) != -1 || compareQueries(Q2, Q1, blockSize, 1) != 1) {
		printf("testCompareQueries: Test 1.2 failed\n");
		exit(1);
	}

	// Test 2
	Q1.L=9, Q1.R=1, Q2.L=4, Q2.R=3;
	if(compareQueries(Q1, Q2, blockSize, 0) != 1) {
		printf("testCompareQueries: Test 2 failed\n");
		exit(1);
	}

	// Test 3
	Q1.L=100, Q1.R=20, Q2.L=100, Q2.R=24;
	if(compareQueries(Q1, Q2, blockSize, 0) != -1) {
		printf("testCompareQueries: Test 3 failed\n");
		exit(1);
	}

	printf("testCompareQueries: all tests passed\n");
}

void sortQueries(struct query Q[], int lo, int hi, int blockSize, int byPos) {
	if (hi - lo < 1) return;
	// Partition
	struct query pivot = Q[hi];
	int swap = lo;
	for (int i = lo; i < hi; i++){
		if (compareQueries(Q[i], pivot, blockSize, byPos) < 0) {
			struct query temp = Q[i];
			Q[i] = Q[swap];
			Q[swap++] = temp;
		}
	}
	Q[hi] = Q[swap];
	Q[swap] = pivot;
	// D&Q
	sortQueries(Q, lo, swap-1, blockSize, byPos);
	sortQueries(Q, swap+1, hi, blockSize, byPos);
}

void testSortQueries(){
	int blockSize = 10;
	struct query Q[4];
	Q[0].L = 35; Q[0].R = 4; Q[0].pos = 0;
	Q[1].L = 10, Q[1].R = 10; Q[1].pos = 1;
	Q[2].L = 35, Q[2].R = 2; Q[2].pos = 2;
	Q[3].L = 45, Q[3].R = 20; Q[3].pos = 3;
	struct query Q0 = Q[0], Q1 = Q[1], Q2 = Q[2], Q3 = Q[3];

	// Test 1
	sortQueries(Q, 0, 3, blockSize, 0);
	if(compareQueries(Q[0], Q1, blockSize, 0) != 0 ||
		compareQueries(Q[1], Q2, blockSize, 0) != 0 || 
		compareQueries(Q[2], Q0, blockSize, 0) != 0 || 
		compareQueries(Q[3], Q3, blockSize, 0) != 0){
		printf("testSortQueries: test 1 failed\n");
		exit(1);
	}

	// Test 2
	sortQueries(Q, 0, 3, blockSize, 1);
	if(Q[0].pos != Q0.pos ||
		Q[1].pos != Q1.pos || 
		Q[2].pos != Q2.pos || 
		Q[3].pos != Q3.pos){
		printf("testSortQueries: test 2 failed\n");
		exit(1);
	}

	printf("testSortQueries: all tests passed\n");
}

struct query update_mo(struct query q, struct query mo, int A[], int F[]) {
	while(mo.R < q.R) {
		mo.sol += F[A[++mo.R]]++ == 0 ? 1 : 0;
	}
	while(mo.R > q.R) {
		mo.sol -= F[A[mo.R--]]-- <= 1 ? 1 : 0;
	}
	while(mo.L > q.L) {
		mo.sol += F[A[--mo.L]]++ == 0 ? 1 : 0;
	}
	while(mo.L < q.L){
		mo.sol -= F[A[mo.L++]]-- <= 1 ? 1 : 0;
	}
	return mo;
}

int main(int argc, char const *argv[])
{
	int print = 0;
	int A[30010];
	int F[1000010];
	fill(F, 1000010, 0);
	struct query Q[200010];
	int ans[200010];

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
		if(print) printf("i:%d Q.L:%d Q.R:%d\n", i, Q[i].L, Q[i].R);
	}

	// Sort Queries
	int blockSize = sqrt(n);
	sortQueries(Q, 0, q-1, blockSize, 0);

	// MO's Algo
	struct query mo = {.L=Q[0].L, .R=Q[0].L, .sol=1};
	F[A[Q[0].L]]++;
	for(int i=0; i<q; i++){
		mo = update_mo(Q[i], mo, A, F);
		ans[Q[i].pos] = mo.sol;
	}

	// Solutions
	for (int i = 0; i < q; ++i){
		printf("%d\n", ans[i]);
	}

	return 0;
}

// Test
// int main(int argc, char const *argv[])
// {
// 	testCompareQueries();
// 	testSortQueries();
// 	return 0;
// }