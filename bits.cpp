#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int getBinary(int num) {
    int i=1;
    while (true) {
        if (pow(2, i)>num) {
            break;
        }
        i++;
    }
    //i is num of digits
    int digit, temp;
    int count = 0;
    while (num>0) {
        temp = pow(2, i-1);
        digit = num/temp;
        if (digit==1) {
            count++;
        }
        num = num%temp;
        i--;
    }
    
    return count;
}

int main() {
    int cases;
    cin >> cases;
    for (int i=0; i<cases; i++) {
        string num;
        string temp = "";
        int val, count, tempCount;
        count = 0;
        cin >> num;
        for (auto j : num) {
            temp += j;
            val = stoi(temp);
            tempCount = getBinary(val);
            count = max(count, tempCount);
        }

        cout << count << "\n";
    }
}