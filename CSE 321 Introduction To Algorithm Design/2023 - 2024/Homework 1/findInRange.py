#Class for BST's nodes
class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
# It is traversing the tree and considering whether each node's value falls within, belov, or above the given range. 
# Depending on this comparison, it decides whether to search the left or right subtree or include the current node's value in the result. 
# The result list is then built up as the function traverses the tree, and it is returned once the traversal is complete.
def findInRange(root, start, end):
    result = []
    temp = []
    while root or temp:
        while root:
            if root.value >= start:
                temp.append(root)
            root = root.left

        root = temp.pop()

        if root.value > end:
            break

        if root.value >= start:
            result.append(root.value)

        root = root.right

    return result

#Test codes
root = Node(2)                                       #      2
root.left = Node(1)                                  #  1       3
root.right = Node(3)                                 #              6   
root.right.right = Node(6)                           #          5       7

root.right.right.left = Node(5)
root.right.right.right = Node(7)

start = 2
end = 5
list = findInRange(root, start, end)
print(f"Elements in the range [{start}, {end}]:", list)
