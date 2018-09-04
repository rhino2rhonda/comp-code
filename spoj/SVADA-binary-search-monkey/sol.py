# Binary search working solution in Python 3

from functools import reduce

class Data:

	def __init__(self):
		self.tot = int(input())
		self.numA = int(input())
		self.monksA = []
		for _ in range(self.numA):
			self.monksA.append(Monkey(*[int(x) for x in input().split()]))
		self.numB = int(input())
		self.monksB = []
		for _ in range(self.numB):
			self.monksB.append(Monkey(*[int(x) for x in input().split()]))

class Monkey:

	def __init__(self, a, b):
		self.a = a
		self.b = b

	def get_cocos(self, t):
		cocos = 1 if t >= self.a else 0
		cocos += int(max(0, t - self.a) / self.b)
		return cocos

def get_all_cocos(monks, t):
	return reduce(lambda a,b: a+b, map(lambda m: m.get_cocos(t), monks))

def solve(d):
	lo = 0
	hi = d.tot
	res = None
	while hi >= lo:
		mid = int((hi + lo) / 2)
		cocosA = get_all_cocos(d.monksA, mid)
		cocosB = get_all_cocos(d.monksB, d.tot-mid)
		# print(lo, mid, hi, cocosA, cocosB)
		if cocosA > cocosB:
			hi = mid - 1
		else:
			res = mid
			lo = mid + 1
	if res is None:
		raise Exception('Should not have happened')
	else:
		print(res)

d = Data()
solve(d)