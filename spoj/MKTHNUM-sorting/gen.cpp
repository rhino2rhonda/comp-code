#include <iostream>
#include <stdlib.h>
#include <time.h>


#define N 100000
#define Q 5000
#define NUM_MIN -1000000000
#define NUM_MAX 1000000000


using namespace std;

int main(){
	// Random seed
	srand(time(NULL));

	// N and Q
	cout << N << " " << Q << endl;

	// Array
	for(int i=0; i<N; i++) {
		int val = NUM_MIN + ((((float) rand() / RAND_MAX) * (NUM_MAX - NUM_MIN)));
		cout << val << " ";
	}
	cout << endl;

	// Queries
	for(int i=0; i<Q; i++) {
		int s = (((float) rand() / RAND_MAX) * N);
		int e = s + (((float) rand() / RAND_MAX) * (N - s));
		int k = 1 + (((float) rand() / RAND_MAX) * (e - s));
		cout << s << " " << e << " " << k << endl;
	}

	return 0;
}