#include <bits/stdc++.h>
#include <fstream>

using namespace std;

/**
 * @brief  Verifica daca o coordonata e pe uscat
 * @note   
 * @param  x: linia
 * @param  y: coloana
 * @param  n: numarul total de linii
 * @param  m: numarul total de coloane
 * @retval 
 */
bool is_finish(int x, int y, int n, int m) {
    return (x == 0 || x == n + 1 || y == 0 || y == m + 1);
}

/**
 * @brief  Calculeaza distanta minima pana la tarm
 * @note   
 * @param  x: linia initiala
 * @param  y: coloana initiala
 * @param  grid: harta
 * @param  n: numarul de linii
 * @param  m: numarul de coloane
 * @retval distanta minima
 */
int shortest_path(int x, int y, vector<vector<char>> grid, int n, int m) {
    queue<pair<int, int>> q;
    vector<vector<int>> dist(n + 2, vector<int>(m + 2, 0));

    q.push(make_pair(x, y));

    dist[x][y] = 0;

    while (!q.empty()) {
        pair<int, int> pos = q.front();
        int current_dist = dist[pos.first][pos.second];

        // Verifica daca pozitia e pe mal
        if (is_finish(pos.first, pos.second, n, m)) {
            return current_dist;
        }

        pair<int, int> move_aux;

        if (grid[pos.first][pos.second] == 'V') {
            // Adauga pozitiile de pe verticala
            move_aux = make_pair(pos.first + 1, pos.second);
            if (grid[move_aux.first][move_aux.second] != '.') {
                q.push(move_aux);
                dist[move_aux.first][move_aux.second] = current_dist + 1;
            }

            move_aux = make_pair(pos.first - 1, pos.second);
            if (grid[move_aux.first][move_aux.second] != '.') {
                q.push(move_aux);
                dist[move_aux.first][move_aux.second] = current_dist + 1;
            }
        } else if (grid[pos.first][pos.second] == 'O') {
            // Adauga pozitiile de pe orizontala
            move_aux = make_pair(pos.first, pos.second + 1);
            if (grid[move_aux.first][move_aux.second] != '.') {
                q.push(move_aux);
                dist[move_aux.first][move_aux.second] = current_dist + 1;
            }

            move_aux = make_pair(pos.first, pos.second - 1);
            if (grid[move_aux.first][move_aux.second] != '.') {
                q.push(move_aux);
                dist[move_aux.first][move_aux.second] = current_dist + 1;
            }
        } else if (grid[pos.first][pos.second] == 'D') {
            // Adauga pozitiile de pe orizontala si verticala
            move_aux = make_pair(pos.first + 1, pos.second);
            if (grid[move_aux.first][move_aux.second] != '.') {
                q.push(move_aux);
                dist[move_aux.first][move_aux.second] = current_dist + 1;
            }

            move_aux = make_pair(pos.first - 1, pos.second);
            if (grid[move_aux.first][move_aux.second] != '.') {
                q.push(move_aux);
                dist[move_aux.first][move_aux.second] = current_dist + 1;
            }

            move_aux = make_pair(pos.first, pos.second + 1);
            if (grid[move_aux.first][move_aux.second] != '.') {
                q.push(move_aux);
                dist[move_aux.first][move_aux.second] = current_dist + 1;
            }

            move_aux = make_pair(pos.first, pos.second - 1);
            if (grid[move_aux.first][move_aux.second] != '.') {
                q.push(move_aux);
                dist[move_aux.first][move_aux.second] = current_dist + 1;
            }
        }
        // Marcheaza pozitia ca fiind vizitata si scoate din coada
        grid[pos.first][pos.second] = '.';
        q.pop();
    }

    return -1;
}

int main() {
    ifstream in;
    ofstream out;

    in.open("poduri.in");
    out.open("poduri.out");

    // Read input
    int n, m, x, y;
    in >> n >> m >> x >> y;

    vector<vector<char>> grid(n + 2, vector<char>(m + 2, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            in >> grid[i][j];
        }
    }

    out << shortest_path(x, y, grid, n, m);

    in.close();
    out.close();
    return 0;
}
