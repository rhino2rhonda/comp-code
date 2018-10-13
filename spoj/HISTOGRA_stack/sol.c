#include <stdio.h>

#define MAX_N 100000
#define lli long long int

int inp(){
	char c;
	while((c=getchar_unlocked())<'0' || c > '9');
	int num = c - '0';
	while((c=getchar_unlocked())>='0' && c<='9') num = num*10 + c - '0';
	return num;
}

struct item {
	lli val;
	int beg;
	int end;
};

int main(){
	struct item A[MAX_N];
	int S[MAX_N];
	int s_size = 0;
	while (1) {
		int n = inp();
		if (n == 0) break;
		for(int i=0; i<n; i++) A[i].val = inp();
		// for(int i=0; i<n; i++) printf("%d ", A[i]);
		// printf("\n");
		
		for(int i=0; i<n; i++){
			int beg = i;
			while(s_size > 0 && A[S[s_size-1]].val > A[i].val){
				s_size--;
				A[S[s_size]].end = i;
				beg = A[S[s_size]].beg;
			}
			if (s_size <= 0 || A[S[s_size-1]].val < A[i].val){
				S[s_size] = i;
				A[i].beg = beg;
				s_size++;
			} else {
				A[i].beg = A[i].end = i;
			}
		}
		while(s_size > 0) A[S[--s_size]].end = n;

		lli max = -1;
		for(int i=0; i<n; i++){
			lli val = A[i].val * (A[i].end - A[i].beg);
			max = max > val ? max : val;
		}

		printf("%lld\n", max);
	}
	return 0;
}