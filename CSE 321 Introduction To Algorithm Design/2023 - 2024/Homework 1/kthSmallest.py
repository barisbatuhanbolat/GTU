#Class for BST's nodes
class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

# Utilizes an iterative in-order traversal approach with a stack.
# It starts by traversing as far left as possible in the tree to find the smallest element.
# As it traverses the tree, it decrements the value of 'k' for each node encountered.
# When 'k' becomes zero, the function returns the value of the kth smallest element.
def kthSmallest(root, k):
    stack = []
    current = root    
    while True:
        while current:
            stack.append(current)
            current = current.left        
        current = stack.pop()
        k -= 1
        if k == 0:
            return current.value        
        current = current.right

#Test codes
root = Node(2)                                       #      2
root.left = Node(1)                                  #  1       3
root.right = Node(3)                                 #             6                                                    
root.right.right = Node(6)                           #          5     7         
root.right.right.left = Node(5)
root.right.right.right = Node(7)

k = 3
kthSmallest_element = kthSmallest(root, k)
print(f"{k}th smallest element:", kthSmallest_element) 