#include <iostream>
#include <cstdint>
#include <string>

using namespace std;

const int INF = 10010;

uint8_t a[INF];

int stk[INF];

char stk2[INF];

int idx, pc, sp, sp2;

int main(){
    string cmd;
    getline(cin, cmd);
    int len = cmd.size();
    char c;
    uint8_t byte;
    while(pc < len){
        if(cmd[pc] == '>')idx ++;
        else if(cmd[pc] == '<')idx --;
        else if(cmd[pc] == '+')a[idx] ++;
        else if(cmd[pc] == '-')a[idx] --;
        else if(cmd[pc] == ','){
            if((c = getchar()) == EOF){
                byte = 0;
                a[idx] = byte;
            }else a[idx] = c;
        }else if(cmd[pc] == '.'){
            cout << a[idx];
        }else if(cmd[pc] == '['){
            if(!a[idx]){
                stk2[++sp2] = '[';
                int cur = pc;
                while(sp2){
                    cur ++;
                    if(cmd[cur] == ']')sp2--;
                    else if(cmd[cur] == '[')stk2[++sp2] = '[';
                }
                pc = cur;
            }else stk[++sp] = pc;
        }
        else if(cmd[pc] == ']'){
            if(a[idx])pc = stk[sp];
            if(!a[idx])--sp;
        }
        pc ++;
    }
    
    return 0;
}