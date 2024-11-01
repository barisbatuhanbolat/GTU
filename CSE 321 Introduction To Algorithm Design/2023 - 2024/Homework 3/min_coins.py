# Funtion traverses all possible combinations of coin denominations for each level of recursion.
# Time complexity of this function is O(n*m). n is target value , m is number of coin denominations.
def min_coins(coins, target, index):
  if target == 0:
    return 0
  if index >= len(coins):
    return 999999
  result = 999999
  for i in range(0, target / coins[index] + 1):
    temp_target = target - i * coins[index]
    min_result = min_coins(coins, temp_target, index + 1)
    result = min(result, min_result)
  return result
