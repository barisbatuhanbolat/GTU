# The function recursively calculates the maximum discount for the included set and excluded set by considering the current store and moving to the next store.
# The discounts for the included and excluded sets are compared, and the set with the higher discount is returne
def find_max_discount(stores,index):
    if index == len(stores):
        return []
    current_store = stores[index]
    current_included_set = find_max_discount(stores,index + 1)
    current_included_set.add(current_store)
    current_included_discount = calc_discount(current_included_set)

    current_excluded_set = find_max_discount(stores,index + 1)
    current_excluded_discount = calc_discount(current_excluded_set)

    if current_included_set > current_excluded_set :
        return current_included_discount
    else :
        return current_excluded_discount
    

    
    