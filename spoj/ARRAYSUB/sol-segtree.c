#include <stdio.h>

#define MAX_N 1000000
#define INF -1

#define max(a, b) (a > b ? a : b) 
#define min(a, b) (a < b ? a : b) 

int inp(){
	char c;
	while((c=getchar_unlocked()) < '0' || c > '9');
	int num = c - '0';
	while((c=getchar_unlocked()) >= '0' && c <= '9') num = num*10 + c - '0';
	return num;
}

void printTree(int S[], int node, int l, int r){
	// printf("dbg: %d\n", node);
	if (l > r) return;
	for(int i=0; i<(node-1)/2; i++) printf(" ");
	printf("node:%d l:%d r:%d val:%d\n", node, l, r, S[node]);
	if(l == r) return;
	int mid = (l+r)/2;
	int nodeL = 2*node+1;
	int nodeR = nodeL+1;
	printTree(S, nodeL, l, mid);
	printTree(S, nodeR, mid+1, r);
}

void setTarget(int S[], int node, int l, int r, int target, int val){
	// printf("setTarget node:%d l:%d r:%d target:%d val:%d\n", node, l, r, target, val);
	if (l > target || r < target ) return;
	if (l == r) {
		S[node] = val;
		return;
	}
	int mid = (l+r)/2;
	int nodeL = 2*node+1;
	int nodeR = nodeL+1;
	setTarget(S, nodeL, l, mid, target, val);
	setTarget(S, nodeR, mid+1, r, target, val);
	S[node] = max(S[nodeL], S[nodeR]);
}

int queryRange(int S[], int node, int l, int r, int s, int e){
	// printf("dbg: n:%d nv:%d l:%d r:%d s:%d e:%d\n", node, S[node], l, r, s, e);
	if (l > r || l > e || r < s) return INF;
	if (l==s && r==e) return S[node];
	int mid = (l+r)/2;
	int nodeL = 2*node+1;
	int nodeR = nodeL+1;
	int maxL = queryRange(S, nodeL, l, mid, max(s,l), min(e,mid));
	int maxR = queryRange(S, nodeR, mid+1, r, max(s,mid+1), min(e,r));
	return max(maxL, maxR);
}

int main(){
	int S[2*MAX_N];
	int n = inp();
	for(int i=0; i<2*n; i++) S[i] = INF;
	for(int i=0; i<n; i++) setTarget(S, 0, 0, n-1, i, inp());
	// printTree(S, 0, 0, n-1);
	int k = inp();
	for(int i=0; i<=n-k; i++){
		printf("%d", queryRange(S, 0, 0, n-1, i, i+k-1));
		// queryRange(S, 0, 0, n-1, i, i+k-1);
		// printf("\n");
		// if (i==1) return 0;
		if(i<n-1) printf(" ");
	}
	printf("\n");
	return 0;
}