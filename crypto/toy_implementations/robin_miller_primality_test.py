# HW3-4 Version 1
# 
# Implement the Rabin Miller test for primality
#

from random import randrange

def rabin_miller(n, target=128):
    """returns True if prob(`n` is composite) <= 2**(-`target`)"""

    # Based on the psudo code in
    # https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
    # This code is different from the udacity quiz answer
    
    if n % 2 == 0:
        return False
    else:
        d = 0
        r = 0
        t = n - 1
        while t % 2 == 0:
            t = t / 2
            r += 1
        d = t

    for i in range(target):
        a = randrange(2, n-1)
        x = pow(a, d) % n
        if x == 1 or x == n-1:
            continue
        for j in range(r-1):
            x = x * x % n
            if x == 1:
                return False
            if x == n - 1:
                break

    return True

assert rabin_miller(79) == True

