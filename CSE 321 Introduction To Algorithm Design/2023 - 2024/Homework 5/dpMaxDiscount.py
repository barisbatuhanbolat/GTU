# Class for representing Store for just discount
class Store :
    def __init__(self,disc) :
        self.discount = disc
# I created this 'calc' function to test this program.
# It should has O(1) time complexity but now it has O(n) time complexity for this programs test.
def calc(stores) :
    total = 0
    for store in stores:
        total += store.discount
    return total

# This function finds the combination of stores that maximizes the total discount and return the result.
def dpMaxDiscount(stores) :
    dp = []
    for store in stores :
        temp = dp
        temp.append(store)
        if calc(temp) > calc(dp) :
            dp = temp
    return dp , calc(dp)

# Test codes
stores = [Store(10),Store(20),Store(15),Store(50),Store(5)]

sets , total = dpMaxDiscount(stores)
print(f"Total discount: {total}")
print("Stores:")
for store in sets:
    print(f"Store with discount: {store.discount}")

