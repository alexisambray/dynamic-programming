// Alexis Sofia Ambray
// CSALGCM - N01
// P4: LCS

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void printLCS(string X, string Y);

int main() {
  // input of string X and Y
  string X, Y;

  cin >> X >> Y;
  printLCS(X, Y);
}

void printLCS(string X, string Y) {
  // dp[i][j] stores the longest common subsequence length of X[0, 1....i] and
  // Y[0, 1, ....j]
  vector<vector<int> > dp(X.size() + 1, vector<int>(Y.size() + 1));

  for (int i = 1; i <= X.size(); i++) {
    for (int j = 1; j <= Y.size(); j++) {
      // if X[i - 1] == Y[j - 1], then this charater should be included in
      // longest common subsequence
      if (X[i - 1] == Y[j - 1]) {
        dp[i][j] = 1 + dp[i - 1][j - 1];
      } else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    }
  }

  // get the length of the longest common subsequence
  int LCSLength = dp[X.size()][Y.size()];

  // Create a character array to store the LCS string
  vector<char> LCS(LCSLength);

  int currIdx = LCSLength - 1;

  int i = X.size(), j = Y.size();

  while (i > 0 && j > 0) {
    // If current character in X and Y are equal, then the current character is
    // part of Longest common subsequence
    if (X[i - 1] == Y[j - 1]) {
      // Put current character in LCS array
      LCS[currIdx] = X[i - 1];

      // reduce value of i
      i--;

      // reduce value of j
      j--;

      // reduce value of currIdx
      currIdx--;
    }

    // If the characters are not same, then find the larger of two and go in the
    // direction of larger value
    else if (dp[i - 1][j] > dp[i][j - 1])
      i--;
    else
      j--;
  }

  // print the Longest common subsequence string
  for (char c : LCS) {
    cout << c;
  }
  cout << "\n";
}
