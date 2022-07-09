// Alexis Sofia Ambray
// CSALGCM - N01
// P4: Party Scheduling

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void partyBudget(vector<string>);

// function for spliting the string according to the separator character
vector<string> splitString(string s, char separator);

int main() {
  // list for inputs
  vector<string> inputs;

  string input;
  getline(cin, input);

  inputs.push_back(input);
  int n = stoi(splitString(inputs[0], ' ')[1]);

  for (int i = 0; i < n; i++) {
    getline(cin, input);
    inputs.push_back(input);
  }

  // call the partyBudget function
  partyBudget(inputs);
}

void partyBudget(vector<string> inputs) {
  // Extract the party Budget and the number of parties
  int partyBudget = stoi(splitString(inputs[0], ' ')[0]);
  int n = stoi(splitString(inputs[0], ' ')[1]);

  // party[i][0] indicates the entrance fee of ith party
  // party[i][1] indicates the fun at ith party
  vector<vector<int> > party(n, vector<int>(2));

  for (int i = 0; i < n; i++) {
    vector<string> input = splitString(inputs[i + 1], ' ');

    party[i][0] = stoi(input[0]);
    party[i][1] = stoi(input[1]);
  }

  // dp[i][j] denotes the maximum fun till ith party with j amount of budget
  vector<vector<int> > dp(n + 1, vector<int>(partyBudget + 1));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= partyBudget; j++) {
      // if the party's entrance fee is within the budget
      if (party[i - 1][0] <= j) {
        // There are two choices here: Consider this party or do not consider
        // this party
        dp[i][j] =
            max(party[i - 1][1] + dp[i - 1][j - party[i - 1][0]], dp[i - 1][j]);
      } else {
        // The party's entrance fee is out of the budget. We cannot consider
        // this party
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  // get the maximum fun
  int maxFun = dp[n][partyBudget];

  // sumOfEntranceFees denotes the sum of the entrance fees of the parties for
  // maximum fun
  int sumOfEntranceFees = 0;

  for (int i = 0; i <= partyBudget; i++) {
    if (dp[n][i] == maxFun) {
      sumOfEntranceFees = i;
      break;
    }
  }

  // print the sum of the entrance fees and the max fun
  cout << sumOfEntranceFees << " " << maxFun << endl;
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
