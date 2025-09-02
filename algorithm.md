# Algorithm to evaluate the poker hand
> A Basic Evaluation Algorithm
The evaluative procedure under consideration is constructed to accommodate the analysis of poker hands comprising cardinalities ranging from 5 to 9 elements. For the purposes of exposition and without loss of generality, we shall focus our attention on the canonical case of the 7-card stud variant. This particular instantiation is not only emblematic of the broader class of such combinatorial games, but also represents the modal scenario encountered in practical applications, thereby justifying its selection as the paradigmatic example for our subsequent mathematical discourse.


Following the logic stated in: [Algorithm by HenryRlee](https://github.com/HenryRLee/PokerHandEvaluator/blob/develop/Documentation/Algorithm.md)
We know that a deck has 52 different cards, and a 7-card poker hand consists of 7 different cards from a deck. We can easily represent a 7-card poker hand with a 52-bit binary uniquely, with exactly 7 bits set to 1 (representing this card is being selected )and 45 bits set to 0.

For example, if a hand has
```
5 of Spades,
4 of Clubs,
7 of Spades,
Jack of Diamonds,
Ace of Clubs,
10 of Spades,
and 5 of Hearts,
```
we can have such a 52-bit binary as a represenation:

```
 |   Spades   |   Hearts   |  Diamonds  |   Clubs   |
 23456789TJQKA23456789TJQKA23456789TJQKA23456789TJQKA
 0001010010000000100000000000000000010000010000000001
```
There are exactly 52 choose 7, or 133,784,560, possible unique 7-card hand representations. If we can assign each of these 52-bit binaries (with exactly 7 bits set) a unique integer in the range [1, 133,784,560], we could use this as an index into a hash table of that size, ensuring every hand maps to a distinct entry. This requires constructing a perfect hash function for 52-bit numbers with exactly 7 bits set.

Imagine lining up all 133,784,560 possible 7-card hands, each represented as a unique 52-bit binary, in strict alphabetical (lexicographical) order—like arranging books on a shelf from A to Z. If we have a function that, given any such binary, tells us exactly where it sits on this shelf (its position in the lineup), that function acts as a perfect hash: it assigns each hand a unique, orderly number, just as a librarian assigns each book a precise spot on the shelf.

Let's formalize this to a more general problem, and name it hashbinarysum7.
```
Problem: HashNBinaryKSum7

Input: integer n, integer k, an n-bit binary with exactly k bits set to 1


Expected Output: the position of the binary in the lexicographical ordering of all n-bit
binaries with exactly k bits of ones
Consider an example with n = 4 and k = 2, the binary 0011 should return 1, and 1010 should return 5.

With the following order, we can say which one is of higher ranking. 
0011 0101 0110 1001 1010 1100
```
The problem can be solved in recursions. In order to get the position in the ordering, we can instead count how many numbers are ahead of that position.

So, for “1010,” you count all the valid codes that start with “0” (which is 3), then continue recursively for the remaining digits, each time narrowing down the problem until you reach the end. This is the essence of the recursive approach described above, now seen as a journey through a hallway of lockers, each step narrowing your choices and tallying up the possibilities you’ve left behind.

Let’s use a metaphor to make this process clearer. Imagine you’re standing in front of a long line of lockers, each with a unique 4-digit binary code as its number. You want to find out how many lockers come before locker “1010” in the special lineup where only lockers with exactly two “1”s in their code are allowed.

To do this, you look at each digit from left to right, deciding at each step how many possible lockers could have come before, based on your choices so far.

- First, you look at the leftmost digit. If it’s a “1” (as in “1010”), you ask: “How many lockers could there be if I put a ‘0’ here and then fill the remaining 3 spots with exactly 2 ones?” That’s like asking, “How many ways can I arrange 2 ones in 3 places?” The answer is “3 choose 2,” or 3.
- Next, you move to the second digit. Since the first was a “1,” you now have one fewer “1” left to place (so k decreases by 1). The second digit is “0,” so you don’t add anything to your count—just move on.
- At the third digit, it’s another “1.” Again, you ask: “If I put a ‘0’ here, how many ways can I fill the last spot with the remaining one ‘1’?” But since the digit is “1,” you continue, reducing k by 1 again.
- Finally, you reach the last digit. If you’ve placed all your “1”s, you’re done.

This process is like walking down the row of lockers, at each step counting how many possible valid lockers you could have passed if you’d made a different choice at that digit. Each time you see a “1,” you consider the alternate path where you’d have put a “0” and filled the rest with the remaining ones, adding up all those possibilities. In the end, the total count tells you exactly how many lockers (or binary numbers) come before “1010” in the special lineup.


We can optimize the recursion to a loop, and the sample C code is shown below.
```
Expected input:
  q: an array of length 'len', representing an n-bit binary number (each q[i] is 0 or 1)
     The array should contain exactly 'k' elements set to 1, and (len - k) elements set to 0.
  len: the number of bits (n)
  k: the number of bits set to 1 in q (k)

Example usage:
  For n = 4, k = 2, and q = {1,0,1,0} (which is binary "1010"),
  the function computes the lexicographical position of "1010" among all 4-bit numbers with exactly 2 ones.

  The function expects that 'choose' is a precomputed 2D array such that choose[n][k] = n choose k.

  The function returns the position (starting from 1) of the input binary in the ordered list of all n-bit binaries with k ones.
```
```cpp
int hash_binary(const unsigned char q[], int len, int k)
{
  // q: array of 0s and 1s, length 'len', with exactly 'k' ones
  // len: number of bits (n)
  // k: number of ones in q
 
  int sum = 0;
  for (int i = 0; i < len; i++)
  {
    if (q[i])
    {
      // If we put a '0' here, how many ways can we arrange the remaining k ones in the rest?
      if (len - i - 1 >= k)
        sum += choose[len - i - 1][k];
      k--;
      if (k == 0)
        break;
    }
  }
  return ++sum;
}
```

Here is a tree diagram to visualize how the function computes the position of "1010" (with n=4, k=2):

Each level represents a digit (bit) position in the binary number. At each node, you choose either `'0' or '1'`, and keep track of how many '1's you have left to place (k). Only paths with exactly 2 ones are valid.

```
Tree Diagram for n=4, k=2 (4-bit binary with exactly 2 ones):

Level 0:                    start
                          /        \
Level 1:                  0         1
                        /   \      /   \
Level 2:                0     1    0     1
                      /   \  / \  /   \  / \
Level 3:              1   0 1  0 1   0 0   1
                    /   \/   \/   \/   \/   \
Level 4:            1   0 1  0 1  0 0  1 0  0

Valid paths (exactly 2 ones):
0011 (pos 1) - path: 0→0→1→1
0101 (pos 2) - path: 0→1→0→1  
0110 (pos 3) - path: 0→1→1→0
1001 (pos 4) - path: 1→0→0→1
1010 (pos 5) - path: 1→0→1→0  ← our target
1100 (pos 6) - path: 1→1→0→0


Step-by-step breakdown:
1. First bit = 1
   - If we put 0 here, we need 2 ones in remaining 3 positions
   - Count: C(3,2) = 3 combinations (0011, 0101, 0110)
   - These are positions 1, 2, 3
   - k decreases to 1 (we used one '1')

2. Second bit = 0  
   - No additional count since we didn't choose 1
   - k remains 1

3. Third bit = 1
   - If we put 0 here, we need 1 one in remaining 1 position
   - Count: C(1,1) = 1 combination (1001)
   - This is position 4
   - k decreases to 0 (we used our last '1')

4. Fourth bit = 0
   - No additional count since k = 0

Total count = 3 + 1 = 4
Therefore "1010" is at position 5 (since we count from 1)

Recursive logic:
- At each '1' bit: count combinations if we had chosen '0' instead
- Use C(remaining_positions, remaining_ones) for counting
- Decrease k by 1 after each '1' bit
- Stop when k reaches 0
```




The final increment (the ++sum at the end of the function) is only needed if we want the positions to start from 1. However, for most programming applications—especially when using the result as a hash table index—it is more natural and efficient to have positions start from 0. This is because arrays and hash tables in most languages are zero-indexed. By omitting the increment, the function directly returns a zero-based position, which matches the way data structures are typically accessed in code and avoids an unnecessary adjustment step.

We can precompute all possible n choose k and store the results. For a problem with a n-bit binary, the function runs in at most n cycles.

If we apply this function to a poker hand, it'll take 52 cycles to compute the hash value. Meanwhile we need a hash table of size 133784560 entries in the 7-card poker hand case. Both the time and memory performance are not what we expected.

