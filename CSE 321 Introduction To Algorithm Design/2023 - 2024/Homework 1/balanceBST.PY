#Class for BST's nodes
class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
# Converts a sorted list of values into a balanced Binary Search Tree (BST). 
# It achieves this by selecting the middle element of the list as the root of the tree and 
# recursively building the left and right subtrees using the elements to the left and right of the middle element.
def listToBST(list,start,end):
    if start <= end:
        mid = (start + end) // 2
        root = Node(list[mid])
        root.left = listToBST(list, start, mid - 1)
        root.right = listToBST(list, mid + 1, end)
        return root
    return None 

# Perform in-order traversal on a BST and add nodes to the given list.
def inorderTraversal(root, result):
    if root:
        inorderTraversal(root.left, result)
        result.append(root.value)
        inorderTraversal(root.right, result)
# Balances a given BST by first performing an in-order traversal to extract the nodes in sorted order. 
# It then calls the listToBST function to create a new balanced BST from the sorted list of nodes. 
def balanceBST(root):
    list = []
    inorderTraversal(root, list)
    return listToBST(list,0,len(list) - 1)

# Prints the tree as balanced    
def printTree(root):
    if root:
        printTree(root.left)
        print(root.value, end=' ')
        printTree(root.right)

#Test codes
root3 = Node(1)
root3.right = Node(2)
root3.right.right = Node(3)
root3.right.right.right = Node(4)
root3.right.right.right.right = Node(5)

root4 = balanceBST(root3)
printTree(root4)
