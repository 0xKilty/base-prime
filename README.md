# Base Prime Equivalence

### Unofficially Sponsored by Red Bull
![](https://upload.wikimedia.org/wikipedia/en/f/f5/RedBullEnergyDrink.svg)

### Runtime language difference
With the inputs being 5 digits and the largest base being 10,000 averaged over 10 tests.
- **main.c**: 0.177s
- **main.py**: 5m14.028s

There are some memory management tricks that speed up the C program that are not possible to do in Python.

### Implementation
This implementation defines a `base loop-p`.

For example a `base loop-2` in base 10:

$` 0 = 2^0 = 1 `$

$` 2^1 = 2^0 \cdot 2 `$

$` 2^2 = 2^1 \cdot 2 `$

$` 2^3 = 2^2 \cdot 2 `$

$` 2^4 = 2^3 \cdot 2 `$

$` 2^5 = 2^4 \cdot 2 `$

$` 2^6 = 2^5 \cdot 2 `$

$` 2^7 = 2^6 \cdot 2 `$

$` 2^8 = 2^7 \cdot 2 `$

$` 2^9 = 2^8 \cdot 2 `$

Then, the current base prime (10 in this case) would then be assigned.

$` 3^1 = 3 `$

Then the base loop would continue with 2.

$` 3^1 \cdot 2^1 = 3^1 \cdot 2 `$

$` 3^1 \cdot 2^2 = 3^1 \cdot 2^1 \cdot 2 `$

You can start to see a tree structure where each node in the tree has a "base" number of children (except or the leaf nodes).

The implementation relies on the iteration of a base prime as each number relies on the previous computation.

[Or does it?](https://www.youtube.com/watch?v=AsxsQkKnmBI)

We can actually break out of a base loop if the base prime becomes greater than the number that we are checking for equality. This kind of "jumps up" a node in the iteration tree. 

But then the iterator will be messed up because the previous values won't be computed. So we have to compute the next iterator which is what the iterator would have been if it had completed its full base loop. This keeps the iterator and the base prime aligned.
