from sys import stdin

def solve(M):
	gold = 0
	mem_p1 = mem_p2 = None
	for curr, m_curr in enumerate(M):
		if curr == 0:
			gold = m_curr
		elif curr == 1:
			gold = max(m_curr, mem_p1)
		else:
			gold = max(m_curr + mem_p2, mem_p1)
		mem_p2 = mem_p1
		mem_p1 = gold
	return gold

inp = stdin.readlines()
T = int(inp[0])
for t in range(T):
	# m = int(inp[(2*t)+1])
	M = map(int, reversed(inp[2*(t+1)].split()))
	print("Case {}: {}".format(t+1, solve(M)))