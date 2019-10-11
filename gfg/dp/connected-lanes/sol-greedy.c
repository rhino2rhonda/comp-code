#include <stdio.h>

#define MAX_N 100000

int main() {
	while (1) {
		int n, m;
		int N[MAX_N], M[MAX_N];

		scanf("%d", &n);
		if (n==0) break;
		for (int i=0; i<n; i++) scanf("%d", &N[i]);

		scanf("%d", &m);
		for (int i=0; i<m; i++) scanf("%d", &M[i]);

		int C[MAX_N][2];
		int size = 0;
		int sum1=0, sum2=0;
		int i1=0, i2=0;
		while (1) {
			if (i1 >= n && i2 >= m) {
				C[size][0] = sum1;
				C[size++][1] = sum2;
				break;
			}
			if (i2 >= m || (i1 < n && N[i1] < M[i2])) {
				sum1 += N[i1++];
			} else if (i1 >= m || M[i2] < N[i1]) {
				sum2 += M[i2++];
			} else { // N[i1] == M[i2]
				C[size][0] = sum1 + N[i1++];
				C[size++][1] = sum2 + M[i2++];
				sum1 = sum2 = 0;
			}
		}
		int sum = 0;
		for (int i=0; i<size; i++) sum += C[i][0] > C[i][1] ? C[i][0] : C[i][1];
		printf("%d\n", sum);

	}
	return 0;
}