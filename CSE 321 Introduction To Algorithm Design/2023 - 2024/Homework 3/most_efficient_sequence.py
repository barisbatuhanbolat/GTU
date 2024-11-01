# Function iterates over each part in the current list of parts and recursively explores the remaining parts to find the most efficient sequence.
# The cost of the current sequence is calculated by adding the cost of the current part to the cost of the previously determined sequence.
# And compares the current cost with the result cost and updates the result sequence and cost if the current sequence is more efficient.
def most_efficient_sequence(parts,cost,index):
    if len(parts) == 0:
        return []
    res_sequence = 0
    res_cost = 999999
    for part in parts:
        parts.remove(part)
        temp_sequence = most_efficient_sequence(parts,cost,part)
        temp_sequence.add(part)
        temp_cost = temp_cost + cost[index]
        if temp_cost < res_cost:
            res_sequence = temp_sequence
            res_cost = temp_cost

        parts.add(part)

    return res_sequence
