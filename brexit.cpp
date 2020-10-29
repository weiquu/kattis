#include <iostream>
#include <vector>

using namespace std;

int main() {
    int countries, partnerships, home, left;
    cin >> countries >> partnerships >> home >> left;
    home--; left--;

    vector<int> initialPartnerships(countries, 0);
    vector<int> currPartnerships(countries, 0);
    vector<vector<bool> > partners(countries, vector<bool>(countries, false));
    for (int i=0; i<partnerships; i++) {
        int c1, c2; cin >> c1 >> c2; c1--; c2--;
        initialPartnerships[c1]++;
        initialPartnerships[c2]++;
        currPartnerships[c1]++;
        currPartnerships[c2]++;
        partners[c1][c2] = true;
        partners[c2][c1] = true;
    }

    vector<int> leaving;
    vector<bool> hasLeftVec(countries, false);
    leaving.push_back(left);
    hasLeftVec[left] = true;
    int i=0;
    bool homeLeft = false;
    if (left==home) {
        homeLeft = true;
    }
    while (i<leaving.size() && !homeLeft) {
        left = leaving[i];
        for (int j=0; j<countries; j++) {
            if (partners[left][j]) {
                currPartnerships[j]--;
                if (currPartnerships[j]<=initialPartnerships[j]/2) {
                    //maybe have another indicator to see if they have decided to leave alr
                    if (j==home) {
                        homeLeft = true;
                        break;
                    }
                    if (!hasLeftVec[j]) {
                        leaving.push_back(j);
                        hasLeftVec[j] = true;
                    }
                }
            }
        }
        i++;
    }

    if (homeLeft) {
        cout << "leave\n";
    }
    else {
        cout << "stay\n";
    }
}