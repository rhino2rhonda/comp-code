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

int main(){
	int n, q;
	int A[MAX_N];
	Query Q[MAX_Q];

	// Read Input

	cin >> n >> q;
	// cout << "n:" << n << " q:" << q << endl; // Debug

	for (int i=0; i<n; i++) cin >> A[i];
	// for (int i=0; i<n; i++) cout << "\t" << A[i] << endl; // Debug
	// fflush(stdout);

	for (int i=0; i<q; i++){
		int s, e, k;
		cin >> Q[i].s >> Q[i].e >> Q[i].k;
		Q[i].s--;
		Q[i].e--;
		// cout << "s: " << Q[i].s << " e: " << Q[i].e << " k: " << Q[i].k << endl; // Debug
	}

	// Process Queries

	for (int i=0; i<q; i++){

		// Make max heap of size k
		vector<int> heap(A + Q[i].s, A + Q[i].s + Q[i].k);
		make_heap(heap.begin(), heap.end());

		// for(auto x: heap){ // Debug
		// 	cout << x << " ";
		// }
		// cout << endl;

		// Maintain heap of k smallest elements
		for (int j=Q[i].s + Q[i].k; j<=Q[i].e; j++){
			if (A[j] >= heap[0]) continue;
			heap[0] = A[j];
			make_heap(heap.begin(), heap.end());
		}

		// Heap head is the kth smallest element
		printf("%d\n", heap[0]);
	}

    return 0;
}