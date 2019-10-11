import functools as ft

class TopSortException(Exception):
	pass

def read_deps():
	n, m = [int(x) for x in input().split()]
	deps = [set() for _ in range(n)]
	for _ in range(m):
		x, y = [int(x) for x in input().split()]
		deps[y-1].add(x-1)
	return deps

def _top_sort_dfs(curr, deps, state, top_sorted):
	if state[curr] == 2:
		return
	if state[curr] == 1:
		raise TopSortException('Dependency loop detected')
	state[curr] = 1
	for next_ in sorted(deps[curr]):
		_top_sort_dfs(next_, deps, state, top_sorted)
	state[curr] = 2
	top_sorted.append(curr + 1)

def top_sort(deps, mode='dfs'):
	state = [0 for _ in deps]
	if mode == 'dfs':
		top_sorted = []
		for curr in range(len(deps)):
			_top_sort_dfs(curr, deps, state, top_sorted)
	elif mode == 'bfs':
		print(deps)
		for curr in range(len(deps)):
			_enumerate_all_deps(curr, deps, state)
		print(deps)
		top_sorted = _top_sort_bfs(deps)
	return top_sorted

if __name__ == '__main__':
	deps = read_deps()
	try:
		top_sorted = top_sort(deps, mode='dfs')
		print(' '.join([str(x) for x in top_sorted]))
	except TopSortException:
		print('Sandro fails.')