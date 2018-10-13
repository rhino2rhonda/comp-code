#include <stdio.h>

void main(){
	int n = 100000;
	printf("%d ", n);
	for(int i=0; i<n; i++) printf("%d ", 1000000000);
	printf("\n0\n");
}