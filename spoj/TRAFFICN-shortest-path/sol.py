import heapq
import copy

class PriorityQueue:
	def __init__(self, mode='max-heap'):
		self._heap = []
		self._node_idx = {}
		self._node_prio = {}
		self.is_min_heap = mode == 'min-heap'

	def push(self, node, priority):
		if node in self._node_idx:
			if self._node_prio[node] == priority:
				return
			node_idx = self._node_idx[node]
			self._node_prio[node] = priority
			self._sift_up(node_idx)
			self._sift_down(node_idx)
		else:
			self._node_prio[node] = priority
			self._node_idx[node] = len(self)
			self._heap.append(node)
			self._sift_up(len(self)-1)

	def pop(self):
		extract = self._heap[0] 
		last_node = self._heap[-1]
		self._heap[0] = last_node
		self._node_idx[last_node] = 0
		self._heap.pop()
		self._sift_down(0)
		return extract

	@staticmethod
	def _parent_idx(child_idx):
		return int((child_idx - 1) / 2)

	@staticmethod
	def _child_idx(parent_idx):
		l = parent_idx * 2
		return l, l+1

	def _swap_nodes(self, node1_idx, node2_idx):
		node1, node2 = self._heap[node1_idx], self._heap[node2_idx]
		self._heap[node1_idx], self._heap[node2_idx] = node2, node1
		self._node_idx[node1], self._node_idx[node2] = node2_idx, node1_idx

	def _prio_valid(self, parent, child):
		return parent <= child if self.is_min_heap else parent >= child

	def _sift_up(self, node_idx):
		while node_idx > 0:
			parent_idx = self._parent_idx(node_idx)
			child_prio = self._node_prio[self._heap[node_idx]]
			parent_prio = self._node_prio[self._heap[parent_idx]]
			if self._prio_valid(parent_prio, child_prio):
				break
			self._swap_nodes(node_idx, parent_idx)
			node_idx = parent_idx

	def _sift_down(self, node_idx):
		while node_idx < len(self):
			child_l_idx, child_r_idx = self._child_idx(node_idx)
			parent_prio = self._node_prio[self._heap[node_idx]]
			
			if child_l_idx >= len(self):
				break
			child_l_prio = self._node_prio[self._heap[child_l_idx]]
			child_r_prio = None if child_r_idx >= len(self) else self._node_prio[self._heap[child_r_idx]]

			next_prio, next_idx = parent_prio, node_idx
			if not self._prio_valid(parent_prio, child_l_prio):
				next_prio, next_idx = child_l_prio, child_l_idx
			if child_r_prio is not None and not self._prio_valid(next_prio, child_r_prio):
				next_prio, next_idx = child_r_prio, child_r_idx

			if parent_prio == next_prio:
				break
			self._swap_nodes(node_idx, next_idx)
			node_idx = next_idx

	def __len__(self):
		return len(self._heap)


	def __str__(self):
		return str(self._heap)

def read_ints():
	return [int(x) for x in input().split()]

def read_test_case():
	n, m, k, s, t = read_ints()
	s-=1
	t-=1
	
	graph1 = [[] for _ in range(n)]
	for _ in range(m):
		d, c, l = read_ints()
		graph1[d-1].append((c-1, l))

	graph2 = [[] for _ in range(n)]
	for _ in range(k):
		d, c, l = read_ints()
		graph2[d-1].append((c-1, l))
		graph2[c-1].append((d-1, l))

	return m, n, k, s, t, graph1, graph2

EMPTY = -123456
def shortest_path(graph, s, t):
	best_paths = [EMPTY for _ in range(len(graph))]
	visited = [False for _ in range(len(graph))]
	best_paths[s] = 0
	
	ready = PriorityQueue(mode='min-heap')
	ready.push(s, 1)
	
	while len(ready) > 0:
		node = ready.pop()
		if node == t:
			return best_paths[node]

		for neighbor, road_len in graph[node]:
			if visited[neighbor]:
				continue
			next_path = best_paths[node] + road_len
			if best_paths[neighbor] == EMPTY or best_paths[neighbor] > next_path:
				best_paths[neighbor] = next_path
			ready.push(neighbor, best_paths[neighbor])

		visited[node] = True

	return -1

def merge_graphs(graph1, graph2, s, t):
	graph1.extend(copy.deepcopy(graph1))
	for i in range(len(graph2), 2*len(graph2)):
		for j in range(len(graph1[i])):
			node, l = graph1[i][j]
			graph1[i][j] = node + len(graph2), l
	for i in range(len(graph2)):
		for j in range(len(graph2[i])):
			node, l = graph2[i][j]
			graph1[i].append((node + len(graph2), l))
	graph1[t + len(graph2)].append((t, 0))

def run():
	num_tests = read_ints()[0]
	for _ in range(num_tests):
		m, n, k, s, t, graph1, graph2 = read_test_case()
		# print(m, n, k, s, t)
		merge_graphs(graph1, graph2, s, t)
		# print(graph1)
		print(shortest_path(graph1, s, t))	

run()
