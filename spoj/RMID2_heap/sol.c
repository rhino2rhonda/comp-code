#include <stdio.h>
#include <stdlib.h>

#define QUERY -1
#define TC_END 0

#define MAX_HEAP 1
#define MIN_HEAP 2
#define HEAP_MAX 100000

int inp() {
	char c;
	int neg = 0;
	while(1){
		c = getchar_unlocked();
		if (c == '-') {
			c = getchar_unlocked();
			neg = 1;
			break;
		}
		else if (c >= '0' && c <= '9') break;
	}
	int num = c - '0';
	while((c = getchar_unlocked()) >= '0' && c <= '9') num = (num*10) + (c-'0');
	return neg == 0 ? num: -num;
}

/////////////// BEGIN HEAP

struct Heap {
	int type;
	int harr[HEAP_MAX];
	int size;
};

struct Heap* newHeap(int type){
	struct Heap* h = malloc(sizeof(struct Heap));
	h->type = type;
	h->size = 0;
	return h;
}

void resetHeap(struct Heap* h) {
	h->size = 0;
}

int getFirst(struct Heap* h) {
	return h->harr[0];
}

void insertHeap(struct Heap* h, int val){
	int curr = h->size++;
	h->harr[curr] = val;
	int parent;
	int temp;
	while((parent = (curr-1)/2) >= 0){
		int violation = 0;
		if (h->type == MAX_HEAP && h->harr[parent] < h->harr[curr]) violation = 1;
		if (h->type == MIN_HEAP && h->harr[parent] > h->harr[curr]) violation = 1;
		if (violation){
			temp = h->harr[parent];
			h->harr[parent] = h->harr[curr];
			h->harr[curr] = temp;
			curr = parent;
		} else break;
	}
}

int extractHeap(struct Heap* h){
	if(h->size <= 0) {
		printf("Extract heap must be called on non-empty heap\n");
		exit(1);
	}
	int ext = h->harr[0];
	h->harr[0] = h->harr[--(h->size)];
	int curr = 0;
	while(1){
		int childL = (2*curr) + 1;
		if (childL >= h->size) break;
		int swapChild = childL;
		int childR = childL + 1;
		if (childR < h->size){
			if(h->type == MAX_HEAP && h->harr[childR] > h->harr[childL]) swapChild = childR;
			if(h->type == MIN_HEAP && h->harr[childR] < h->harr[childL]) swapChild = childR;
		}
		int violation = 0;
		if(h->type == MAX_HEAP && h->harr[curr] < h->harr[swapChild]) violation = 1;
		if(h->type == MIN_HEAP && h->harr[curr] > h->harr[swapChild]) violation = 1;
		if(violation){
			int temp = h->harr[swapChild];
			h->harr[swapChild] = h->harr[curr];
			h->harr[curr] = temp;
			curr = swapChild;
		} else break;
	}
	return ext;
}

void printHeap(struct Heap* h){
	printf("Printing Heap:\nType: %d\nSize: %d\nData: ", h->type, h->size);
	for(int i=0; i<h->size; i++) printf("%d:%d ", i, h->harr[i]);
	printf("\n");
}

//////////////// END HEAP

int main() {
	struct Heap* hmax = newHeap(MAX_HEAP);
	struct Heap* hmin = newHeap(MIN_HEAP);
	int t = inp();
	for(int i=0; i<t; i++){
		if(i>0) printf("\n");
		resetHeap(hmax);
		resetHeap(hmin);
		while(1) {
			int next = inp();
			if (next == TC_END) break;
			if (next == QUERY){
				if (hmax->size > 0) printf("%d\n", extractHeap(hmax));
			} else {
				if (hmax->size == 0 || next <= getFirst(hmax)) insertHeap(hmax, next);
				else insertHeap(hmin, next);
			}
			if(hmax->size - hmin->size > 1) {
				insertHeap(hmin, extractHeap(hmax));
			} else if (hmin->size > hmax->size) {
				insertHeap(hmax, extractHeap(hmin));
			}
		}
	}
	return 0;
}