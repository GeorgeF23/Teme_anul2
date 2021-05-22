#include <bits/stdc++.h>

using namespace std;

#define MAX_N 10

class Solution {
 public:
    void solve() {
        read_input();
        possible_pieces[1] = 1;
        get_possible_pieces(2);
        print_solution();
    }

 private:
    int possible_pieces[MAX_N + 1];
    int k, n, t;

    int solution = -1;
    int solution_pieces[MAX_N + 1];

    // Read the input from the file
    void read_input() {
        ifstream in;
        in.open("lego.in");
        in >> k >> n >> t;
        in.close();
    }

    // Generate all possible combinations of pieces using backtracking
    void get_possible_pieces(int index) {
        for (int i = possible_pieces[index - 1] + 1; i <= k; i++) {
            possible_pieces[index] = i;

            if (index == n)
                check_solution();   // When a combination is made, check it
            else
                get_possible_pieces(index + 1);
        }
    }

    // Print the solution to the file
    void print_solution() {
        ofstream out;
        out.open("lego.out");
        out << solution << "\n";
        for (int i = 1; i <= n; i++) {
            out << solution_pieces[i] << " ";
        }
        out.close();
    }

    // Checks if the current solution is better than the last one
    void check_solution() {
        int consecutive_numbers = get_consecutive_numbers(possible_pieces);
        if (consecutive_numbers > solution) {
            solution = consecutive_numbers;
            memcpy(solution_pieces, possible_pieces, (n + 1) * sizeof(int));
        }
    }

    // Get the number of consecutive numebers that can be made with n pieces
    int get_consecutive_numbers(int *pieces) {
        // dp[i] = number of pieces required to make number i
        vector<int> dp(t * pieces[n] + 1, INT_MAX);
        int max_consecutive = 0;
        int current_consecutive = 0;

        // The numbers equal to the pieces can be made with one piece
        for (int i = 1; i <= n; i++) {
            dp[pieces[i]] = 1;
        }

        for (int i = 2; i <= t * pieces[n]; i++) {
            if (dp[i] == INT_MAX) {
                // If a number is not yet calculated
                int best_piece = 1;
                // Find the piece that will result in the smallest amount
                // of pieces used to make the number
                for (int j = 1; j <= n; j++) {
                    int piece = pieces[j];

                    if (i - piece < 1) continue;

                    if (dp[i - piece] < dp[i - best_piece]) {
                        best_piece = piece;
                    }
                }
                dp[i] = 1 + dp[i - best_piece];
            }
        }

        // Count how many consecutive numbers can be made
        for (int i = 1; i <= t * pieces[n]; i++) {
            if (dp[i] <= t) {
                current_consecutive++;
            } else {
                if (current_consecutive > max_consecutive) {
                    max_consecutive = current_consecutive;
                }
                current_consecutive = 0;
            }
        }

        if (current_consecutive > max_consecutive) {
            max_consecutive = current_consecutive;
        }
        return max_consecutive;
    }
};


int main() {
    auto *solution = new Solution();
    solution->solve();
    delete solution;
    return 0;
}
