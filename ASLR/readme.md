

Q: How randomized is the stack addr?

For the stack addr, it seems that 3 digits in the middle (bfXXX000) will be randomized. Also, it seems that the 3rd most
significant digit is at least 7. So if we assume that each randomized digit can have 16 values, then in total there will
be 16^3 = 4096. Not a very large number...

Q: What about heap addr?

TODO: Do a malloc in dummy.c and see where it is located.


