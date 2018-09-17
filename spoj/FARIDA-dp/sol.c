#include <stdio.h>

int inp() {
	char c;
	while((c=getchar_unlocked()) < '0' || c > '9');
	int num = c - '0';
	while((c=getchar_unlocked()) >= '0' && c <= '9') num = (num*10) + (c - '0');
	return num;
}

int main(){
	int T = inp();
	for(int t=1; t<=T; t++){
		int m = inp();
		long int gold = 0, prev1 = 0, prev2 = 0;
		while(m--){
			gold = inp() + prev2;
			gold = gold > prev1 ? gold : prev1;
			prev2 = prev1;
			prev1 = gold;
		}
		printf("Case %d: %ld\n", t, gold);
	}
	return 0;
}