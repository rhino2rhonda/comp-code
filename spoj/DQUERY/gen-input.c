#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int arr_max = 30000;
int query_max = 200000;
int num_max = 1000000;

void main()
{
	srand(time(NULL));
	int arr_size = 1 + ((((float) rand()) / RAND_MAX) * (arr_max-1));
	printf("%d\n", arr_size);
	for (int i=0; i<arr_size; i++){
		int n = 1 + ((((float) rand()) / RAND_MAX) * (num_max-1));
		printf("%d ", n);
	}
	int query_size = 1 + ((((float) rand()) / RAND_MAX) * (query_max-1));
	printf("\n%d\n", query_size);
	for (int i=0; i<query_size; i++){
		int l = 1 + ((((float) rand()) / RAND_MAX) * (arr_size-1));
		int r = l + ((((float) rand()) / RAND_MAX) * (arr_size-l));
		printf("%d %d\n", l, r);
	}
}