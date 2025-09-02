// this file is used to find a general functiont that can obtain the an almost perfect hash function for the HashNBinaryKSum problem
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono; // especially for the time complexity analysis

// This function computes the lexicographical position (rank) of a given n-bit binary number q[]
// with exactly k ones, among all n-bit binaries with exactly k ones.
// It does this by counting how many valid binaries come before q[] in the ordering.
// For each '1' in q[], it adds the number of ways to place the remaining ones in the remaining positions
// if a '0' had been placed at that position instead.
// The function returns the position (starting from 1) of q[] in the ordered list.

vector<vector<int>> initialize_choose(int n, int k)
{
    vector<vector<int>> choose(n + 1, vector<int>(k + 1, 0));
    for (int i = 0; i <= n; i++)
    {
        choose[i][0] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            choose[i][j] = choose[i - 1][j - 1] + choose[i - 1][j];
        }
    }

    return choose;
}
/*

EXAMPLE: q = [1,0,1,0], k = 2, n = 4
Target: Find position of "1010" among all 4-bit numbers with exactly 2 ones

Step-by-step:
1. i=0, q[0]=1: If we put 0 here, we need 2 ones in remaining 3 positions
   - Remaining positions: 3 (positions 1,2,3)
   - Need to place: 2 ones
   - Count: choose[3][2] = 3 combinations (0011, 0101, 0110)
   - Add to sum: sum = 3
   - Decrease k: k = 1

2. i=1, q[1]=0: No action (bit is 0)

3. i=2, q[2]=1: If we put 0 here, we need 1 one in remaining 1 position
   - Remaining positions: 1 (position 3)
   - Need to place: 1 one
   - Count: choose[1][1] = 1 combination (1001)
   - Add to sum: sum = 3 + 1 = 4
   - Decrease k: k = 0, break loop

4. Final result: return sum + 1 = 5
   So "1010" is at position 5 in the ordering

The function returns position 5, which matches our expected ordering:
0011 (pos 1), 0101 (pos 2), 0110 (pos 3), 1001 (pos 4), 1010 (pos 5), 1100 (pos 6)
*/
int hash_binary(const vector<int> q, int k, vector<vector<int>> choose)
{
    // q: array of 0s and 1s, length 'len', with exactly 'k' ones
    // len: number of bits (n)
    // k: number of ones in q
    // it should be from q we select k bits to be 1, and the rest to be 0

    int len = q.size();
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        if (q[i]) // if the bit is 1;
        {
            // If we put a '0' here, how many ways can we arrange the remaining k ones in the rest?
            if (len - i - 1 >= k)
                // 'choose' here is a 2D array (vector of vectors) where choose[n][k] gives "n choose k" (the binomial coefficient).
                // It should be precomputed so that choose[a][b] == C(a, b) == a! / (b! * (a-b)!)
                sum += choose[len - i - 1][k];
            //-1 because we are using 0-based index

            k--;
            if (k == 0)
                break;
        }
    }
    return ++sum;
}
void print_binary(const vector<int> q)
{
    for (int i = 0; i < q.size(); i++)
    {
        if (i == q.size() - 1)
            cout << q[i];
        else
        cout << q[i] << " ";
    }
    return; 
}


int main()
{
    vector<int> q = {1, 0, 1, 0};
    int k = 2;
    vector<vector<int>> choose = initialize_choose(q.size(), k); // this is to initialize the precomputed choose array
    cout << "The number of ways to choose " << k << " bits from " << q.size() << " bits is " << choose[q.size()][k] << endl;
    cout << "The hash value of the binary [" ;
    print_binary(q);
    cout << "] is " << hash_binary(q, k, choose) << endl;
    return 0;
}