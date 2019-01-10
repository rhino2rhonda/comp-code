#include <stdio.h>

#define MAX_K 10
#define MAX_N 100
#define MIN_NUM -1
#define MAX_NUM 100000

#define minimum(x, y) ((x) < (y) ? (x) : (y))
#define maximum(x, y) ((x) > (y) ? (x) : (y))


int solve(int lists[MAX_K][MAX_N], int k, int n){
	int ptrs[MAX_K];
	for (int i=0; i<k; i++) ptrs[i] = 0;
	int min, max;
	int minRange = MAX_NUM;
	while (1){
		min = MAX_NUM;
		max = MIN_NUM;
		for (int i=0; i<k; i++){
			min = minimum(min, lists[i][ptrs[i]]);
			max = maximum(max, lists[i][ptrs[i]]);
		}
		minRange = minimum(minRange, max - min);
		int minList = -1;
		for (int i=0; i<k; i++){
			if (lists[i][ptrs[i]] == min){
				minList = i;
				break;
			}
		}
		if (++ptrs[minList] >= n) break;
	}
	return minRange;
}

void test(){
	int k = 3;
	int n = 5;
	int A[MAX_K][MAX_N] = {
		{4, 7, 9, 12, 15},
		{0, 8, 10, 14, 20},
		{6, 12, 16, 30, 50}
	};
	printf("Result: %d\n", solve(A, k, n));
	int B[MAX_K][MAX_N] = {
		{10, 20, 30, 30, 100},
		{33, 36, 45, 45, 90},
		{48, 49, 55, 59, 70}
	};
	printf("Result: %d\n", solve(B, k, n));
}

int main(){
	test();
	return 1;
}