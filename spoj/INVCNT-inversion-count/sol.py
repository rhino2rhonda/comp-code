def get_test_cases():
	t = int(input())
	input()
	for _ in range(t):
		n = int(input())
		A = []
		for _ in range(n):
			A.append(int(input()))
		yield A
		try:
			input()
		except:
			pass

def merge(A, B):
	a = b = 0
	C = []
	inv = 0
	while a < len(A) or b < len(B):
		if a >= len(A) or (b < len(B) and A[a] > B[b]):
			inv += len(A) - a
			C.append(B[b])
			b += 1
		else:
			C.append(A[a])
			a += 1
		# print(a, b, C[-1], a >= len(A) or (b < len(B) and A[a] > B[b]))
	return C, inv

def merge_sort(X):
	if len(X) <= 1:
		return X, 0
	mid = int(len(X)/2)
	A, invA = merge_sort(X[:mid])
	B, invB = merge_sort(X[mid:])
	sorted_, inv = merge(A, B)
	return sorted_, inv + invA + invB

# print(merge_sort([1,2,3,4,5,6,8,10,9]))

for t in get_test_cases():
	print(merge_sort(t)[1])