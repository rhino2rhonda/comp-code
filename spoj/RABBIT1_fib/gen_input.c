#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int tc = 100;
int M_max = 20;
int N_max = 2147483647;

int main() {
	srand(time(NULL));
	printf("%d\n", tc);
	while(tc--){
		int m = 1 + (int)((float)rand()*(M_max-1)/RAND_MAX);
		int n = 1 + (int)((float)rand()*(N_max-1)/RAND_MAX);
		printf("%d %d\n", n, m);
	}
	return 0;
}