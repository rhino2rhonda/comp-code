#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <set>

#define EMPTY -123456
#define DONE -654321

using namespace std;

void printGraph(vector<vector<pair<int,int> > > graph, int n) {
	for (int i=0; i<n; i++) {
		for (vector<pair<int,int>>::iterator itr=graph[i].begin(); itr != graph[i].end(); itr++) {
			pair<int, int> node = *itr;
			cout << "Ef:" << i << " Et:" << node.first << " Length:" << node.second << endl;
		}
	}
}

// struct compareNodes {
// 	bool operator()(const pair<int,int*> a, const pair<int,int*> b) { 
// 		cout << "dbg " << a.first << " " << *(a.second) << " " << b.first << " " << *(b.second) << endl;
// 	    return *(a.second) > *(b.second); 
// 	}
// };

struct CompareNodes {
	CompareNodes(vector<int> best_paths) {
		this->best_paths = best_paths;
	}
	~CompareNodes() = default;
	vector<int> best_paths;
	bool operator()(const int& a, const int& b) { 
		return this->best_paths[a] < this->best_paths[b];
	}
};

int shortestPath(vector<vector<pair<int,int> > > graph, int n, int s, int t) {
	cout << n << " " << s << " " << t << endl;
	vector<int> best_paths(n);
	for (int i=0; i<n; i++) best_paths[i] = EMPTY;
	best_paths[s] = 0;

	// priority_queue<pair<int, int*>, vector<pair<int, int*> >, compareNodes> ready;
	// pair<int, int*> s_ready;
	// s_ready.first = s;
	// s_ready.second = &best_paths[s];
	// ready.push(s_ready);
	// set<int> queued;
	// queued.insert(s);
	set<int, CompareNodes(best_paths) > ready;
	ready.insert(s);

	while (!ready.empty()) {
		// cout << "ready length: " << ready.size() << endl;
		int node = *(ready.begin);
		cout << "Node popped: " << node << endl;
		ready.erase(node);
		// queued.erase(node);

		int best_path = best_paths[node];
		cout << "Best Path: " << best_path << endl;
		best_paths[node] = DONE;
		if (node == t) return best_path;

		for (vector<pair<int,int>>::iterator itr=graph[node].begin(); itr != graph[node].end(); itr++) {
			pair<int, int> neighbor = *itr;
			int n_node = neighbor.first;
			int r_length = neighbor.second;
			if (best_paths[n_node] == DONE) continue;
			// cout << "Debug1" << endl;
			// if (queued.find(n_node) == queued.end()) {
			// 	pair<int, int*> n_pair;
			// 	n_pair.first = n_node;
			// 	n_pair.second = &best_paths[n_node];
			// 	ready.push(n_pair);
			// 	queued.insert(n_node);
			// }
			int next_path = best_path + r_length;
			if (best_paths[n_node] == EMPTY || best_paths[n_node] > next_path)
				best_paths[n_node] = next_path;
			if (ready.find(n_node) != queued.end()) ready.erase(n_node);
			ready.insert(n_node);
		}
	}
	return -1;
}

int main() {
	int t;
	cin >> t;
	while(t--) {
		int n, m, k, s, t;
		cin >> n >> m >> k >> s >> t;
		s--; t--;
		cout << "n:"<< n << " m:" << m << " k:" << k << " s:" << s << " t:" << t << endl;

		vector<vector<pair<int,int> > > graph(n);
		for (int i=0; i<m; i++) {
			int d;
			pair<int, int> node;
			cin >> d >> node.first >> node.second; // first: neighbor node, second: road length
			d--; node.first--;
			graph[d].push_back(node);
		}

		printGraph(graph, n);
		cout << shortestPath(graph, n, s, t) << endl;
	}
	return 0;
}