#include <bits/stdc++.h>

using namespace std;

// Easy way to define a 3d matrix
typedef vector<int> v1d;
typedef vector<v1d> v2d;
typedef vector<v2d> v3d;


struct stock {
    int current_value;
    int loss;
    int profit;
};

/**
 * Checks if a stock could be included in the solution
 */
void check_stock(stock s, v3d *dp, int i, int value, int loss) {
    // Initially we suppose that we don't consider buying the stock
    (*dp)[i][value][loss] = (*dp)[i - 1][value][loss];
    // We check if we could consider the stock
    if (s.loss <= loss && value >= s.current_value) {
        int aux = (*dp)[i - 1][value - s.current_value][loss -s.loss];

        // We buy the stock only if it makes us more profit
        (*dp)[i][value][loss] = max((*dp)[i][value][loss], aux + s.profit);
    }
}

int main() {
    ifstream fin;
    ofstream fout;

    fin.open("stocks.in");
    fout.open("stocks.out");

    int no_stocks, budget, max_loss;
    fin >> no_stocks >> budget >> max_loss;

    vector<stock> stocks(no_stocks + 1);
    v3d dp(no_stocks + 1, v2d(budget + 1, v1d(max_loss + 1, 0)));

    // Read the input from the file
    for (int i = 1; i <= no_stocks; i++) {
        int current_value, min_value, max_value;
        fin >> current_value >> min_value >> max_value;

        int loss = current_value - min_value;
        int profit = max_value - current_value;
        stocks[i] = (stock){current_value, loss, profit};
    }

    // We solve the problem using DP by considering smaller problems
    // that have less stocks to take in consideration, smaller budget
    // and smaller max_loss
    for (int i = 1; i <= no_stocks; i++) {
        for (int value = 0; value <= budget; value++) {
            for (int loss = 0; loss <= max_loss; loss++) {
                check_stock(stocks[i], &dp, i, value, loss);
            }
        }
    }

    fout << dp[no_stocks][budget][max_loss];

    fin.close();
    fout.close();
    return 0;
}
