# Utils

debug = False
def prnt(*args, **kwargs):
	if debug:
		print(*args, **kwargs)

# Read input

n_tc = int(input())
if debug:
	prnt('T')

for id_tc in range(1, n_tc+1):
	prnt('TC', id_tc)
	A = input().strip()
	prnt('A', A)
	B = input().strip()
	prnt('B', B)

	# Brute
	def enumerate_subsequences(X):
		# print(X)
		if len(X) == 0:
			return []
		elif len(X) == 1:
			return ['', X]
		subseqs = enumerate_subsequences(X[1:])
		prnt('dbg', subseqs, X)
		return [*subseqs, *[X[0] + s for s in subseqs]]

	seq_A = enumerate_subsequences(A)
	seq_B = enumerate_subsequences(B)
	best = 0, ''
	# print(len(seq_A), len(seq_B))
	for a in seq_A:
		for b in seq_B:
			if a == b and len(a) > best[0]:
				best = len(a), a
	print(*best)	
