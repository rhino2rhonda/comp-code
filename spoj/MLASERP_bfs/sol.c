#include <stdio.h>
#include <stdlib.h>

#define EMPTY '.'
#define BLOCKED '*'
#define COW 'C'

#define W_MAX 100
#define H_MAX 100
#define LASERS_MAX 10001

enum direction {Left, Right, Up, Down, Begin};

int inp_num(){
	char c;
	while((c=getchar_unlocked()) < '0' || c > '9');
	int num = c-'0';
	while((c=getchar_unlocked()) >= '0' && c <= '9') num = (num*10) + (c-'0');
	return num; 
}

int inp_maze(){
	while(1){
		char c = getchar_unlocked();
		if(c == COW || c == EMPTY || c == BLOCKED) return c;
	}
}

struct grid {
	int i;
	int j;
	int type;
	int visited;
	int lasers;
	int incoming;
};

struct queue {
	struct grid* items[LASERS_MAX];
	int last;
	int first;
};

struct queue* new_queue(){
	struct queue* q = malloc(sizeof(struct queue));
	q->first = 0;
	q->last = -1;
	return q;
}

void add(struct queue* q, struct grid* g){
	q->items[++(q->last)] = g;
	// printf("Added to queue: %c %d %d last:%d\n", g->type, g->i, g->j, q->last);
}

struct grid* pop(struct queue* q){
	if (q->last < q->first) return NULL;
	return q->items[(q->first)++];
}

int search(struct grid maze[H_MAX][W_MAX], int H, int W, int cow_i, int cow_j){
	struct queue* q = new_queue();
	struct grid* cow = &maze[cow_i][cow_j], *g;
	cow->lasers = 0;
	add(q, cow);
	int temp=0;
	while((g=pop(q)) != NULL){
		// if(temp++ == 10) exit(1);
		g->visited = 1;
		// printf("popped: type:%c, lasers:%d, dir:%d, i:%d, j:%d\n", g->type, g->lasers, g->incoming, g->i, g->j);
		for(int x=Left; x<=Down; x++){
			int i=g->i, j=g->j;
			// printf("\tneigbour %d %d %d\n", x, i, j);
			switch(x){
				case Left:
					if(j--<=0) continue;
					break;
				case Right:
					if(j++>=W-1) continue;
					break;
				case Up:
					if(i--<=0) continue;
					break;
				case Down:
					if(i++>=H-1) continue;
					break;
			}
			// printf("\tneighbor: type:%c, visited:%d, lasers:%d, dir:%d, i:%d, j:%d\n", maze[i][j].type,
			 // maze[i][j].visited, maze[i][j].lasers, maze[i][j].incoming, maze[i][j].i, maze[i][j].j);
			if(maze[i][j].type == BLOCKED) continue;
			else if(maze[i][j].visited == 0) {
				maze[i][j].visited = 2;
				add(q, &maze[i][j]);
			} else if(maze[i][j].visited == 1){
				int lasers = maze[i][j].lasers;
				if(maze[i][j].incoming != x && maze[i][j].incoming != Begin) lasers++;
				if(g->lasers > lasers) {
					g->lasers = lasers;
					g->incoming = x;
					// printf("lasers updated %d %d\n", lasers, x);
				}
			}
		}
		if(g->type == COW && g != cow) return g->lasers;
	}
	return -1;
}

int main(){
	int W = inp_num();
	int H = inp_num();
	// printf("H:%d W:%d\n", H, W);
	struct grid M[H_MAX][W_MAX];
	int cow_i, cow_j;
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			M[i][j].type = inp_maze();
			M[i][j].i = i;
			M[i][j].j = j;
			M[i][j].visited = 0;
			M[i][j].incoming = Begin;
			M[i][j].lasers = LASERS_MAX;
			if (M[i][j].type == COW){
				cow_i = i;
				cow_j = j;
				// printf("cow_i:%d cow_j:%d\n", cow_i, cow_j);
			}
			// printf("%c ", M[i][j]);
		}
		// printf("\n");
	}
	printf("%d\n", search(M, H, W, cow_i, cow_j));
	return 0;
}