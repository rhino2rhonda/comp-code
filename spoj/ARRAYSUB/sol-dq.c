#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000
#define MAX_K 100000
#define FRONT 1
#define REAR 0

int inp(){
	char c;
	while((c=getchar_unlocked())<'0' || c>'9');
	int num = c - '0';
	while((c=getchar_unlocked())>='0' && c<='9') num = num*10 + c - '0';
	return num;
}

struct DQ {
	int front, rear, size, cap;
	int arr[MAX_K];
};

struct DQ* newDQ(int n){
	struct DQ* dq = malloc(sizeof(struct DQ));
	dq->cap = n;
	dq->front = 1;
	dq->rear = 0;
	dq->size = 0;
	return dq;
}

int isEmpty(struct DQ* dq){
	return dq->size <= 0;
}

int get(struct DQ* dq, int front){
	return dq->arr[front ? dq->front : dq->rear];
}

void enqueue(struct DQ* dq, int val, int end){
	dq->size++;
	if (end == FRONT) {
		dq->front = (dq->cap + dq->front - 1) % dq->cap;
		dq->arr[dq->front] = val;
	} else {
		dq->rear = (dq->rear + 1) % dq->cap;
		dq->arr[dq->rear] = val;
	}
}

void dequeue(struct DQ* dq, int end){
	dq->size--;
	if (end == FRONT) {
		dq->front = (dq->front + 1) % dq->cap;
	} else {
		dq->rear = (dq->cap + dq->rear - 1) % dq->cap;
	}
}

void printDQ(struct DQ* dq){
	printf("DQ size:%d cap:%d f:%d r:%d\n", dq->size, dq->cap, dq->front, dq->rear);
	printf("front:%d rear:%d\n", get(dq, FRONT), get(dq, REAR));

	if (isEmpty(dq)) {
		printf("DQ is empty\n");
		return;
	}
	for(int i=0; i<dq->size; i++) printf("%d\n", dq->arr[(dq->front + i) % dq->cap]);
}

int main(){
	int A[MAX_N];
	int n = inp();
	struct DQ* dq = newDQ(n);
	for(int i=0; i<n; i++) A[i] = inp();
	int k = inp();

	for(int i=0; i<n; i++){
		if(!isEmpty(dq) && get(dq, FRONT) <= i - k) dequeue(dq, FRONT);
		while(!isEmpty(dq) && A[get(dq, REAR)] <= A[i]) dequeue(dq, REAR);
		enqueue(dq, i, REAR);
		if (i >= k-1) printf("%d ", A[get(dq, FRONT)]);
	}
	printf("\n");

	return 0;
}