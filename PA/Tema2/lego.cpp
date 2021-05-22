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

        void read_input(){
            ifstream in;
            in.open("lego.in");
            in >> k >> n >> t;
            in.close();
        }

        void get_possible_pieces(int index) {
            for (int i = possible_pieces[index - 1] + 1; i <= k; i++) {
                possible_pieces[index] = i;

                if (index == n) check_solution(); 
                else get_possible_pieces(index + 1);
            }
        }

        void print_solution() {
            ofstream out;
            out.open("lego.out");
            out << solution << "\n";
            for (int i = 1; i <= n; i++) {
                out << solution_pieces[i] << " ";
            }
            out.close();
        }

        void check_solution() {
            int max_consecutive_numbers = -1;
            int consecutive_numbers = 0;

            for (int i = 1; i <= possible_pieces[n] * t; i++) {
                if (can_make_number_with_pieces(possible_pieces, i, t)) {
                    consecutive_numbers++;
                } else {
                    if (consecutive_numbers > max_consecutive_numbers) {
                        max_consecutive_numbers = consecutive_numbers;
                    }
                    consecutive_numbers = 0;
                }
            }
            if (consecutive_numbers > max_consecutive_numbers) {
                max_consecutive_numbers = consecutive_numbers;
            }
            
            if (max_consecutive_numbers > solution) {
                solution = max_consecutive_numbers;
                memcpy(solution_pieces, possible_pieces, (n + 1) * sizeof(int));
            }

        }

        bool can_make_number_with_pieces(int *pieces, int number, int depth) {
            if (number == 0) return true;
            if (depth == 0) return false;
            for (int i = 1; i <= n; i++) {
                if (can_make_number_with_pieces(pieces, number - pieces[i], depth - 1)) return true;
            }
            return false;
        }
};


int main() {
    auto *solution = new Solution();
    solution->solve();
    delete solution;
    return 0;
}