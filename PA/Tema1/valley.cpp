#include <bits/stdc++.h>

using namespace std;

/**
 * Computes the number of hours required to make the valley
 * 
 * peaks:   vector that contains the heights of the peaks
 * no_peaks:    number of peaks in the vector
 * 
 * return: the hours required to make the valley
 */
long long solve(vector<int> peaks, int no_peaks) {
    long long hours = 0;
    int bottom = 1;

    // Search the minimum value between the first and last element in vector
    for (int i = 2; i < no_peaks - 1; i++) {
        if (peaks[i] < peaks[bottom]) {
            bottom = i;
        }
    }

    // Dig on the left side
    for (int i = 1; i <= bottom; i++) {
        if (peaks[i] > peaks[i - 1]) {
            hours += peaks[i] - peaks[i - 1];
            peaks[i] = peaks[i - 1];
        }
    }

    // Dig on the right side
    for (int i = no_peaks - 2; i >= bottom; i--) {
        if (peaks[i] > peaks[i + 1]) {
            hours += peaks[i] - peaks[i + 1];
            peaks[i] = peaks[i + 1];
        }
    }

    return hours;
}

int main() {
    ifstream fin;
    ofstream fout;

    fin.open("valley.in");
    fout.open("valley.out");

    int no_peaks;
    fin >> no_peaks;

    vector<int> peaks(no_peaks);

    for (int i = 0; i < no_peaks; i++) {
        fin >> peaks[i];
    }

    fout << solve(peaks, no_peaks);

    fin.close();
    fout.close();
    return 0;
}
