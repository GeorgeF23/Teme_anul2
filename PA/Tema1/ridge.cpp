#include <bits/stdc++.h>

#define MIN2(a, b) min(dp[i - 1][a], dp[i - 1][b])
#define MIN3 min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2]))

using namespace std;

typedef vector<long long> v1d;
typedef vector<v1d> v2d;

struct mountain {
    int height;
    int cost;
};


int main() {
    ifstream fin;
    ofstream fout;

    fin.open("ridge.in");
    fout.open("ridge.out");

    int no_mountains;
    fin >> no_mountains;

    vector<mountain> mountains(no_mountains);
    v2d dp(no_mountains, v1d(3, 0));

    // Read input from file
    for (int i = 0; i < no_mountains; i++) {
        int height, cost;
        fin >> height >> cost;
        mountains[i] = (mountain){height, cost};
    }

    for (int i = 0; i < no_mountains; i++) {
        if (i == 0) {
            // Base case
            dp[i][0] = 0;
            dp[i][1] = 1LL * mountains[i].cost;
            dp[i][2] = 2LL * mountains[i].cost;
        } else {
            // Conditional checks to make sure that the heights will not
            // be the same after digging
            if (mountains[i - 1].height == mountains[i].height) {
                dp[i][0] = MIN2(1, 2);
                dp[i][1] = MIN2(0, 2) + 1LL * mountains[i].cost;
                dp[i][2] = MIN2(0, 1) + 2LL * mountains[i].cost;
            } else if (mountains[i - 1].height + 1 == mountains[i].height) {
                dp[i][0] = MIN3;
                dp[i][1] = MIN2(1, 2) + 1LL * mountains[i].cost;
                dp[i][2] = MIN2(0, 2) + 2LL * mountains[i].cost;
            } else if (mountains[i - 1].height + 2 == mountains[i].height) {
                dp[i][0] = MIN3;
                dp[i][1] = MIN3 + 1LL * mountains[i].cost;
                dp[i][2] = MIN2(0, 1) + 2LL * mountains[i].cost;
            } else if (mountains[i - 1].height - 1 == mountains[i].height) {
                dp[i][0] = MIN2(0, 2);
                dp[i][1] = MIN2(0, 1) + 1LL * mountains[i].cost;
                dp[i][2] = MIN3 + 2LL * mountains[i].cost;
            } else if (mountains[i - 1].height - 2 == mountains[i].height) {
                dp[i][0] = MIN2(0, 1);
                dp[i][1] = MIN3 + 1LL * mountains[i].cost;
                dp[i][2] = MIN3 + 2LL * mountains[i].cost;
            } else {
                dp[i][0] = MIN3;
                dp[i][1] = MIN3 + 1LL * mountains[i].cost;
                dp[i][2] = MIN3 + 2LL * mountains[i].cost;
            }
        }
        // Heights can not be negative
        if (mountains[i].height < 2) {
            dp[i][2] = LONG_LONG_MAX;
        }
        if (mountains[i].height < 1) {
            dp[i][1] = LONG_LONG_MAX;
        }
    }

    int i = no_mountains;   // For the macro to work
    fout << MIN3;

    fin.close();
    fout.close();
    return 0;
}
