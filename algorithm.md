# Algorithm to evaluate the poker hand


The standard ranking of poker hands, from highest to lowest, is as follows:

1. **Royal Flush**  
   - A, K, Q, J, 10, all of the same suit.

2. **Straight Flush**  
   - Five cards in sequence, all of the same suit (e.g., 9-8-7-6-5 of hearts).

3. **Four of a Kind**  
   - Four cards of the same rank (e.g., 7-7-7-7-K).

4. **Full House**  
   - Three cards of one rank and two cards of another rank (e.g., 8-8-8-4-4).

5. **Flush**  
   - Five cards of the same suit, not in sequence (e.g., A-10-7-6-2 of clubs).

6. **Straight**  
   - Five cards in sequence, not all of the same suit (e.g., 5-4-3-2-A).

7. **Three of a Kind**  
   - Three cards of the same rank (e.g., Q-Q-Q-9-2).

8. **Two Pair**  
   - Two cards of one rank, two cards of another rank (e.g., J-J-4-4-9).

9. **One Pair**  
   - Two cards of the same rank (e.g., 10-10-8-6-3).

10. **High Card**  
    - None of the above; the highest card plays (e.g., A-Q-9-6-3 of mixed suits).

These rankings are used to determine the winner in most standard poker games, including Texas Hold'em and Omaha.


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

> The above solution is simple, and is a brute force approach to compute the combinatorics table for all possibilities. Yet when it comes to large number, e.g C(100,5), the entire function fails and return segmentation fault.

#### Evaluatete the flush 
One of the main challenges in designing a poker hand evaluator is handling the Flush category, which includes both Flushes and Straight Flushes. The complexity arises because, for these hands, the suit of each card becomes important, whereas for most other hand types (like pairs, full houses, etc.), only the rank matters.

If we temporarily ignore the possibility of a Flush, we can greatly simplify the representation of a poker hand. Instead of tracking all 52 cards individually (which would require a 52-bit binary number, one bit per card), we can represent the hand as a 13-digit number in base 5 (a "quinary" number). Here’s why: for each of the 13 ranks (Ace through King), a player can have anywhere from 0 to 4 cards (since there are four suits). So, for each rank, there are 5 possible counts (0, 1, 2, 3, or 4). By using a base-5 digit for each rank, we can compactly encode the entire hand’s rank distribution, ignoring suits.

This quinary representation is extremely useful for evaluating most hand types efficiently, because it allows us to quickly determine combinations like pairs, three-of-a-kinds, and full houses by simply examining the counts for each rank. However, this approach does not distinguish between suits, so it cannot be used to detect Flushes or Straight Flushes. That’s why handling Flushes requires a separate approach, and is a key source of complexity in poker hand evaluation algorithms.

So we can split the problem into two branches, the hands with a flush and the hands without a flush. The first one can be represented by a 13-bit binary, and the latter one can be represented by a 13-bit quinary (count for one rank).

In 7-card poker, if there are at least five cards in the same suit, this hand is guaranteed to be either Flush or Straight Flush.

Because if we have at least 5 cards in the same suit, these cards must have different ranks, and then combining 2 more cards from the other suit cannot form a Four of a Kind or a Full House. We also know that, there cannot be two flushes in different suits in a 7-card hand.
POKE RRAN

Therefore, we can first evaluate whether the hand is a flush or not. Once we find a flush in a 7-card hand, we can stop evaluating the rest of the cards. However, if the hand has more than 7 cards, we need to keep evaluating the other branch.

It's not hard to determine whether a hand has a flush or not, we only need a counter for each suit. In the meantime, we need to maintain a binary for each suit, so that when we see a flush, we can pass the corresponding binary to the function that evaluates flush hands.

For example, given the input:
```
Suppose we have the following 7-card hand:

 2 of Hearts,
 3 of Hearts,
 6 of Hearts,
 9 of Hearts,
 King of Hearts,
 5 of Diamonds,
 7 of Clubs,

our 4 counters and binaries are:
 Hearts:     counter 4, binary 1001001001100
 Diamonds:   counter 1, binary 0000100000000
 Clubs:      counter 1, binary 0000001000000
 Spades:     counter 0, binary 0000000000000

In this example, the Hearts suit has 4 cards, so there is no flush. 

Now, let's look at another example where a flush is present:

 3 of Clubs,
 5 of Clubs,
 8 of Clubs,
 10 of Clubs,
 Queen of Clubs,
 2 of Diamonds,
 7 of Hearts,

our 4 counters and binaries are:
 Clubs:      counter 5, binary 0100100101000
 Diamonds:   counter 1, binary 0000000000001
 Hearts:     counter 1, binary 0000001000000
 Spades:     counter 0, binary 0000000000000
```

Here, as soon as we see the Clubs counter reach 5, we know there is a flush, and the binary 0100100101000 (for Clubs) can be passed to the flush evaluation function.

Once any suit’s counter reaches 5 or more, we know a flush is present in that suit. At this point, we can take the corresponding 13-bit binary (for example, 0000101101100 for Spades) and pass it directly to the flush evaluation function. There is no need to consider the other suits, since it is impossible for another flush to exist in the same 7-card hand.

To evaluate the flush, we could use the `HashNBinaryKSum7` function with precomputed hash tables for k = 5, 6, and 7. However, since there are only 2^13 = 8192 possible 13-bit combinations, it is more efficient to use a direct lookup table of size 8192. This approach eliminates the need to compute the perfect hash at runtime, making the evaluation much faster.

If the hand has 7 or fewer cards, we can immediately return the flush evaluation result. If there are more than 7 cards, we must also evaluate the non-flush branch and compare the outcomes to determine the best hand.

#### Hash For a Restricted Quinary
Consider the scenario in which the suits of the cards are rendered irrelevant—such as after flush detection—leaving only the distribution of card ranks to distinguish hand strength. In this context, a 7-card poker hand can be succinctly encoded as a 13-digit quinary numeral (i.e., each digit in base 5), where each digit represents the count of cards of a particular rank (from deuce through ace). The essential constraint imposed on this representation is that the sum of all digits must be exactly 7, corresponding to the total number of cards in the hand. i.e. The number of cards for each suit is not binary but can be of any numebr in range [0,6).

To construct this quinary encoding, one maintains an array of 13 counters, each initialized to zero and corresponding to a distinct rank. As each card is processed, the counter associated with its rank is incremented. For instance, a hand containing 2 Aces, 3 Fives, 1 Seven, and 1 Jack would be represented by the quinary sequence 2001000103000, where the position of each digit reflects the rank (with a conventional ordering such as deuce through ace).

To construct a perfect hash function for this quinary representation, we can use an approach analogous to the binary case. By arranging all possible quinary sequences (where the sum of the digits equals 7) in lexicographical order, the index or position of a given quinary within this ordering serves as its unique hash value.

```
 Problem: HashN4KSum

 Input: integer n, integer k, an (n+1)-bit quinary with the sum of all bits
  equal to k

 Output: the position of the quinary in the lexicographical ordering of all
  (n+1)-bit quinaries with sum of all bits equal to k
```

Just as with the binary hash, to determine the position of a given quinary, we count all valid quinary numbers that are lexicographically less than it. Take, for example, the 4-digit quinary 4300.

To determine the position of a given quinary (such as 4300), we need to count how many valid quinaries come before it in lexicographical order. This is done by counting all valid quinaries in the range [0000, 4300). However, since positions are typically counted starting from 1 (not 0), we must add 1 to this count to obtain the actual position of 4300 itself. In other words, the position of 4300 is equal to the number of quinaries less than 4300, plus one for 4300 itself.

To break down the counting, we split [0000, 4300) into two parts: [0000, 4000) and [4000, 4300). The first part counts all quinaries where the first digit is less than 4, and the second part counts those where the first digit is exactly 4 and the remaining digits are less than 300. The second part is equivalent to counting quinaries in [000, 300) with one fewer digit (n-1) and a reduced sum (k-4), making it a smaller subproblem.

However, unlike the binary case, calculating the size of [0000, 4000) directly is more complex. To handle this, we further divide it into [0000, 1000), [1000, 2000), [2000, 3000), and [3000, 4000). Each of these subranges corresponds to fixing the first digit and recursively solving for the remaining digits with an appropriately reduced k. For instance, [1000, 2000) corresponds to [000, 1000) with k-1, [2000, 3000) to [000, 1000) with k-2, and so forth.

Now the remaining problem is solving the range [0000, 1000) with parameter k. This range can be splitted into [000, 400) and [400, 1000), and eventually it can be partitioned into 5 small ranges. The result of the problem is the sum of the result of the 5 subproblems with range of exactly a power of 5.

We can use dynamic programming to solve all these subproblems, and store the result in an array. Let's use a 3-d array dp[l][n][k] of size 5*14*8, where n is the number of trailing zero bits, k is the remaining number of k, and l is the most significant bit of the excluding endpoint. For example, the result of [0000, 1000) is stored in dp[1][3][k], as the excluding endpoint is 1000, resulting l to be 1 and n to be 3. Another example is [000, 200), whose result is stored in dp[2][2][k].

Below is a conceptual diagram of the dynamic programming array `dp[l][n][k]` used in the quinary hash algorithm. This 3D array is indexed by:

- `l`: the most significant digit of the excluding endpoint (range: 1 to 4)
- `n`: the number of remaining digits (range: 1 to 13)
- `k`: the remaining sum to distribute (range: 0 to 7)

### **3D ARRAY VISUALIZATION: dp[l][n][k]**
Total size: 4 × 13 × 8 = 416 entries

This 3D array `dp[l][n][k]` is used to quickly calculate the number of ways to distribute `k` points among `n` positions.

**n is the bucket (container):**
- `n` represents the **number of positions/containers** available to distribute points
- Think of `n` as the number of "slots" or "buckets" you have
- For example, if `n = 3`, you have 3 positions: [position 0, position 1, position 2]

**k is the content (what goes into the buckets):**
- `k` represents the **total number of points** you need to distribute across those n positions
- Think of `k` as the "stuff" you're putting into the buckets
- For example, if `k = 5`, you have 5 points to distribute

**Visual Example:**
```
n = 3 (3 buckets/positions): [ ][ ][ ]
k = 5 (5 points to distribute)

Possible distributions:
[2][2][1]  ← 2+2+1 = 5 points in 3 buckets
[3][1][1]  ← 3+1+1 = 5 points in 3 buckets  
[4][1][0]  ← 4+1+0 = 5 points in 3 buckets
[5][0][0]  ← 5+0+0 = 5 points in 3 buckets
```
The number of ways to distribute $k$ indistinguishable points into $n$ distinguishable buckets (with no upper limit per bucket) is given by the stars-and-bars formula:

$C(k + n - 1, k) = C(k + n - 1, n - 1)$

However, in our case, each bucket can hold at most 4 points (since we are working in base-5), so the actual count is less and must be computed recursively or with dynamic programming as described above.

**In the context of poker:**
- `n = 13` (13 ranks: 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A)
- `k = 7` (7 cards in the hand)
- We're distributing 7 cards across 13 possible ranks

**How to fill this array step by step:**

**Step 1: Set the base cases**
- When l=1, we are dealing with the range [0000, 1000)
- `dp[1][1][k] = 1` if k ≤ 4, otherwise = 0
- This is because each position can hold at most 4 points
- And as the largest count is 1, then it takes up 4 * 4 matrix space

**Step 2: Fill the first layer (l=1)**
- Use the recurrence: `dp[1][n][k] = Σ(dp[1][n-1][k-i])` where i goes from 0 to min(4, k)

  - **Why min(4, k)?**  
    Each "bucket" (position) can hold at most 4 points (since we're working in base-5, representing up to 4 cards of a rank in poker).  
    - If k < 4, you can't put more than k points in a bucket (since you don't have enough points).
    - If k ≥ 4, you can't put more than 4 points in a bucket (since that's the maximum allowed).
    - So, for each position, the number of points you can assign ranges from 0 up to the smaller of 4 or k, hence `i = 0 ... min(4, k)`.
- This formula counts all possible ways to distribute k points among n positions

**Step 3: Build the other layers (l > 1)**
- Use the formula: `dp[l][n][k] = dp[l-1][n][k] + dp[1][n][k-l+1]`
- This breaks down complex ranges into simpler subproblems

**Example:**
Suppose we want to find `dp[2][3][5]`, which is the number of ways to distribute 5 points in the range [000, 200):

1. First, split into two parts:
   - [000, 100): distribute 5 points = `dp[1][3][5]`
   - [100, 200): distribute 5-1=4 points = `dp[1][3][4]`

2. Calculate the results:
   - `dp[1][3][5] = 0` (invalid: 3 positions can hold at most 12 points, not 15)
   - `dp[1][3][4] = 15` (valid combinations: 004, 013, 022, 031, 040, 103, 112, 121, 130, 202, 211, 220, 301, 310, 400)

3. Final result: `dp[2][3][5] = 0 + 15 = 15`

**Why are the values for the first row (n=1) like this:**

When n=1, there is only one position to fill. This is the base case, and we need to consider what each k value means:

**Analysis for n=1:**
- **k=0**: Place 0 points → only one way: `[0]` → `dp[1][1][0] = 1`
- **k=1**: Place 1 point → only one way: `[1]` → `dp[1][1][1] = 1`
- **k=2**: Place 2 points → only one way: `[2]` → `dp[1][1][2] = 1`
- **k=3**: Place 3 points → only one way: `[3]` → `dp[1][1][3] = 1`
- **k=4**: Place 4 points → only one way: `[4]` → `dp[1][1][4] = 1`
- **k=5**: Place 5 points → **impossible!** Each position can hold at most 4 points → `dp[1][1][5] = 0`
- **k=6**: Place 6 points → **impossible!** → `dp[1][1][6] = 0`
- **k=7**: Place 7 points → **impossible!** → `dp[1][1][7] = 0`

**Why is this the case:**
1. **Physical limit**: Each position can hold at most 4 points (since it's base-5: 0,1,2,3,4)
2. **Uniqueness**: With only one position, each valid k value has only one arrangement
3. **Boundary condition**: These base cases are the starting point for the recurrence; all more complex cases are built from these

**Recurrence base:**

VISUAL REPRESENTATION:

Layer l=1 (for ranges like [0000, 1000)):
n\k  0  1  2  3  4  5  6  7 
1    1  1  1  1  1  0  0  0  ← Base case: only valid for k ≤ 4 
2    1  2  3  4  5  0  0  0
3    1  3  6  10 15 0  0  0
4    1  4  10 20 35 0  0  0
5    1  5  15 35 70 0  0  0
...  ... ... ... ... ... ... ... ...
13   1  13 91 455 1820 0 0 0

Layer l=2 (for ranges like [0000, 2000)):
n\k  0  1  2  3  4  5  6  7
1    1  1  1  1  1  0  0  0
2    1  2  3  4  5  0  0  0
3    1  3  6  10 15 0  0  0
4    1  4  10 20 35 0  0  0
5    1  5  15 35 70 0  0  0
...  ... ... ... ... ... ... ... ...
13   1  13 91 455 1820 0 0 0

Layer l=3 (for ranges like [0000, 3000)):
n\k  0  1  2  3  4  5  6  7
1    1  1  1  1  1  0  0  0
2    1  2  3  4  5  0  0  0
3    1  3  6  10 15 0  0  0
4    1  4  10 20 35 0  0  0
5    1  5  15 35 70 0  0  0
...  ... ... ... ... ... ... ... ...
13   1  13 91 455 1820 0 0 0

Layer l=4 (for ranges like [0000, 4000)):
n\k  0  1  2  3  4  5  6  7
1    1  1  1  1  1  0  0  0
2    1  2  3  4  5  0  0  0
3    1  3  6  10 15 0  0  0
4    1  4  10 20 35 0  0  0
5    1  5  15 35 70 0  0  0
...  ... ... ... ... ... ... ... ...
13   1  13 91 455 1820 0 0 0


The base cases for the array dp:
```cpp
  if 0 <= i <= 4:
    dp[1][1][i] = 1;
  if i > 4:
    dp[1][1][i] = 0;
```
Consider the range [00, 10) (which means all 2-digit quinary numbers starting at 00 up to but not including 10). If we want the sum of the digits (k) to be 4, there is only one possible quinary number in this range that satisfies this: 04 (since 0+4=4). If we try to find a quinary number in this range with k=5 or any value greater than 4, it is impossible, because the maximum sum you can get with two digits where each digit is at most 4 is 0+4=4. So, for k>4, there are no valid quinary numbers in this range.

Then we iterate the edges:
```cpp
  for each i in [2, 13]:
    dp[1][i][1] = i;
    dp[1][i][0] = 1;
```
Let's look at a concrete example to clarify how the dp array works. Consider a 4-digit quinary number (each digit can be 0, 1, 2, 3, or 4), and suppose we want the sum of the digits to be k=1. In this case, dp[1][3][1] represents the number of 4-digit quinary numbers where the sum of the digits is exactly 1.

- In the expression dp[1][3][1], the second index (3) indicates the number of digits being considered. Here, dp[1][3][1] represents the number of ways to distribute a sum of 1 across 3 digits (with each digit allowed to be between 0 and 4, since it's quinary). So, "3" in dp[1][3][1] tells us we are working with 3 digits. For example, the valid 3-digit quinary numbers with digit sum 1(the last digit) are 001, 010, and 100.

To construct such numbers, we need to distribute a total sum of 1 across 4 digits, with each digit allowed to be between 0 and 4. The only way to do this is to set one of the digits to 1 and the rest to 0. This gives us the following possibilities:
- 0001
- 0010
- 0100
- 1000

However, since the dp array is 0-indexed for the digit positions, dp[1][3][1] actually counts the number of ways to distribute a sum of 1 across 3 remaining digits (after fixing the first digit). In this context, the three valid quinary numbers are 001, 010, and 100 (where the sum of the digits is 1). So, dp[1][3][1] = 4- 1 = 3.

If k=0, the only way to achieve a sum of 0 is to set all digits to 0, resulting in a single valid quinary number: 000. Therefore, dp[1][3][0] = 1.

This illustrates how the dp array counts the number of valid quinary numbers for a given number of digits and a target sum k. And thus we can conclude that k = min(4, any numebr).
Now we can iterate all dp[1][i][j]. We do this by iterating the next digit from 0 to 4 and evaluating the shorter expression for smaller k. :
```cpp
  for (int i = 2; i <= 13; ++i) {
    for (int j = 0; j <= 7; ++j) {
      dp[1][i][j] = 0;
      for (int next_digit = 0; next_digit <= 4; ++next_digit) {
        if (j - next_digit >= 0)
          dp[1][i][j] += dp[1][i-1][j-next_digit];
      } 
    }
  }
```
For example, to evaluate dp[1][2][7] (which counts the number of 2-digit quinary numbers in the range [00, 10) whose digits sum to 7), we consider all possible values for the second digit (from 0 to 4). For each possible value, the first digit is determined as 7 minus that value. This gives the combinations 07, 16, 25, 34, and 43. However, most of these are invalid because at least one digit exceeds the maximum allowed value of 4 in base-5. Specifically, 07, 16, and 25 are invalid because the first digit would be greater than 4. In the dynamic programming table, this is handled because dp[1][1][k] = 0 for k > 4, so these cases contribute nothing to the sum.

Now the iteration for the rest of the entries:

  for each l in [2, 4] and i in [1, 13] and j in [0, 7]:
    dp[l][i][j] = dp[l-1][i][j] + dp[1][i][j-l+1]
For example dp[4][4][5], which is equivalent to the number of valid quinaries in the range [00000, 40000) with k=5. It can be splitted into [00000, 30000) with k=5, and [30000, 40000). The former one is dp[3][4][5], the latter one is equivalent to [00000, 10000) with k=k-3, which is dp[1][4][2].

Finally we can compute the hash of the quinary base on the dp arrays. The example C code is shown below.


```cpp
int hash_quinary(unsigned char q[], int len, int k)
{
  int sum = 0;
  int i;

  for (i=0; i<len; i++) {
    sum += dp[q[i]][len-i-1][k];

    k -= q[i];

    if (k <= 0)
      break;
  }

  return ++sum;
}
```
In practice, the final increment can be ignored.

The final lookup hash table will contain 49205 entries, and the hash function takes at most 13 cycles to compute. This algorithm is much better than any others that do 7-card poker evaluation by checking all 21 combinations.