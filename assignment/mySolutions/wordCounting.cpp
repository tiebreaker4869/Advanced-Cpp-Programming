#include <iostream>

using namespace std;
enum STATE{
    INIT,
    COUNTING,
    SPACING,
    ENTERING
};

int main(){
    int wc = 0, cc = 0, lc = 0;
    char ch;
    STATE state = INIT;
    //be careful about the case that starts with space.
    while(cin.get(ch)){
        if(ch == ' '){
            cc ++;
            if(state == COUNTING){
                wc ++;
            }
            state = SPACING;
        }else if(ch == '\n'){
            if(state == COUNTING){
                wc ++;
            }
            state = ENTERING;
            cc ++;
            lc ++;
        }else{
            cc ++;
            state = COUNTING;
        }
    }
    
    cout << cc <<" " << wc << " " << lc << endl;
    
    return 0;
}