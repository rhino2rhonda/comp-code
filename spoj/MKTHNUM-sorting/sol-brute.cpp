#include <iostream>
#include <algorithm>
#include <vector>


#define MAX_N 100000
#define MAX_Q 5000


using namespace std;

typedef struct {
	int s;
	int e;
	int k;
} Query;

int inp(){
	char c;
	int neg = 0;
	while(1){
		c = getchar_unlocked();
		if(c == '-'){
			neg = 1;
		} else if (c >= '0' && c <= '9') {
			break;
		} else {
			neg = 0;
		}
	}
	
	int num = c - '0';
	while((c = getchar_unlocked()) >= '0' && c <= '9') num = (num * 10) + (c - '0');

	return neg ? -1 * num : num; 
}

int main(){
	int n, q;
	int A[MAX_N];
	Query Q[MAX_Q];

	// Read Input

	// cin >> n >> q;
	n = inp();
	q = inp();
	// cout << "n:" << n << " q:" << q << endl; // Debug

	// for (int i=0; i<n; i++) cin >> A[i];
	for (int i=0; i<n; i++) A[i] = inp();
	// for (int i=0; i<n; i++) cout << "\t" << A[i] << endl; // Debug

	for (int i=0; i<q; i++){
		Q[i].s = inp()-1;
		Q[i].e = inp()-1;
		Q[i].k = inp();
		// cin >> Q[i].s >> Q[i].e >> Q[i].k;
		// cout << "s: " << Q[i].s << " e: " << Q[i].e << " k: " << Q[i].k << endl; // Debug
	}

	// Process Queries

	for (int i=0; i<q; i++){

		// Sort sub array
		vector<int> heap(A + Q[i].s, A + Q[i].e + 1);
		sort(heap.begin(), heap.end());

		// for(auto x: heap){ // Debug
		// 	cout << x << " ";
		// }
		// cout << endl;

		// Print Kth smallest element
		printf("%d\n", heap[Q[i].k-1]);
	}

    return 0;
}