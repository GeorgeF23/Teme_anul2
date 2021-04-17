#include <bits/stdc++.h>

using namespace std;

struct computer {
    int power;
    int cost;
};

/**
 * Comapre functions for sorting computers by their power
 */
bool cmp(computer a, computer b) {
    return a.power < b.power;
}



int main() {
    ifstream fin;
    ofstream fout;

    fin.open("crypto.in");
    fout.open("crypto.out");


    int no_computers, money, best_power, last_upgrade = 0;
    fin >> no_computers >> money;

    vector<computer> computers(no_computers);

    // c[i] = cost to upgrade the first i computers to the i'th computer power
    vector<long long> c(no_computers, 0);
    // total_cost[i] = cost to upgrade the first i computers once
    vector<long long> total_cost(no_computers, 0);

    // Read computers info from file
    for (int i = 0; i < no_computers; i++) {
        int power, cost;
        fin >> power >> cost;

        computers[i] = (computer){power, cost};
    }

    // Sort computers by power
    sort(computers.begin(), computers.end(), cmp);

    best_power = computers[0].power;    // Worst power we could have
    total_cost[0] = 1LL * computers[0].cost;


    for (int i = 1; i < no_computers; i++) {
        total_cost[i] = total_cost[i - 1] + 1LL * computers[i].cost;

        int power_difference = (computers[i].power - computers[i - 1].power);
        c[i] = c[i - 1] + power_difference * total_cost[i - 1];

        if (c[i] <= money) {
            // We can upgrade the first i computers to i'th computer's power
            best_power = computers[i].power;
            last_upgrade = i;
        } else {
            // The cost is too big, no point in continuing
            break;
        }
    }


    // Check if we can still make some upgrades
    if (money - c[last_upgrade] > total_cost[last_upgrade]) {
        best_power += (money - c[last_upgrade]) / total_cost[last_upgrade];
    }

    fout << best_power;

    fin.close();
    fout.close();
    return 0;
}
