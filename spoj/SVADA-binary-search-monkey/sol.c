// Binary search working solution in C

#include <stdio.h>

int countCocos(int N, int T, int B[], int C[]) {
	int c = 0;
	for(int i=0; i<N; i++) {
		if(T >= B[i]){
			c += 1 + ((T - B[i]) / C[i]);			
		}
	}
	return c;

}

int main() {

	// Input
	int T, N, M;
	int A[100], B[100], C[100], D[100];
	scanf("%d", &T);
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		scanf("%d %d", &A[i], &B[i]);
	}
	scanf("%d", &M);
	for(int i=0; i<M; i++){
		scanf("%d %d", &C[i], &D[i]);
	}

	int lo = 0;
	int hi = T;
	int res = -1;
	while(hi >= lo) {
		int mid = (hi + lo) / 2;
		int cocosA = countCocos(N, mid, A, B);
		int cocosB = countCocos(M, T - mid, C, D);
		// printf("debug %d %d %d %d %d\n", lo, mid, hi, cocosA, cocosB);
		if(cocosA > cocosB) {
			hi = mid - 1;
		} else {
			res = mid;
			lo = mid + 1;
		}
	}
	printf("%d\n", res);
	return 0;
}