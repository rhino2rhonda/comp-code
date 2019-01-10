#include <stdio.h>

struct bstNode {
	int val;
	int lr[2];
};

int isAvl(struct bstNode bst[], int size){
	int cur = size;
	while(cur--){
		if(bst[cur].val == -1) continue;
		if(bst[cur].lr[0] - bst[cur].lr[1] < -1 || bst[cur].lr[0] - bst[cur].lr[1] > 1) return 0;
		if(cur <= 0) break;
		int p = (cur-1)/2;
		bst[p].lr[cur%2] = 1 + (bst[cur].lr[0] > bst[cur].lr[1] ? bst[cur].lr[0] : bst[cur].lr[1]);
	}
	return 1;
}

int main(){
	struct bstNode bst[1000];
	int t;
	scanf("%d", &t);
	while(t--){
		int size;
		scanf("%d", &size);
		for(int i=0; i<size; i++) {
			scanf("%d", &(bst[i].val));
			bst[i].lr[0] = bst[i].lr[1] = 0;
		}
		printf("%s\n", isAvl(bst, size) ? "T": "F");
	}
	return 0;
}