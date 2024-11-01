# Class for representing point in two dimensional plane
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

# Class for representing antennas on streets
class Antenna:
    def __init__(self, leftPoint, rightPoint):
        self.leftPoint = leftPoint
        self.rightPoint = rightPoint
        
# This function sorts the antennas based on their rightmost point's x-coordinate.
# It then finds and returns the set of non-overlapping antennas that cover the maximum
def maxAntennas(antennas):
    n = len(antennas)
    for i in range(n-1) :
        mint = i
        for j in range (i+1,n) :
            if antennas[j].rightPoint.x < antennas[mint].rightPoint.x :
                mint = j
            temp = antennas[mint]
            antennas[mint] = antennas[i]
            antennas[i] = temp


    actives = []
    currentRightX = -999999

    for antenna in antennas:
        if antenna.leftPoint.x > currentRightX:
            actives.append(antenna)
            currentRightX = antenna.rightPoint.x

    return actives

# Test Codes
antenna1 = Antenna(Point(1, 3), Point(4, 6))
antenna2 = Antenna(Point(2, 4), Point(6, 2))
antenna3 = Antenna(Point(5, 5), Point(8, 7))

antennas = [antenna1, antenna2, antenna3]

result = maxAntennas(antennas)

print("Activated Antennas:")
for antenna in result:
    print(f"Left Point: ({antenna.leftPoint.x}, {antenna.leftPoint.y}), "
          f"Right Point: ({antenna.rightPoint.x}, {antenna.rightPoint.y})")
