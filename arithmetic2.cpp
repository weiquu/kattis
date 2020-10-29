#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    string num, eight, sixteen; cin >> num; eight=""; sixteen="";
    map<char, string> eightToTwo; eightToTwo['0']="000"; eightToTwo['1']="001"; eightToTwo['2']="010"; eightToTwo['3']="011";
    eightToTwo['4']="100"; eightToTwo['5']="101"; eightToTwo['6']="110"; eightToTwo['7']="111";
    map<string, string> twoToSixteen; twoToSixteen["0000"]="0"; twoToSixteen["0001"]="1"; twoToSixteen["0010"]="2"; twoToSixteen["0011"]="3";
    twoToSixteen["0100"]="4"; twoToSixteen["0101"]="5"; twoToSixteen["0110"]="6"; twoToSixteen["0111"]="7";
    twoToSixteen["1000"]="8"; twoToSixteen["1001"]="9"; twoToSixteen["1010"]="A"; twoToSixteen["1011"]="B";
    twoToSixteen["1100"]="C"; twoToSixteen["1101"]="D"; twoToSixteen["1110"]="E"; twoToSixteen["1111"]="F";
    
    for (auto c : num) {
        eight += eightToTwo[c];
    }

    int size = eight.size();
    size = size%4;
    if (size==1) {
        eight = "000" + eight;
    }
    else if (size==2) {
        eight = "00" + eight;
    }
    else if (size==3) {
        eight = "0" + eight;
    }

    for (int i=0; i<eight.size(); i+=4) {
        sixteen += twoToSixteen[eight.substr(i, 4)];
    }

    int count = 0;
    for (auto c : sixteen) {
        if (c=='0') {
            count++;
        }
        else {
            break;
        }
    }
    if (count!=0) {
        if (count==sixteen.size()) {
            sixteen = "0";
        }
        else {
            sixteen = sixteen.substr(count);
        }
    }
    cout << sixteen << "\n";
}