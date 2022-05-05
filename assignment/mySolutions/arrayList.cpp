#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 100010;

int a[N];

int sz, capacity;

char op[10];

void add(int x){
    if(sz == 0){
        capacity = 10;
        a[++sz] = x;
        return;
    }
    a[++sz] = x;
    if(sz == capacity)capacity = capacity + (capacity >> 1);
}

int get(int x){
    if(x+1 > sz)return -1;
    else return a[x+1];
}

void remove(int x){
    for(int i = 1; i <= sz; i ++){
        if(a[i] == x){
            for(int j = i; j < sz; j ++){
                a[j] = a[j+1];
            }
            sz --;
            return;
        }
    }
}

int getSize(){
    return sz;
}

int getCapacity(){
    return capacity;
}

int main(){
    int n, x;
    cin >> n;
    while(n -- ){
        scanf("%s", op);
        if(strcmp(op, "add") == 0){
            cin >> x;
            add(x);
        }else if(strcmp(op, "remove") == 0){
            cin >> x;
            remove(x);
        }else if(strcmp(op, "get") == 0){
            cin >> x;
            cout << get(x) << " " << endl;
        }else if(strcmp(op, "getSize") == 0){
            cout << getSize() <<" " << endl;
        }else{
            cout << getCapacity() << " " << endl;
        }
    }
    
    return 0;
}