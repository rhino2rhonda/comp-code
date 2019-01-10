#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M_PI 3.14159265358979323846
#define MAX_V 3010

// Set 

typedef struct {
	int elems[MAX_V];
	int size;
	int cap;
} Set;

Set* setNew(int cap, int def){
	Set* s = malloc(sizeof(Set));
	def = def == 0 ? 0 : 1;
	s->size = def == 0 ? 0 : cap;
	s->cap = cap;
	for(int i=0; i<cap; i++) s->elems[i] = def;
	return s;
}

void setAdd(Set* s, int i){
	if (i >= 0 && i < s->cap && s->elems[i] != 1){
		s->elems[i] = 1;
		s->size++;
	}
}

void setRemove(Set* s, int i){
	if (i >= 0 && i < s->cap && s->elems[i] != 0){
		s->elems[i] = 0;
		s->size--;
	}
}

int setHas(Set* s, int i){
	if (i < 0 || i >= s->cap) return 0;
	return s->elems[i] == 0 ? 0 : 1;
}

void setPrint(Set* s){
	printf("Printing Set:\nCapacity: %d\t Size: %d\n", s->cap, s->size);
	for(int i=0; i<s->cap; i++) printf("%d ", s->elems[i]);
	printf("\n");
}

void setTest(){
	Set* s = setNew(10, 0);
	setAdd(s, 3);
	setAdd(s, 7);
	setAdd(s, 7);
	setPrint(s);
	s = setNew(6, 1);
	setRemove(s, 5);
	setRemove(s, 3);
	setRemove(s, 3);
	setPrint(s);
}

// Heap

typedef struct {
	double weight;
	int n1;
	int n2;
} Edge;

Edge* edgeNew(double weight, int n1, int n2){
	Edge* e = malloc(sizeof(Edge));
	e->weight = weight;
	e->n1 = n1;
	e->n2 = n2;
	return e;
}

typedef struct {
	Edge* edges[MAX_V*(MAX_V-1)/2];
	int size;
} Heap;

Heap* heapNew(){
	Heap* h = malloc(sizeof(Heap));
	h->size = 0;
	return h;
}

void heapAdd(Heap* h, Edge* e){
	h->edges[h->size] = e;
	int curr = h->size++;
	while (curr > 0){
		int parent = (curr - 1) / 2;
		if (h->edges[parent]->weight <= h->edges[curr]->weight) break;
		Edge* e = h->edges[parent];
		h->edges[parent] = h->edges[curr];
		h->edges[curr] = e;
		curr = parent;
	}
}

Edge* heapExtractMin(Heap* h){
	Edge* minEdge = h->edges[0];
	h->edges[0] = h->edges[--h->size];
	int curr = 0;
	while(1){
		int child = (curr * 2) + 1;
		if (child >= h->size) break;
		int childR = child+1;
		if (childR < h->size && h->edges[childR]->weight < h->edges[child]->weight){
			child = childR;
		}
		if (h->edges[curr]->weight <= h->edges[child]->weight) break;
		Edge* e = h->edges[curr];
		h->edges[curr] = h->edges[child];
		h->edges[child] = e;
		curr = child;
	}
	return minEdge;
}

void heapPrint(Heap* h){
	printf("Printing Heap:\nSize: %d\n", h->size);
	for(int i=0; i<h->size; i++) printf("[%f %d %d] ", h->edges[i]->weight, h->edges[i]->n1, h->edges[i]->n2);
	printf("\n");
}

void heapTest(){
	Heap* h = heapNew();
	Edge* e = edgeNew(10, 2, 3);
	heapAdd(h, e);
	e = edgeNew(4, 1, 4);
	heapAdd(h, e);
	e = edgeNew(7, 10, 4);
	heapAdd(h, e);
	heapPrint(h);
	e = heapExtractMin(h);
	printf("Extracted edge: %f %d %d\n", e->weight, e->n1, e->n2);
	heapPrint(h);
	e = heapExtractMin(h);
	printf("Extracted edge: %f %d %d\n", e->weight, e->n1, e->n2);
	heapPrint(h);
}

// Vertex

typedef struct {
	int r;
	int x;
	int y;
} Vertex;

int vertexReadStatic(Vertex V[]){
	V[0].x = 2; V[0].y = 2; V[0].r = 2;
	V[1].x = 1; V[1].y = 6; V[1].r = 1;
	V[2].x = 6; V[2].y = 1; V[2].r = 1;
	return 3;
	// V[0].x = 1; V[0].y = 1; V[0].r = 1;
	// V[1].x = 1; V[1].y = 4; V[1].r = 1;
	// return 2;
}

int vertexRead(Vertex V[]){
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%d %d %d", &V[i].x, &V[i].y, &V[i].r);
	}
	return n;
}

void vertexPrint(Vertex V[], int size){
	printf("Printing vertices:\nSize: %d\n", size);
	for(int i=0; i<size; i++) printf("[x:%d y:%d r:%d] ", V[i].x, V[i].y, V[i].r);
	printf("\n");
}

void vertexTest(){
	Vertex V[10];
	int size = vertexRead(V);
	printf("Nodes Read: %d\n", size);
	vertexPrint(V, size);
}

// Prim's Algo

double computeWeight(Vertex v1, Vertex v2){\
	double weight = M_PI * v1.r;
	weight += M_PI * v2.r;
	weight += 2 * pow(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) + pow(v1.r - v2.r, 2), 0.5);
	return weight;
}

void computeWeightTest(){
	Vertex v1 = {.x = 10, .y = 20, .r = 30};
	Vertex v2 = {.x = 20, .y = 20, .r = 30};
	printf("Weight: %f\n", computeWeight(v1, v2));
	Vertex v3 = {.x = 1, .y = -2, .r = 5};
	Vertex v4 = {.x = 4, .y = -6, .r = 11};
	printf("Weight: %f\n", computeWeight(v3, v4));
}

double prim(Vertex V[], int size){
	Set* targetSet = setNew(size, 0);
	Set* sourceSet = setNew(size, 1);

	Heap* minHeap = heapNew();

	int currV = 0;
	setRemove(sourceSet, 0);
	setAdd(targetSet, 0);
	double sum = 0;

	while(sourceSet->size > 0){
		for(int i=0; i<size; i++){
			// printf("debug : i:%d currV:%d\n", i, currV);
			if (i==currV || setHas(targetSet, i)) continue;
			heapAdd(minHeap, edgeNew(computeWeight(V[currV], V[i]), currV, i));
			// heapPrint(minHeap);
		}
		Edge* e;
		while(1){
			if (minHeap->size <= 0){
				printf("Error: heap is empty\n");
				exit(1);
			}
			e = heapExtractMin(minHeap);
			// printf("Extracted edge: %d %d %d\n", e->weight, e->n1, e->n2);
			if (setHas(sourceSet, e->n1) || setHas(sourceSet, e->n2)) break;
		}
		sum += e->weight;
		currV = setHas(targetSet, e->n1) ? e->n2 : e->n1;
		setRemove(sourceSet, currV);
		setAdd(targetSet, currV);
	}
	return sum;
}

void solve(){
	Vertex V[MAX_V];
	while(1){
		int size = vertexRead(V);
		if(size <= 0) return;
		printf("%.3f\n", prim(V, size));
	}
}

int main() {
	solve();
	return 0;
}