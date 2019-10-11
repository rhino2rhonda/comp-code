/*
Given weights and values of n items, put these items in a knapsack of capacity W to get the maximum 
total value in the knapsack. In other words, given two integer arrays val[0..n-1] and wt[0..n-1] 
which represent values and weights associated with n items respectively. Also given an integer W which
represents knapsack capacity, find out the maximum value subset of val[] such that sum of the weights
of this subset is smaller than or equal to W. You cannot break an item, either pick the complete item,
or don’t pick it (0-1 property).

Greedy counter example:
W = [12, 10,  10], val = [6, 4, 4], S = 20
Val/W = [0.5, 0.4, 0.4]
Greedy solution is to pick item 1 (W=12, Val=6)
But best solution is to pick items 2 and 3 (W=20, Val=8)

DP: Evaluate all subsets of items and pick the max value subset that fits

Top-down:
	Knapsack(n,k) ->
	  v = Val[n-1], w = Val[n-1]
	  best_value = max(Knapsack(n-1, k-w)+v, knapsack(n-1, k))

Bottom-up:
	Memoize by k and n values
	Start from k=0, n=0 and build table upwards
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 1000
#define MAX_C 1000
#define EMPTY -11233

typedef struct {
	int w;
	int val;
} Item;

int best_value(int n, int c, Item items[], int* counter){
	(*counter)++;
	if (n <= 0) return 0;
	Item item = items[n-1];
	if (item.w > c) return 0;
	int include = item.val + best_value(n-1, c-item.w, items, counter);
	int exclude = best_value(n-1, c, items, counter);
	return include > exclude ? include : exclude;
}

int best_value_memoized(int n, int c, Item items[], int saved_vals[MAX_N][MAX_C], int *counter){
	(*counter)++;
	if (n <= 0) return 0;
	Item item = items[n-1];
	if (item.w > c) return 0;
	if (saved_vals[n-1][c] != EMPTY) return saved_vals[n-1][c];
	int include = item.val + best_value_memoized(n-1, c-item.w, items, saved_vals, counter);
	int exclude = best_value_memoized(n-1, c, items, saved_vals, counter);
	int best_val = include > exclude ? include : exclude;
	saved_vals[n-1][c] = best_val;
	return best_val;
}

int best_value_bottoms_up(int n, int c, Item items[]){
	int saved_vals[MAX_N][MAX_C];
	for (int i=0; i<n; i++){
		for (int j=0; j<=c; j++){
			saved_vals[i][j] = EMPTY;
		}
	}
	for(int ni=0; ni<n; ni++){
		for(int ci=0; ci<=c; ci++){
			Item item = items[ni];
			if (ni == 0) {
				saved_vals[ni][ci] = item.w > ci ? 0 : item.val;
				continue;
			}
			int include = item.w > ci ? 0 : item.val + saved_vals[ni-1][ci-item.w];
			int exclude = saved_vals[ni-1][ci];
			saved_vals[ni][ci] = include > exclude ? include : exclude;
		}
	}
	return saved_vals[n-1][c];
}

int test1() {
	int n = 3;
	int c = 20;
	Item items[3];
	items[0].w = 12;
	items[0].val = 6;
	items[1].w = 10;
	items[1].val = 4;
	items[2].w = 10;
	items[2].val = 4;
	int val = best_value_bottoms_up(n, c, items);
	printf("Best Values: %d\n", val);
}

void test2() {
	srand(time(NULL));
	int n = 800;
	int c = 1000;
	printf("n: %d\tc: %d\n", n, c);
	Item items[MAX_N];
	for (int i =0; i<n; i++){
		items[i].w = ((float)rand()) * 20 / RAND_MAX;
		items[i].val = ((float)rand()) * 100 / RAND_MAX;;
	}
	int w_sum=0, val_sum=0;
	for (int i=0; i<n; i++){
		// printf("Item:%d\tW:%d\tVal:%d\n", i+1, items[i].w, items[i].val);
		w_sum += items[i].w;
		val_sum += items[i].val;
	}
	printf("Total Weight: %d\tTotal Value: %d\n", w_sum, val_sum);
	
	int test_type = 2;

	if (test_type == 0){
		printf("Test: Best Val Recursive\n");

		int t_start = time(NULL);
		int counter = 0;
		int val = best_value(n, c, items, &counter);
		int t_end = time(NULL);
		printf("Best Value: %d\n", val);
		printf("Time taken: %d seconds\n", t_end - t_start);
		printf("Function calls: %d\n", counter);
	}
	if (test_type == 1) {
		printf("Test: Best Val Recursive Memoized\n");
		
		int t_start = time(NULL);
		int repeat = 1000;
		int counter;
		int val;
		for (int i = 0; i < repeat; ++i) {
			int saved[MAX_N][MAX_C];
			for (int i=0; i<n; i++){
				for (int j=0; j<=c; j++){
					saved[i][j] = EMPTY;
				}
			}
			counter = 0;
			val = best_value_memoized(n, c, items, saved, &counter);
		}
		int t_end = time(NULL);
		printf("Best Value: %d\n", val);
		printf("Time taken: %d seconds\n", t_end - t_start);
		printf("Function calls: %d\n", counter);
	}
	if (test_type == 2){
		printf("Test: Best Val Bottom Up\n");

		int t_start = time(NULL);
		int repeat = 1000;
		int val;
		for (int i = 0; i < repeat; ++i){
			val = best_value_bottoms_up(n, c, items);
		}
		int t_end = time(NULL);
		printf("Best Value: %d\n", val);
		printf("Time taken: %d seconds\n", t_end - t_start);
		printf("Computations: %d\n", n*c);
	}
	
}

int main()
{
	test2();
	return 0;
}