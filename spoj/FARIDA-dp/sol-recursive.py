def solve(m, M, mem):
	if m >= len(M):
		return 0
	if m == len(M)-1:
		return M[m]
	if mem[m] is not None:
		return mem[m]
	m1 = M[m] + solve(m+2, M, mem)
	m2 = M[m+1] + solve(m+3, M, mem)
	mem[m] = max(m1, m2)
	return mem[m]

T = int(input())
for t in range(T):
	m = int(input())
	M = [int(x.strip()) for x in input().split()]
	mem = [None for x in range(m)]
	print("Case {}: {}".format(t+1, solve(0, M, mem)))