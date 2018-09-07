#include <stdio.h>
#include <stdlib.h>

int A[200000];
int C[200000];

long int merge(int* A, int* B, int sizeA, int sizeB) {
	int a=0,b=0,c=0;
	long int inv=0;
	while (a < sizeA || b < sizeB) {
		if (a >= sizeA || (b < sizeB && A[a] > B[b])) {
			C[c++] = B[b++];
			inv += sizeA - a;
		} else {
			C[c++] = A[a++];
		}
	}
	for(int i=0; i<sizeA; i++) {
		A[i] = C[i];
	}
	for(int i=0; i<sizeB; i++) {
		B[i] = C[sizeA + i];
	}
	return inv;
}

long int merge_sort(int* X, int size) {
	if (size <= 1) return 0;
	int mid = size/2;
	int sizeA = mid;
	int sizeB = size - sizeA;
	long int invA = merge_sort(X, sizeA);
	long int invB = merge_sort(&X[mid], sizeB);
	long int inv = merge(X, &X[mid], sizeA, sizeB);
	return inv + invA + invB;
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

int main() {
	int T, N;
	T = in();
	for (int t=0; t<T; t++){
		N = in();
		for (int i=0; i<N; i++){
			A[i] = in();
		}
		printf("%ld\n", merge_sort(A, N));
	}
	return 0;
}