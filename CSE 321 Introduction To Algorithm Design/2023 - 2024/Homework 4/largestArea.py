# Helper function to calculate area between two interval
def area(f, start, end):
  total = 0
  for x in range(start, end + 1):
    total += f[x]
  return total
# The function efficiently identifies and returns the maximum total area under the function 
# represented by the array f within the specified interval [start, end] using a decrease and conquer strategy.
def largestArea(f, start, end):
  max_area = area(f, start, end)
  while start < end:
    if area(f, start + 1, end) > area(f, start, end - 1): 
      start += 1 
    else: 
      end -= 1 
    
    current_area = area(f, start, end) 
    if current_area > max_area: 
      max_area = current_area 
  return max_area 

# Test example
f = [2,1,2,-2,1,-1,1]
start = 0
end  = 3
print(f"The maximum total area {[start,end]}: {largestArea(f,0,3)}")

