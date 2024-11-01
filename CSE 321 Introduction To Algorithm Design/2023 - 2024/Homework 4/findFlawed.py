# Custom class for fuse.
# I use this classes instance variable "isFlawed" to check flawity of a fuse. 
class fuse:
    def __init__(self, isFlawed):
        self.isFlawed = isFlawed

# This function uses binary search algorithm to reduce the search space to find flawed fuse.
def findFlawed(fuses):
    left = 0
    right = len(fuses) - 1
    while left <= right:
        mid = (left + right) // 2
        if fuses[mid].isFlawed == False:
            left = mid + 1
        else:
            right = mid - 1
    return left 


# Test example
fuse1 = fuse(False)
fuse2 = fuse(False)
fuse3 = fuse(False)
fuse4 = fuse(True)
fuse5 = fuse(False)

fuses = [fuse1,fuse2,fuse3,fuse4,fuse5]
index = findFlawed(fuses)

print(index)