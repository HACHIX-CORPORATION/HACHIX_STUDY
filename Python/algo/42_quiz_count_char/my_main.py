import re

def count_max_char(paragraph: str) -> tuple:
    cache = {}
    for ch in paragraph:
        if ch.isalpha() is True:
            if ch.lower() in cache:
                cache[ch.lower()] += 1
            else:
                cache[ch.lower()] = 1
    
    max_key = max(cache, key=cache.get)
    
    return (max_key, cache[max_key])
    

if __name__ == '__main__':
    s = 'This is a pen. This is an apple. Applepen.'
    print(count_max_char(s))