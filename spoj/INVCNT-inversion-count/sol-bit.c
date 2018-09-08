#include <stdio.h>

#define MAX_VAL 10000000
int BIT[MAX_VAL];

int init_bit(int size){
	for (int i=0; i<size; i++){
		BIT[i] = 0;
	}
}

void print_bit(int size){
	for(int i=0; i<size; i++) {
		printf("%d %d\n", i, BIT[i]);
	}
}

void update_bit(int idx, int val) {
	for (; idx<=MAX_VAL; idx += idx & -idx) {
		BIT[idx -1] += val;
	}
}

int query_bit(int idx) {
	int sum=0;
	for (; idx >= 1; idx -= idx & -idx) {
		sum += BIT[idx-1];
	}
	return sum;
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
		init_bit(10000000);
		long int inv = 0;
		for (int i=0; i<N; i++){
			int val = in();
			inv += i - query_bit(val);
			update_bit(val, 1);
		}
		printf("%ld\n", inv);
	}
	return 0;
}