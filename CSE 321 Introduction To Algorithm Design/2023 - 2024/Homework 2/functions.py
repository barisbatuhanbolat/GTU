# Class for tree nodes
class TreeNode:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
# Detects and retun the maximum of two numbers.
def max(x,y):
    if x > y:
        return x
    return y
# Returns the absolute value of a number.
def abs(x):
    if x < 0:
        return -1*x
    return x

# Recursively calculate the height of the left and right subtrees and return the maximum height plus 1 for the current level.
# The average case time complexity of this function is O(n)
def height_of_tree(root):
    if root is None:
        return 0
    else:
        return 1 + max(height_of_tree(root.left), height_of_tree(root.right))
    
# Calculate the height of the left and right subtrees
# Check if the tree is balanced by comparing the heights of the left and right subtrees. Also, recursively check the balance of the leftand right subtrees.
# The average case time complexity of this function is O(n log n)
def is_balanced(root):
    if root is None:
        return True

    lh = height_of_tree(root.left)
    rh = height_of_tree(root.right)

    return abs(lh - rh) <= 1 and is_balanced(root.left) and is_balanced(root.right)

#Test codes
root = TreeNode(1)
root.left = TreeNode(2)
root.right = TreeNode(3)
root.left.left = TreeNode(4)
root.left.right = TreeNode(5)
root.right.right = TreeNode(6)
root.left.left.left = TreeNode(7)

print("Height:", height_of_tree(root))
print("Is tree balanced?", is_balanced(root))
