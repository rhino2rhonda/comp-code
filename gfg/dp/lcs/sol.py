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

	# DP
	res = [[0 for a in range(len(A))] for b in range(len(B))]
	lcs = [['' for a in range(len(A))] for b in range(len(B))]

	for i in range(len(A)):
		for j in range(len(B)):
			def _get_r(pi, pj):
				r = res[pj][pi] if pi >= 0 and pj>=0 else 0
				l = lcs[pj][pi] if pi >= 0 and pj>=0 else ''
				return r, l
			r1, l1 = _get_r(i-1, j-1)
			if A[i] == B[j]:
				r1 += 1
				l1 += A[i]
			r2, l2 = _get_r(i, j-1)
			r3, l3 = _get_r(i-1, j)
			if r1 > r2 and r1 > r3:
				res[j][i] = r1
				lcs[j][i] = l1
			elif r2 > r1 and r2 > r3:
				res[j][i] = r2
				lcs[j][i] = l2
			else:
				res[j][i] = r3
				lcs[j][i] = l3
	print(res[len(B)-1][len(A)-1], lcs[len(B)-1][len(A)-1])