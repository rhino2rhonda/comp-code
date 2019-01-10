#include <stdio.h>

#define END 0

int inp(){
	char c;
	while(1){
		c = getchar_unlocked();
		if(c >= '0' && c<='9') break;
	}
	int num = c - '0';
	while(1){
		c = getchar_unlocked();
		if(c < '0' || c > '9') break;
		num *= 10;
		num += c - '0';
	}
	return num;
}


int main(){
	int trucks[1000];
	int lane[1000];
	while(1){
		// Input
		int n = inp();
		// printf("n:%d\n", n);
		if (n == END) return 0;
		for(int i=0; i<n; i++) trucks[i] = inp();
		// for(int i=0; i<n; i++) printf("%d ", trucks[i]);
		// printf("\n");
		// printf("ignored: %d\n", inp());
		// inp();
		// Logic
		int l = -1;
		int next = 1;
		for(int t=0; t<n; t++){
			// printf("truck:%d next:%d, l:%d\nQueue: ", trucks[t], next, l);
			// for(int i=0; i<=l; i++) printf("%d ", lane[i]);
			// printf("\n");
			if(next == trucks[t]){
				next++;
				continue;
			}
			while(l >= 0 && next == lane[l]) {
				next++;
				l--;
			}
			lane[++l] = trucks[t];
		}
		while(l >= 0 && next == lane[l]) {
			next++;
			l--;
		}
		// printf("final: next:%d, l:%d\nQueue: ", next, l);
		// for(int i=0; i<=l; i++) printf("%d ", lane[i]);
		// printf("\n");
		printf("%s\n", next > n ? "yes": "no");
	}
}