// Alexis Sofia Ambray
// CSALGCM - N01
// P4: Matrix Chain Multiplication

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// function for splitting the string according to the separator character
vector<string> splitString(string s, char separator);

void assignTable(vector<string> input);

// Function for printing the optimal parenthesis of matrix chain multiplication
void printOptimalParenthesis(int i,
                             int j,
                             int n,
                             vector<vector<int> > bracketBreakPoint,
                             vector<string> input,
                             int& matrixIdx);

int main() {
  // list for inputs
  vector<string> inputs;

  string input;
  getline(cin, input);

  inputs.push_back(input);

  // get the number of the inputs
  int n = stoi(input);

  for (int i = 0; i < n; i++) {
    getline(cin, input);
    inputs.push_back(input);
  }

  // call the assignTable function
  assignTable(inputs);
}

void assignTable(vector<string> input) {
  int n = input.size();

  // Dimensions of ith matrix is denoted by matrixDimension[i] *
  // matrixDimension[i + 1] where 0 <= i <= n - 1
  vector<int> matrixDimension(n);

  for (int i = 1; i < n; i++) {
    matrixDimension[i - 1] = stoi(splitString(input[i], ' ')[1]);
  }

  matrixDimension[matrixDimension.size() - 1] =
      stoi(splitString(input[n - 1], ' ')[2]);

  // dp[i][j] denotes Minimum number of scalar multiplications
  // needed to compute the matrix matrix[i] * matrix[i+1]...matrix[j]
  vector<vector<int> > dp(n, vector<int>(n));

  // bracketBreakPoint[i][j] stores the optimal break point index
  vector<vector<int> > bracketBreakPoint(n, vector<int>(n));

  // L is chain length.
  for (int L = 2; L < n; L++) {
    for (int i = 1; i < n - L + 1; i++) {
      int j = i + L - 1;
      dp[i][j] = INT_MAX;
      for (int k = i; k <= j - 1; k++) {
        // q = cost/scalar multiplications
        int q =
            dp[i][k] + dp[k + 1][j] +
            matrixDimension[i - 1] * matrixDimension[k] * matrixDimension[j];

        // if the current cost is less
        if (q < dp[i][j]) {
          dp[i][j] = q;

          // kth index is the break point of the selected segment
          bracketBreakPoint[i][j] = k;
        }
      }
    }
  }

  // matrixIdx is used to print the matrix name in printOptimalParenthesis
  // function
  int matrixIdx = 1;

  printOptimalParenthesis(1, n - 1, n, bracketBreakPoint, input, matrixIdx);
}

// Function for printing the optimal
// parenthesization of a matrix chain product
void printOptimalParenthesis(int i,
                             int j,
                             int n,
                             vector<vector<int> > bracketBreakPoint,
                             vector<string> input,
                             int& matrixIdx) {
  // If only one matrix is left
  if (i == j) {
    cout << input[matrixIdx][0];
    matrixIdx++;
    return;
  }

  if (!(i == 1 && j == n - 1))
    cout << "(";

  // Put brackets around the matrices from ith index to bracketBreakPoint[i][j]
  // index.
  printOptimalParenthesis(i, bracketBreakPoint[i][j], n, bracketBreakPoint,
                          input, matrixIdx);

  // Put brackets around the matrices from bracketBreakPoint[i][j] + 1 index to
  // jth index.
  printOptimalParenthesis(bracketBreakPoint[i][j] + 1, j, n, bracketBreakPoint,
                          input, matrixIdx);

  if (!(i == 1 && j == n - 1))
    cout << ")";
}

// function for spliting the string according to separator string
vector<string> splitString(string str, char separator) {
  vector<string> inputs;
  string input = "";
  for (auto x : str) {
    if (x == separator) {
      inputs.push_back(input);
      input = "";
    } else {
      input = input + x;
    }
  }
  inputs.push_back(input);
  return inputs;
}
