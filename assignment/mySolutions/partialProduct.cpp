#include <iostream>

using namespace std;

typedef long long ll;

int main(){
    int n;
    cin >> n;
    ll res = 1, x;
    while(n -- ){
        cin >> x;
        if(res * x > 2147483647 || res * x < -2147483648){
            cout << -1;
            break;
        }
        res = res * x;
        cout << res << " ";
    }
    return 0;
}