#include <iostream>

using namespace std;

int main(){
    string s;
    int n;
    cin >> s >> n;
    int len = s.size();
    string res = "";
    if(len == 1 || n == 1){
        cout << s << endl;
        return 0;
    }
    for(int i = 0; i < n; i ++){
        if(i == 0 || i == n-1){
            int index = i;
            while(index < len){
                res += s[index];
                index += n + n - 2;
            }
        }else{
            int index = i;
            bool inZ = false;
            while(index < len){
                res += s[index];
                if(!inZ){
                    index += n - 1 - i + n - 1 - i;
                }else{
                    index += i + i;
                }
                inZ = !inZ;
            }
        }
    }
    cout << res << endl;
    
    return 0;
}