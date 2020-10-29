#include <iostream>
#include <string>

using namespace std;

int main() {
    int games;
    cin >> games;
    for (int i=0; i<games; i++) {
        cout << "5 1 5 6\n";
        string move;
        cin >> move;
        while (move == "MOVE") {
            int aRow, aCol, bRow, bCol;
            cin >> aRow >> aCol >> bRow >> bCol;
            if (bRow==5) {
                bRow=4;
            }
            cout << 5-bRow << " " << 7-bCol << " " << 5-aRow << " " << 7-aCol << "\n";
            cin >> move;
        }
    }
}