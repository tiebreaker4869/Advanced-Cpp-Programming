#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main(){
    string s;
    cin >> s;
    if(s == "0"){
        cout << s << endl;
        return 0;
    }
    bool isNegative = s[0] == '-';
    if(isNegative)s = s.substr(1);
    while(s.back() == '0')s = s.substr(0, s.size()-1);
    reverse(s.begin(), s.end());
    if(isNegative && s.size() >= 10 && s > "2147483648"){
        cout << -1 << endl;
        return 0;
    }
    if(!isNegative && s.size() >= 10 && s > "2147483647"){
        cout << -1 << endl;
        return 0;
    }
    if(isNegative)s = "-" + s;
    cout << s << endl;
    
    return 0;
}