# Class for representing point in two dimensional plane
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

# This helper recursive utility function to find the minimum number of sensors needed to cover a given set of sensors horizontally.
def minSensorsUtil(sensors):
    n = len(sensors)
    if n == 0 :
        return 0
    if n == 1 :
        return 1
    mid = n//2

    leftSensors = minSensorsUtil(sensors[:mid])
    rightSensors = minSensorsUtil(sensors[mid:])

    count = min(leftSensors, rightSensors)

    leftSensor = sensors[mid - 1]
    rightSensor = sensors[mid]

    for sensor in sensors[mid:]:
        if abs(sensor.x - leftSensor.x) > abs(sensor.x - rightSensor.x):
            break
        count += 1

    return count
# This function finds the minimum number of sensors needed to cover a given set of sensors horizontally.
def minSensors(sensors):
    n = len(sensors)
    for i in range(0,n-1) :
        mint = i
        for j in range(i+1,n) :
            if sensors[j].x < sensors[mint].x :
                mint = j
            temp = sensors[mint]
            sensors[mint] = sensors[i]
            sensors[i] = temp
    return minSensorsUtil(sensors)

# Test Codes
sensors = [Point(1, 2), Point(3, 4), Point(5, 6), Point(7, 8), Point(9, 10)]
result = minSensors(sensors)
print("Minimum number of sensors needed:", result)