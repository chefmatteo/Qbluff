//this file is used to find a general functiont that can obtain the an almost perfect hash function for the HashNBinaryKSum problem
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono; //especially for the time complexity analysis

 // This function computes the lexicographical position (rank) of a given n-bit binary number q[]
  // with exactly k ones, among all n-bit binaries with exactly k ones.
  // It does this by counting how many valid binaries come before q[] in the ordering.
  // For each '1' in q[], it adds the number of ways to place the remaining ones in the remaining positions
  // if a '0' had been placed at that position instead.
  // The function returns the position (starting from 1) of q[] in the ordered list.


  vector<vector<int>> initialize_choose (int n, int k){
    //this is the function to initialize the choose array, a 2D array that 
    //store the number of ways to choose k elements from n elements
    
    vector<vector<int>> choose(n+1, vector<int>(k+1, 0));
    for (int i = 0; i <= n; i++) {
      choose[i][0] = 1;
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= k; j++) {
        choose[i][j] = choose[i-1][j-1] + choose[i-1][j];
      }
    }

    return choose;


  }
  int hash_binary(const vector<int> q, int k, vector<vector<int>> choose)
  {
    // q: array of 0s and 1s, length 'len', with exactly 'k' ones
    // len: number of bits (n)
    // k: number of ones in q
   int len = q.size();
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
      if (q[i]) //if the bit is 1; 
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

int main(){
    vector<int> q = {1,0,1,0};
    int k = 2;
    vector<vector<int>> choose = initialize_choose(q.size(), k); //this is to initialize the precomputed choose array 
    cout << choose[q.size()][k] << endl;
    //cout << hash_binary(q, k, choose) << endl;
    return 0;
}