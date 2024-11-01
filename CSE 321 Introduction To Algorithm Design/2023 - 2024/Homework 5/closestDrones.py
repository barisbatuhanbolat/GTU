from math import sqrt

# Class for representing point in two dimensional plane
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

# This function calculates the Euclidean distance between two points in a given list.
def dist(points,i,j):
    return sqrt((points[i].x-points[j].x)**2 + (points[i].y-points[j].y)**2)

# This function finds the minimum distance between points in the strip of a given width.
def stripClosest(strip, d):
    min_dist = d
    n = len(strip)
    for i in range(0,n-1) :
        mint = i
        for j in range(i+1,n) :
            if strip[j].y < strip[mint].y :
                mint = j
            temp = strip[mint]
            strip[mint] = strip[i]
            strip[i] = temp
    for i in range(n):
        for j in range(i+1, n):
            if (strip[j].y  - strip[i].y ) >= min_dist:
                break
            min_dist = min(min_dist, dist(strip,i,j))
    return min_dist

# This helper recursive utility function to find the minimum distance between points in a drones list.
def closestDronesUtil(drones):
    n = len(drones)
    if n == 0 or n == 1 :
        return 0
    if n == 2 :
        return dist(drones,0,1)
    if n == 3 :
        return min(dist(drones,0,1) , dist(drones,0,2) , dist(drones,1,2))
    
    dl = closestDronesUtil(drones[:n//2])
    dr = closestDronesUtil(drones[n//2:])
    d = min(dl,dr)
    mid = drones[n//2]
    strip = []

    for i in range(n):
        if abs(drones[i].x - mid.x) < d:
            strip.append(drones[i])
    return min(d, stripClosest(strip, d))

# This function finds the minimum distance between any two drones in a list.
def closestDrones(drones):
    n = len(drones)
    for i in range(0,n-1) :
        mint = i
        for j in range(i+1,n) :
            if drones[j].x < drones[mint].x :
                mint = j
            temp = drones[mint]
            drones[mint] = drones[i]
            drones[i] = temp

    return closestDronesUtil(drones)
        
# Test Codes
drones = [Point(0,1),Point(2,3),Point(4,5),Point(-2,5),Point(-4,0)]
distance = closestDrones(drones)
print(f"Minimum distance: {distance}")