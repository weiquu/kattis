#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int commands;
    cin >> commands;

    while (commands!=0) {
        vector<int> reg(32, -1);
        for (int i=0; i<commands; i++) {
            string command;
            cin >> command;
            if (command == "CLEAR") {
                int loc;
                cin >> loc;
                reg[loc] = 0;
            }
            else if (command == "SET") {
                int loc;
                cin >> loc;
                reg[loc] = 1;
            }
            else if (command == "OR") {
                int loc, comp;
                cin >> loc >> comp;
                if (reg[loc]==1 || reg[comp]==1) {
                    reg[loc] = 1;
                }
                else if (reg[loc]==0 && reg[comp]==0) {
                    reg[loc] = 0;
                }
                else {
                    reg[loc] = -1;
                }
            }
            else if (command == "AND") {
                int loc, comp;
                cin >> loc >> comp;
                if (reg[loc]==0 || reg[comp]==0) {
                    reg[loc] = 0;
                }
                else if (reg[loc]==1 && reg[comp]==1) {
                    reg[loc] = 1;
                }
                else {
                    reg[loc] = -1;
                }
            }
        }

        for (int i=31; i>=0; i--) {
            if (reg[i]==-1) {
                cout << "?";
            }
            else {
                cout << reg[i];
            }
        }
        cout << "\n";

        cin >> commands;
    }
}