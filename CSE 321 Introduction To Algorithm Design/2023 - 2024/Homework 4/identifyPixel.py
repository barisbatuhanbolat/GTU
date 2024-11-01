# Custom Pixel class with brightness instance value.
class Pixel:
    def __init__(self, brightness):
        self.brightness = brightness

# The function reduces the size of the problem instance by a constant value(one pixel)
# at each step, until it finds the pixel the breaks monotonic pattern.
def identifyPixel(image):
    rows, cols = len(image), len(image[0])
    
    current_row, current_col = rows // 2, cols // 2
    
    while True:
        brightest_pixel = image[current_row][current_col]
        neighbors = [
            (current_row - 1, current_col), 
            (current_row + 1, current_col), 
            (current_row, current_col - 1),
            (current_row, current_col + 1)  
        ]

        for neighbor_row, neighbor_col in neighbors:
            if 0 <= neighbor_row and neighbor_row < rows and 0 <= neighbor_col and neighbor_col < cols:
                neighbor_pixel = image[neighbor_row][neighbor_col]
                if neighbor_pixel.brightness > brightest_pixel.brightness:
                    brightest_pixel = neighbor_pixel
                    current_row, current_col = neighbor_row, neighbor_col

        if brightest_pixel == image[current_row][current_col]:
            return brightest_pixel

# Test Example
image = [
    [Pixel(1), Pixel(3), Pixel(4), Pixel(6)],
    [Pixel(2), Pixel(4), Pixel(10), Pixel(12)],
    [Pixel(3), Pixel(5), Pixel(20), Pixel(14)],
    [Pixel(4), Pixel(6), Pixel(8), Pixel(18)]
]

brightest_pixel = identifyPixel(image)
print(f"Brightest pixel brightness: {brightest_pixel.brightness}")