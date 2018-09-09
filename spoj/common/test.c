#include <stdio.h>
#include <stdlib.h>

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
			int val = in();
			if (val == 0) {
				exit(1);
			}
		}
		// printf("%d\n", 0);
	}
	return 0;
}