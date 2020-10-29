#include <iostream>
#include <cmath>
#include <string>
#include <vector>

typedef unsigned long long int ull;

using namespace std;

string sixteen(ull num) {
    string s;
    vector<string> temp(16);
    temp[0]="0"; temp[1]="1"; temp[2]="2"; temp[3]="3"; temp[4]="4"; temp[5]="5"; temp[6]="6"; temp[7]="7"; temp[8]="8";
    temp[9]="9"; temp[10]="A"; temp[11]="B"; temp[12]="C"; temp[13]="D"; temp[14]="E"; temp[15]="F";
    int i=1;
    while (true) {
        if (pow(16, i) > num) {
            break;
        }
        else {
            i++;
        }
    } //i is no. of digits
    //cout << i << "\n";
    i--;

    while (i>=0) {
        ull power = pow(16, i);
        int digit = num/power;
        //cout << i << ": " << digit << "\n";
        s = s + temp[digit];
        num -= power*digit;
        i--;
    }

    return s;
}

ull eight(string num) {
    ull total = 0;
    int power = num.size()-1;
    for (auto c : num) {
        int digit = c - '0';
        total += pow(8, power)*digit;
        power--;
    }
    return total;
}

int main() {
    string num; cin >> num;
    ull x = eight(num);
    //cout << x << "\n";
    string ans = sixteen(x);
    cout << ans << "\n";
}