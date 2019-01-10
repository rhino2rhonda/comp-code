#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 200

int maxLenBF(int A[], int n){
	int maxLen = -1;
	for (int l=0; l<n; l++){
		for (int r=l+1; r<n; r++){
			int violate = 0;
			int count0 = 0;
			int count1 = 0;
			for (int i=l; i<=r; i++){
				if (A[i] == 0) count0 ++;
				else count1++;
			}
			if (count0 == count1) {
				int newLen = r - l + 1;
				if (maxLen < newLen) {
					maxLen = newLen;
				}
			}
		}
	}
	return maxLen;
}


int maxLenHashTable(int A[], int n){
 	int HT[2*MAX_N];
	for(int i=0; i<2*MAX_N; i++) HT[i] = -100;
	int diff = MAX_N, maxLen = -1;
	HT[MAX_N] = -1;
	for(int i=0; i<n; i++){
		if (A[i] == 0) diff--;
		else diff++;
		if (HT[diff] >= -10) {
			int newLen = i - HT[diff];
			maxLen = maxLen > newLen ? maxLen : newLen;
		} else {
			HT[diff] = i;
		}
	}
	return maxLen;
}

void mainBF() {
	int A[] = {1, 0, 1, 1, 1, 0, 0};
	printf("maxLen: %d\n", maxLenBF(A, 7));

	int B[] = {1,1,1,1};
	printf("maxLen: %d\n", maxLenBF(B, 5));

	int C[] = {0, 0, 1, 1, 0};
	printf("maxLen: %d\n", maxLenBF(C, 5));
}

void mainHT() {
	int A[] = {1, 0, 1, 1, 1, 0, 0};
	printf("maxLen: %d\n", maxLenHashTable(A, 7));

	int B[] = {1,1,1,1};
	printf("maxLen: %d\n", maxLenHashTable(B, 5));

	int C[] = {0, 0, 1, 1, 0};
	printf("maxLen: %d\n", maxLenHashTable(C, 5));
}

void testCases(){
	srand(time(NULL));
	int size = 100;
	int tc = 100;
	int A[100];
	while (tc--){
		for (int i=0; i<size; i++) A[i] = rand() > RAND_MAX/2 ? 1 : 0;
		if (maxLenBF(A, size) != maxLenHashTable(A, size)){
			printf("Test failed: tc:%d [%d != %d]\n", tc, maxLenBF(A, size), maxLenHashTable(A, size));
			printf("A = ");
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