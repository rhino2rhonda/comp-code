# These approaches did not work as they are too heavy on memory and time

class Data:

	def __init__(self):
		self.tot = int(input())
		self.numA = int(input())
		self.monksA = []
		for _ in range(self.numA): # compare with xrange
			self.monksA.append(Monkey(*[int(x) for x in input().split()]))
		self.numB = int(input())
		self.monksB = []
		for _ in range(self.numB):
			self.monksB.append(Monkey(*[int(x) for x in input().split()]))

class Monkey:

	def __init__(self, a, b):
		self.a = a
		self.b = b
		self.curr = None

	def next(self, set_curr=False):
		if self.curr is None:
			next_ = self.a
		else:
			next_ = self.curr + self.b
		if set_curr:
			self.curr = next_
		return next_

# d = Data()
# for m in d.monksA + d.monksB:
# 	print(m.__dict__)

def solve(d):
	tA = tB = 0
	while True:

		# Monkey picks a coconut
		min_m = min_t = None
		for m in d.monksA:
			next_t = m.next()
			if min_t is None or min_t > next_t:
				min_m, min_t = m, next_t
		min_m.curr = tA = min_t

		# Monkey opens a coconut
		min_m = min_t = None
		for m in d.monksB:
			next_t = m.next()
			if min_t is None or min_t > next_t:
				min_m, min_t = m, next_t
		min_m.curr = tB = min_t

		if tA + tB == d.tot:
			print(tA)
			break
		if tA + tB > d.tot:
			raise Exception('Not supposed to happen')

def solve_sorted(d):
	monksA = []
	for m in d.monksA:
		while m.curr is None or m.curr < d.tot:
			monksA.append(m.next(True))
	monksB = []
	for m in d.monksB:
		while m.curr is None or m.curr < d.tot:
			monksB.append(m.next(True))
	monksA.sort()
	monksB.sort()
	c = tA = tB = 0
	while True:
		tA = monksA[c]
		tB = monksB[c]
		c+=1
		if tA + tB == d.tot:
			print(tA)
			break
		if tA + tB > d.tot:
			raise Exception('Not supposed to happen')

def solve_sorted_binary(d):
	monksA = []
	for m in d.monksA:
		while m.curr is None or m.curr < d.tot:
			monksA.append(m.next(True))
	monksB = []
	for m in d.monksB:
		while m.curr is None or m.curr < d.tot:
			monksB.append(m.next(True))
	monksA.sort()
	monksB.sort()
	lo=0
	hi=len(monksA)
	res = None
	print(monksA[:20])
	print(monksB[:20])
	while hi > lo:
		mid = int((hi + lo) / 2)
		tA = monksA[mid]
		tB = monksB[mid]
		print(hi, lo, mid, tA, tB)
		if tA + tB > d.tot:
			hi = mid
		elif tA + tB < d.tot:
			lo = mid
		else:
			res = tA
			break
	if res is None:
		raise Exception('Should not have happened')
	else:
		print(res)

d = Data()
solve_sorted_binary(d)