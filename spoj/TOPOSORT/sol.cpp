#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

#define MAX_V 10000
#define INVALID_GRAPH -123456

int read_int() {
	char c;
	while((c = getchar_unlocked()) < '0' | c > '9');
	int num = c - '0';
	while((c = getchar_unlocked()) >= '0' && c <= '9') num = (num*10) + (c = '0');
	return num;
}

void printGraph(set<int> graph[], int v) {
	cout << "Graph" << endl;
	for (int node=0; node<v; node++) {
		for (set<int>::iterator itr = graph[node].begin(); itr != graph[node].end(); itr++) {
			cout << "Node: " << node << " Child: " << *itr << endl;
		}
	}
}

void printDepCounts(int dep_counts[], int v) {
	cout << "Dep Counts" << endl;
	for (int i=0; i<v; i++) {
		cout << "Node: " << i << " Deps: " << dep_counts[i] << endl;
	}
}

void countDeps(set<int> graph[], int v, int dep_counts[]) {
	for (int node=0; node<v; node++) {
		for (set<int>::iterator itr = graph[node].begin(); itr != graph[node].end(); itr++) {
			dep_counts[*itr]++;
		}
	}
}

void top_sort(set<int> graph[], int dep_counts[], int v, int top_sorted[]) {
	priority_queue<int, vector<int>, greater<int> > ready;
	for (int node=0; node<v; node++) {
		if (dep_counts[node] == 0) ready.push(node);
	}
	for (int i=0; i<v; i++) {
		if (ready.empty()) throw INVALID_GRAPH;
		int node = ready.top();
		ready.pop();
		for (set<int>::iterator itr = graph[node].begin(); itr != graph[node].end(); itr++) {
			dep_counts[*itr]--;
			if (dep_counts[*itr] == 0) ready.push(*itr);
		}
		top_sorted[i] = node + 1;
	}
}

int main() {
	int v = read_int();
	int e = read_int();

	set<int> graph[MAX_V];
	for (int i=0; i<e; i++) {
		int x = read_int();
		int y = read_int();
		graph[x-1].insert(y-1);
	}
	// printGraph(graph, v);

	int dep_counts[MAX_V];
	countDeps(graph, v, dep_counts);
	// printDepCounts(dep_counts, v);

	int top_sorted[MAX_V];
	try {
		top_sort(graph, dep_counts, v, top_sorted);

		// Print sorted
		for (int i=0; i<v-1; i++) {
			cout << top_sorted[i] << " ";
		}
		cout << top_sorted[v-1] << endl;
	}
	catch(int err) {
		if (err = INVALID_GRAPH) {
			cout << "Sandro fails." << endl;
		} else {
			throw err;
		}
	}

	return 0;
}