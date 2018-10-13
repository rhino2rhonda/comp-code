#include <stdio.h>
#include <stdlib.h>

int inp(){
	char c;
	while((c=getchar_unlocked())<'0' || c > '9');
	int num = c - '0';
	while((c=getchar_unlocked())>='0' && c<='9') num = num*10 + c - '0';
	return num;
}

struct PP {
	int petrol;
	int distance;
	struct PP* prev;
	struct PP* next;
};

struct PP* addPP(struct PP* tour, int petrol, int distance){
	struct PP* newPP = malloc(sizeof(struct PP));
	newPP->petrol = petrol;
	newPP->distance = distance;
	if (tour == NULL){
		newPP->prev = newPP;
		newPP->next = newPP;
		return newPP;
	}
	newPP->next = tour;
	newPP->prev = tour->prev;
	tour->prev->next = newPP;
	tour->prev = newPP;
	return tour;
}

void printPP(struct PP* tour, int n){
	if (tour == NULL) {
		printf("Tour is empty\n");
		return;
	}
	struct PP* curr = tour;
	for(int i=0; i<n; i++) {
		printf("%d) %d %d\n", i+1, curr->petrol, curr->distance);
		curr = curr->next;
	}
}

int checkPath(struct PP* tour, int n, int dir){
	int petrol = 0;
	for(int i=0; i<n; i++){
		petrol += tour->petrol - tour->distance;
		if(petrol < 0) return 0;
		tour = dir == 1 ? tour->next : tour->prev;
	}
	return 1;
}

int main(){
	int n = inp();
	struct PP* tour = NULL;
	for(int i=0; i<n; i++) {
		int petrol = inp();
		int distance = inp();
		tour = addPP(tour, petrol, distance);
	}
	// printPP(tour, n);
	for(int i=0; i<n; i++) {
		printf("%s\n", checkPath(tour, n, 1) || checkPath(tour, n, 0) ? "TAK" : "NIE");
		tour = tour->next;
	}
	return 0;
}