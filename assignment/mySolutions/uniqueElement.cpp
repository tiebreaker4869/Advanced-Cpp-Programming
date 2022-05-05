#include <iostream>

using namespace std;

int main(){
    int ans = 0;
    int x;
    while(cin >> x){
        ans ^= x;
    }
    cout << ans << endl;
    
    return 0;
}