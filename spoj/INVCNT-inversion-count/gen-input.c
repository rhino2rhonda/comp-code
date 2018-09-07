#include <stdio.h>
#include <stdlib.h>

int tc = 100;
int size_max = 200000;
int key_max = 10000000;

int main()
{
	printf("%d\n", tc);
	for (int t=0; t<tc; t++){
		int size = (((float) rand()) / RAND_MAX) * size_max; 
		printf("\n%d\n", size);
		for(int s=0; s<size; s++) {
			int rand_num = (((float) rand()) / RAND_MAX) * key_max;
			printf("%d\n", rand_num);
		}
	}
	return 0;
}