#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HASH_MAX 100

int maxLenBF(int A[], int n, int k){
	int maxLen = -1;
	for (int l=0; l<n; l++){
		for (int r=l+1; r<n; r++){
			int violate = 0;
			for (int i=l; i<=r; i++){
				for (int j=i+1; j<=r; j++){
					// printf("\t\t%d %d %d:%d %d:%d\n", l, r, i, A[i], j, A[j]);
					if ((A[i] + A[j]) % k == 0) {
						// printf("violate\n");
						violate = 1;
						break;
					}
				}
				if (violate) break;
			}
			if (!violate) {
				int newLen = r - l + 1;
				if (maxLen < newLen) {
					// printf("\tnewMaxLen:%d, [%d, %d]\n", newLen, l, r);
					maxLen = newLen;
				}
			}
		}
	}
	return maxLen;
}


int maxLenHashTable(int A[], int n, int k){
	int HT[HASH_MAX];
	for(int i=0; i<HASH_MAX; i++) HT[i] = 0;
	int i = 0, j = 1, maxLen = -1;
	HT[A[0] % k]++;
	while (j < n){
		int c = (k - (A[j] % k)) % k;
		while (HT[c] > 0){
			if (i >= j) {
				printf("Should not happen! Exiting.\n");
				exit(1);
			}
			HT[A[i++] % k]--;
		}
		HT[A[j++] % k]++;
		int newLen = j - i;
		maxLen = maxLen > newLen ? maxLen : newLen;
	}
	return maxLen;
}

void mainBF() {
	int A[] = {3, 7, 1, 9, 2};
	printf("maxLen: %d\n", maxLenBF(A, 5, 3));

	int B[] = {2, 4, 4, 3};
	printf("maxLen: %d\n", maxLenBF(B, 4, 4));

	int C[] = {3, 4, 1, 4, 1, 4, 1, 0, 0, 6};
	printf("maxLen: %d\n", maxLenBF(C, 10, 7));
}

void mainHT() {
	int A[] = {3, 7, 1, 9, 2};
	printf("maxLen: %d\n", maxLenHashTable(A, 5, 3));

	int B[] = {2, 4, 4, 3};
	printf("maxLen: %d\n", maxLenHashTable(B, 4, 4));

	int C[] = {3, 4, 1, 4, 1, 4, 1, 0, 0, 6};
	printf("maxLen: %d\n", maxLenHashTable(C, 10, 7));
}


void testCases(){
	srand(time(NULL));
	int size = 100;
	int tc = 100;
	int A[100];
	while (tc--){
		for (int i=0; i<size; i++) A[i] = rand() / size;
		int k = 2 + (((float) rand())*(100)/RAND_MAX);
		if (maxLenBF(A, size, k) != maxLenHashTable(A, size, k)){
			printf("Test failed\n");
			printf("k=%d\nA = ", k);
			for (int i=0; i<size; i++) printf("%d ", A[i]);
			printf("\n");
			return;
		}
	}
	printf("All tests passed\n");
}

int main() {
	testCases();
	return 0;
}