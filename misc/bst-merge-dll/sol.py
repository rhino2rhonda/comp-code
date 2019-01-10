import random
import copy

TC = 100
MAX_N = 500
MAX_VAL = 1000

# Unique Random Number Generator

class RandomGenerator:

	def __init__(self):
		self.mem = {}

	def randint(self, a, b):
		while True:
			r = random.randint(a, b)
			if r not in self.mem:
				self.mem[r] = 1
				return r

randgen = None

# BST utils

class BST:

	def __init__(self, val):
		self.val = val
		self.left = self.right = None

	def insert(self, val):
		if (val < self.val):
			self.left = BST(val) if self.left is None else self.left.insert(val)
		elif (val > self.val):
			self.right = BST(val) if self.right is None else self.right.insert(val)
		return self

	def get_inorder(self):
		arr = [] if self.left is None else self.left.get_inorder()
		arr.append(self.val)
		arr.extend([] if self.right is None else self.right.get_inorder())
		return arr

def gen_random_tree(n):
	bst = BST(randgen.randint(0, MAX_VAL))
	for i in range(n-1):
		bst.insert(randgen.randint(0, MAX_VAL))
	return bst

def merge_bad(bst1, bst2):
	bst = copy.deepcopy(bst1)
	for e in bst2.get_inorder():
		bst.insert(e)
	return bst

# Doubly linked list utils

class DLL:

	def __init__(self, val):
		self.val = val;
		self.prev = self.next = self

	def insert_next(self, dll):
		dll.prev = self
		dll.next = self.next
		self.next.prev = dll
		self.next = dll

	def remove_prev(self):
		temp = self.prev
		temp.prev.next = self
		self.prev = temp.prev
		return temp

	def to_array(self):
		head = self
		cur = self.next
		arr = [self.val]
		while cur is not head:
			arr.append(cur.val)
			cur = cur.next
		return arr


def join_dll(l1, l2):
	if l1 is None:
		return l2
	if l2 is None:
		return l1
	l1.prev.next = l2
	l2.prev.next = l1
	l1.prev, l2.prev = l2.prev, l1.prev
	return l1

def merge_sorted_dll(l1, l2, n1, n2):
	c1 = c2 = 0
	cur1 = l1
	cur2 = l2
	while(c1 < n1 or c2 < n2):
		# print("dbg", cur1.val, cur2.val, c1, c2, n1, n2)
		if c2 >= n2 or (c1 < n1 and cur1.val < cur2.val):
			c1 += 1
			cur1 = cur1.next
		else:
			c2 += 1
			cur2 = cur2.next
			cur1.prev.insert_next(cur2.remove_prev())
	return cur1

# Conversion utils

def bst2dll(bst):
	if bst is None:
		return None
	return join_dll(join_dll(bst2dll(bst.left), DLL(bst.val)), bst2dll(bst.right))

def dll2bst(dll, n):
	if n < 1:
		return None
	elif n == 1:
		return BST(dll.val), dll.next
	l = int((n-1)/2)
	if l > 0:
		bstl, dll = dll2bst(dll, l)
	else:
		bstl = None
	bst = BST(dll.val)
	bst.left = bstl
	r = n - 1 - l
	if r > 0:
		bst.right, dll = dll2bst(dll.next, r)
	return bst, dll

def run():
	global randgen
	for t in range(TC):
		randgen = RandomGenerator()
		n1 = randgen.randint(1, MAX_N)
		n2 = randgen.randint(1, MAX_N)
		bst1 = gen_random_tree(n1)
		bst2 = gen_random_tree(n2)
		bst_test = merge_bad(bst1, bst2)
		l1 = bst2dll(bst1)
		l2 = bst2dll(bst2)
		dll = merge_sorted_dll(l1, l2, n1, n2)
		# print(dll.to_array())
		bst, _ = dll2bst(dll, n1+n2)
		# print(bst.get_inorder())
		# print(bst_test.get_inorder())
		if bst.get_inorder() == bst_test.get_inorder():
			# print("YOLO")
			pass
		else:
			print("STFU")

if __name__ == '__main__':
	run()


