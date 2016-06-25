# HW3-2 Version 1
#
# Define a procedure primitive_roots 
# that takes as input a small prime number
# and returns all the primitive roots of that number
#

from fractions import gcd

def primitive_roots(n):
    """Returns all the primitive_roots of 'n'"""
    roots = []

    # Some properties:
    # - The primitive root g lies in [2, n)
    # - g ^ k = a mode n
    # -- a can be [1, n-1] (Q: Why not 0?)
    # -- k can be [1, n-1]
    # -- Then we know that if g is a primitive root, k1 and k2 shall not give the same result.
    
    for root in range(2, n):
        
        nums = set()
        
        for k in range(1, n):
            a = pow(root, k) % n
            if a in nums:
                break
            else:
                nums.add(a)
        if len(nums) == n-1:
            roots.append(root)
    
    return roots


def test():
    assert primitive_roots(3) == [2]
    assert primitive_roots(5) == [2, 3]
    print "tests pass"

test()