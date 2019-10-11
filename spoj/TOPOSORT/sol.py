import queue as Queue

def read_graph():
	n, m = [int(x) for x in input().split()]
	graph = [set() for _ in range(n)]
	for _ in range(m):
		x, y = [int(x) for x in input().split()]
		graph[x-1].add(y-1)
	return graph

def count_deps(graph):
	dep_count = [0 for _ in range(len(graph))]
	for node, children in enumerate(graph):
		for child in children:
			dep_count[child] += 1
	return dep_count

def top_sort(graph, dep_count):
	top_sorted = []
	queue = Queue.PriorityQueue()
	for i, c in enumerate(dep_count):
		if c == 0:
			queue.put(i)
	while len(top_sorted) < len(graph):
		# print(queue.qsize(), top_sorted)
		if queue.empty():
			return None
		node = queue.get()
		for child in graph[node]:
			dep_count[child] -= 1
			if dep_count[child] <= 0:
				queue.put(child)
		top_sorted.append(node+1)
	return top_sorted

if __name__ == '__main__':
	graph = read_graph()
	# print(graph)
	dep_count = count_deps(graph)
	# print(dep_count)
	top_sorted = top_sort(graph, dep_count)
	if top_sorted is None:
		print('Sandro fails.')
	else:
		print(' '.join([str(x) for x in top_sorted]))