#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int getRandInt(int a, int b){
	return round(a + ((float)rand())*(b-a)/RAND_MAX);
}

void main(){
	srand(time(NULL));
	int n = 10000;
	int max = 50;
	int min = 0;
	printf("%d\n", n);
	for(int i=0; i<n; i++) printf("%d %d\n", getRandInt(min, max), getRandInt(min, max));
}