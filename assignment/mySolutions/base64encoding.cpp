#include <iostream>
#include <vector>

using namespace std;

string base64map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

string base64encoder(vector<char>& chs, int ptr){
    string res = "";
    int len = chs.size();
    if(ptr <= len-3){
    unsigned int x = (chs[ptr] & 0xff) << 16 | (chs[ptr+1] & 0xff) << 8 | (chs[ptr+2] & 0xff);
    //printf("x = %x \n", x);
    x = (x & 0x3f) | ((x >> 6) & 0x3f) << 8 | ((x >> 12) & 0x3f) << 16 | ((x >> 18) & 0x3f) << 24;
    //printf("x = %x \n", x);
    //printf("chs = %c %c %c %c \n", base64map[(x >> 24) & 0xff], base64map[(x >> 16) & 0xff ], base64map[(x >> 8) & 0xff], base64map[x & 0xff]);
    res =res + base64map[(x >> 24) & 0xff] + base64map[(x >> 16) & 0xff ] + base64map[(x >> 8) & 0xff] + base64map[x & 0xff];
    }else if(ptr == len - 2){
        unsigned int x = (chs[ptr] & 0xff) << 8 | (chs[ptr+1] & 0xff);
        x = (x & 0xf) << 2 | ( (x >> 4) & 0x3f) << 8 | ((x >> 10) & 0x3f) << 16;
        //printf("x = %x \n", x);
        res =res + base64map[(x >> 16) & 0xff] + base64map[(x >> 8) & 0xff] + base64map[x & 0xff] + "=";
    }else{
        unsigned int x = (chs[ptr] & 0xff);
        x = (x & 0x3)<<4 | ((x >> 2) & 0x3f) << 8;
        res = res + base64map[(x>>8) & 0xff] + base64map[x & 0xff] + "==";
    }
    
    return res;
}

int main(){
    vector<char> chs;
    char ch;
    while(cin.get(ch)){
        chs.push_back(ch);
    }
    int ptr = 0;
    int len = chs.size();
    string res = "";
    while(ptr < len){
        res += base64encoder(chs, ptr);
        ptr += 3;
    }
    cout << res;
    
    return 0;
}