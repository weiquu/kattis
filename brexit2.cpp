#include <iostream>
#include <vector>

using namespace std;

int main() {
    int countries, partnerships, home, left;
    cin >> countries >> partnerships >> home >> left;
    home--; left--;

    vector<int> currPartnerships(countries, 0);
    vector<vector<int> > partners(countries, vector<int>());
    for (int i=0; i<partnerships; i++) {
        int c1, c2; cin >> c1 >> c2; c1--; c2--;
        currPartnerships[c1]++;
        currPartnerships[c2]++;
        partners[c1].push_back(c2);
        partners[c2].push_back(c1);
    }
    for (int i=0; i<countries; i++) {
        currPartnerships[i] -= (currPartnerships[i]/2);
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
        for (int j=0; j<partners[left].size(); j++) {
            int victim = partners[left][j];
            if (!hasLeftVec[victim]) {
                currPartnerships[victim]--;
                if (currPartnerships[victim]==0) {
                    if (victim==home) {
                        homeLeft = true;
                        break;
                    }
                    leaving.push_back(victim);
                    hasLeftVec[victim] = true;
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