#Class for BST's nodes
class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

# Merge two Binary Search Trees (BSTs) into a single balanced BST.
# It performs in-order traversal for creating lists from trees and it stores them into an empty lists named list. 
# And with helper function it merges two lists.
def mergeBST(root1, root2):
    list = []
    inorderTraversal(root1, list)
    inorderTraversal(root2, list)
    return mergeBSTHelper(list,0,len(list) - 1)

# Perform in-order traversal on a BST and add nodes to the given list.
def inorderTraversal(node, list):
    if node:
        inorderTraversal(node.left, list)
        list.append(node.value)
        inorderTraversal(node.right, list)
    return
# Constructs a balanced BST from a sorted list of elements. 
# It recursively divides the list of elements into two halves, selects the middle element as the root, and constructs the left and right subtrees similarly.
def mergeBSTHelper(list, start, end):
    if start <= end:
        mid = (start + end) // 2
        root = Node(list[mid])
        root.left = mergeBSTHelper(list, start, mid - 1)
        root.right = mergeBSTHelper(list, mid + 1, end)
        return root
    return None    
# Prints the tree as balanced    
def printTree(root):
    if root:
        printTree(root.left)
        print(root.value, end=' ')
        printTree(root.right)

#Test codes
root1 = Node(2)
root1.left = Node(1)
root1.right = Node(3)

root2 = Node(6)
root2.left = Node(5)
root2.right = Node(7)

mergedTree = mergeBST(root1, root2)

printTree(mergedTree)
