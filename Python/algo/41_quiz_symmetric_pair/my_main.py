"""
Symmetric
Input  [(1, 2), (3, 5), (4, 7), (5, 3), (7, 4)]
Output [(5, 3), (7, 4)]
"""
from typing import List, Iterator, Tuple


def find_pair(pairs: List[Tuple[int, int]]) -> Iterator[Tuple[int, int]]:
    ret_pairs = list()
    
    current_index = len(pairs) - 1
    
    while current_index > 0:
        current_0, current_1= pairs[current_index]
        
        for i in range(current_index - 1):
            check_0, check_1 = pairs[i]
            
            if current_0 == check_1 and current_1 == check_0:
                ret_pairs.append(pairs[current_index])
                break
        
        current_index -= 1
        
    return ret_pairs
        
        
if __name__ == '__main__':
    l = [(1, 2), (3, 5), (4, 7), (5, 3), (7, 4)]
    for r in find_pair(l):
        print(r)

