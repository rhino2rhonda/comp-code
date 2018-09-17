#include <stdio.h>

int inp(){
	char c;
	while((c=getchar_unlocked()) < '0' || c > '9');
	int n=c-'0';
	while((c=getchar_unlocked()) >= '0' && c <= '9') n = (n*10)+(c-'0');
	return n;
}

struct event {
	int start;
	int end;
};

void sort(struct event E[], int lo, int hi) {
	if(hi <= lo) return;
	// Partition
	struct event pivot = E[hi];
	struct event temp;
	int mid = lo;
	for(int i=lo; i<hi; i++){
		if (E[i].end < pivot.end){
			temp = E[mid];
			E[mid++] = E[i];
			E[i] = temp;
		}
	}
	E[hi] = E[mid];
	E[mid] = pivot;

	// D&Q
	sort(E, lo, mid-1);
	sort(E, mid+1, hi);
}

void print(struct event E[], int n) {
	for(int i=0; i<n; i++) printf("start:%d\tend:%d\n", E[i].start, E[i].end);
}

int main(int argc, char const *argv[]){
	struct event E[100000];
	int t=inp();
	while(t--){
		int n=inp();
		for(int i=0; i<n; i++){
			E[i].start = inp();
			E[i].end = inp();=
		}
		sort(E, 0, n-1);
		// Count
		int count = 0;
		int curr_end = 0;
		for(int i=0; i<n; i++){
			if (E[i].start >= curr_end) {
				count++;
				curr_end = E[i].end;
			}
		}
		printf("%d\n", count);
	}

	return 0;
}