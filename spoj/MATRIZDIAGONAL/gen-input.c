#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int order_max = 5000;
int num_max = 10000000;
int falso = 0;

int main()
{
	srand(time(NULL));
	int order = 1 + ((((float) rand()) / RAND_MAX) * (order_max-1));
	printf("%d\n", order);
	for (int i=0; i<order; i++){
		for (int j=0; j<order; j++){
			int n = falso ? ((((float) rand()) / RAND_MAX)-0.5) * 2 * num_max: 0;
			printf("%d ", n);
		}
		printf("\n");
	}
	return 0;
}