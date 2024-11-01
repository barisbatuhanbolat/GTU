# The funciton devides the tasks list into two halves recursively at each step to
# find maximum and minimum resources.
def allocateResources(tasks):
    if len(tasks) == 0:
        return 0, 0
    if len(tasks) == 1:
        return tasks[0], tasks[0]
    
    mid = len(tasks) // 2

    left = tasks[0:mid]
    right = tasks[mid:len(tasks)]

    left_max, left_min = allocateResources(left)
    right_max, right_min = allocateResources(right)

    max_resources = max(left_max, right_max)
    min_resources = min(left_min, right_min)

    return max_resources, min_resources

# Test Example
tasks = [8,20,10,15,2]

max_resources, min_resources = allocateResources(tasks)

print(f"Minimum resources needed: {min_resources}")
print(f"Maximum resources needed: {max_resources}")