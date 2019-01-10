def check_avl(bst):
	h = [[0,0] for _ in range(len(bst))]
	for i in reversed(range(len(bst))):
		if(bst[i] == -1):
			continue
		# print("dbg1", i, h[i])
		if abs(h[i][0] - h[i][1]) > 1:
			return False
		if i <= 0:
			break
		p = int((i-1)/2)
		h[p][i%2] = max(h[i][0], h[i][1]) + 1
		# print("dbg2", p, h[p])
	return True

T = int(input());

for t in range(T):
	bst = [int(x.strip()) for x in input().split()]
	print('T' if check_avl(bst) else 'F')
	# break
