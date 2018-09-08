#include <stdio.h>
#include <stdlib.h>

#define MAX_VAL 200000
int INP[MAX_VAL];
int MAP[MAX_VAL];
int BIT[MAX_VAL];
int map_idx = 0;

int init_bit(int size){
	for (int i=0; i<size; i++){
		BIT[i] = 0;
	}
}

void print_bit(int size){
	for(int i=0; i<size; i++) {
		printf("%d %d\n", i, BIT[i]);
	}
}

void update_bit(int idx, int val) {
	for (; idx<=MAX_VAL; idx += idx & -idx) {
		BIT[idx -1] += val;
	}
}

int query_bit(int idx) {
	int sum=0;
	for (; idx >= 1; idx -= idx & -idx) {
		sum += BIT[idx-1];
	}
	return sum;
}

int in()
{
    char c;
    do
	c=getchar_unlocked();
    while (c<=32);
    int res=0;
    do
    {
	res=(res<<1)+(res<<3)+c-'0';
	c=getchar_unlocked();
    }
    while (c>32);
    return res;
}

void quick_sort(int arr[], int lo, int hi) {

	if (lo >= hi) return;

	// Partition
	int pivot = arr[lo];
	int swap_idx = lo+1;
	for (int i = swap_idx; i <= hi; i++){
		if (arr[i] < pivot) {
			if (i != swap_idx) {
				arr[i] += arr[swap_idx];
				arr[swap_idx] = arr[i] - arr[swap_idx];
				arr[i] -= arr[swap_idx];
			}
			swap_idx++;
		}
	}
	if (lo != --swap_idx) {
		arr[lo] += arr[swap_idx];
		arr[swap_idx] = arr[lo] - arr[swap_idx];
		arr[lo] -= arr[swap_idx];
	}

	//D&Q
	quick_sort(arr, lo, swap_idx-1);
	quick_sort(arr, swap_idx+1, hi);

}

int find(int arr[], int size, int val) {
	int lo=0, hi=size-1;
	while (lo<=hi) {
		int mid = (lo + hi) / 2;
		if (arr[mid] == val) return mid+1;
		if (arr[mid] < val) lo = mid + 1;
		else hi = mid - 1;
	}
	printf("Value %d not found. Exiting\n", val);
	exit(1);
}

int main() {
	int T, N;
	T = in();
	for (int t=0; t<T; t++){
		N = in();
		init_bit(N);
		for (int i=0; i<N; i++) INP[i] = MAP[i] = in();
		quick_sort(MAP, 0, N-1);
		long int inv = 0;
		for (int i=0; i<N; i++){
			int val = find(MAP, N, INP[i]);
			inv += i - query_bit(val);
			update_bit(val, 1);
		}
		printf("%ld\n", inv);
	}
	return 0;
}