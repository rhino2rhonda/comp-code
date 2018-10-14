#include <stdio.h>

int inp(){
	char c;
	while((c=getchar_unlocked()) < '0' || c > '9');
	int num = c - '0';
	while((c=getchar_unlocked()) >= '0' && c <= '9') num = num*10 + c - '0';
	return num;
}

int main(){
	int A[100000];
	int n = inp();
	for(int i=0; i<n; i++) A[i] = inp();
	int k = inp();
	for(int i=k-1; i<n; i++){
		int max = -1;
		for(int j=i-k+1; j<=i; j++) max = max > A[j] ? max : A[j];
		printf("%d",max);
		if(i<n-1) printf(" ");
	}
	printf("\n");
	return 0;
}