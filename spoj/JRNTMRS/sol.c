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
	int res;
	struct PP* prev;
	struct PP* next;
};

struct PP* addPP(struct PP* tour, int petrol, int distance){
	struct PP* newPP = malloc(sizeof(struct PP));
	newPP->petrol = petrol;
	newPP->distance = distance;
	newPP->res = 0;
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

struct PP* getFirstTour(struct PP* tour, int n){
	struct PP *start=tour, *end=tour;
	int petrol = 0;
	int start_idx = 0, end_idx = 0;
	while (1){
		if (end == start && end_idx >= n) {
			start->res = 1;
			return start;
		}
		if (start_idx >= n) return NULL;
		petrol += end->petrol - end->distance;
		if (petrol < 0){
			start = end = end->next;
			start_idx = end_idx - end_idx+1;
			petrol = 0;
		} else {
			end = end->next;
			end_idx++;
		}
	}
}

void getAllTours(struct PP* first){
	struct PP* prev = first->prev;
	int def = 0;
	while(prev != first) {
		def += prev->distance - prev->petrol;
		if(def <= 0) {
			prev->res = 1;
			def = 0;
		}
		prev = prev->prev;
	}
}

int main(){
	int n = inp();
	struct PP* tour = NULL;
	for(int i=0; i<n; i++) {
		int petrol = inp();
		int distance = inp();
		tour = addPP(tour, petrol, distance);
	}
	struct PP* first = getFirstTour(tour, n);
	getAllTours(first);
	for(int i=0; i<n; i++) {
		printf("%s\n", tour->res ? "TAK": "NIE");
		tour = tour->next;
	}
	return 0;
}