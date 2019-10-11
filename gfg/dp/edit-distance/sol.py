'''
Find edit distance b/w to strings str1 and str2 defined as:
	The number of operations performed on str2 to make it identical to str1, operations being
	1) delete a character
	2) add a character
	3) replace a character
Cost of each operation is 1

Example:
	gesek -> geek
	add: gesek -> eek
	repl -> esek -> eek
	del -> 'esek' -> geek
'''

EMPTY = -123456

def edit_dist(str1, str2, saved):
	# If str1 is empty edit dist is len(str2)
	if len(str1) == 0:
		return len(str2)

	# If str2 is empty edit dist is len(str1)
	if len(str2) == 0:
		return len(str1)

	if saved[len(str1)-1][len(str2)-1] != EMPTY:
		return saved[len(str1)-1][len(str2)-1]

	# Add char
	add_dist = 1 + edit_dist(str1[1:], str2, saved)

	# Replace char
	repl_cost = 1 if str1[0] != str2[0] else 0
	repl_dist = repl_cost + edit_dist(str1[1:], str2[1:], saved)

	# Delete char
	del_dist = 1 + edit_dist(str1, str2[1:], saved)

	dist = min(add_dist, repl_dist, del_dist)
	saved[len(str1)-1][len(str2)-1] = dist
	return dist

def test():
	str1, str2 = ('geek', 'gessk')
	saved = [[EMPTY for j in range(len(str2))] for i in range(len(str1))]
	print(edit_dist(str1, str2, saved))


test()