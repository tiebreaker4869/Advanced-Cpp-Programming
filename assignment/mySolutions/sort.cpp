#include <iostream>
#include <cstddef>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

bool cmp_option_none(const string& s1, const string& s2){
    return s1 <= s2;
}

bool cmp_option_n(const string& s1, const string& s2){
    return stoi(s1) <= stoi(s2);
}


bool cmp_option_r(const string& s1, const string& s2){
    return s1 > s2;
}

bool cmp_option_i(const string& s1, const string& s2){
    if(s1 == s2)return true;
    string t1 = "", t2 = "";
    for(int i = 0; s1[i]; i++)t1 = t1 + (char)tolower(s1[i]);
    for(int i = 0; s2[i]; i++)t2 = t2 + (char)tolower(s2[i]);
    if(t1 == t2){
        return s1 < s2;
    }
    return t1 <= t2;
}

bool cmp_option_d(const string& s1, const string& s2){
    int i = 0, j = 0;
    string t1 = "", t2 = "";
    int len1 = s1.size(), len2 = s2.size();
    
    for(int i = 0; i < len1; i ++){
        if(isalpha(s1[i]) || isdigit(s1[i]) || s1[i]==' ')t1 = t1 + s1[i];
    }
    
    for(int i = 0; i < len2; i ++){
        if(isalpha(s2[i]) || isdigit(s2[i]) || s2[i] == ' ')t2 = t2 + s2[i];
    }
    
    return t1 <= t2;
}

int main(){
    string s;
    vector<string> str;
    int n, c;
    cin >> n;
    cin >> ws;
    for(int i = 0; i < n; i ++){
        getline(cin, s);
        str.push_back(s);
    }
    
    cin >> c;
    while(c--){
        cin >> s;
        switch(s[0]){
            case '-':
                sort(str.begin(), str.end(), cmp_option_none);
                break;
            case 'n':
                sort(str.begin(), str.end(), cmp_option_n);
                break;
            case 'i':
                sort(str.begin(), str.end(), cmp_option_i);
                break;
            case 'd':
                sort(str.begin(), str.end(), cmp_option_d);
                break;
            case 'r':
                sort(str.begin(), str.end(), cmp_option_r);
                break;
        }
        for(const string& t : str){
            cout << t << endl;
        }
    }
    return 0;
}