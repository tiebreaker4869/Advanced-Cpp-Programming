#include <iostream>
#include <cstddef>

using namespace std;

void print(int* ans, size_t r, size_t c){
    for(size_t i = 0; i < r; i ++){
        for(size_t j = 0; j < c; j ++){
            cout << *(ans + i*c + j) << " ";
        }
        puts("");
    }
}

int main(){
    size_t n, r1, c1, r2, c2;
    int x;
    cin >> n;
    int* ans = nullptr, *tmp1 = nullptr, *tmp2 = nullptr;
    cin >> r1 >> c1;
    ans = new int[r1 * c1];
    for(size_t i = 0; i < r1; i ++)
        for(size_t j = 0; j < c1; j ++){
            cin >> x;
            ans[i*c1 + j] = x;
        }
    n--;
    while(n--){
        cin >> r2 >> c2;
        tmp1 = new int[r2 * c2];
        tmp2 = new int[r1 * c2];
        for(size_t i = 0; i < r2; i ++)
            for(size_t j = 0; j < c2; j ++){
                cin >> x;
                *(tmp1 + i*c2 + j) = x;
            }
        for(size_t i = 0; i < r1; i ++)
            for(size_t j = 0; j < c2; j ++){
                *(tmp2 + i * c2 + j) = 0;
                for(size_t k = 0; k < c1; k ++){
                    *(tmp2 + i*c2 + j) += *(ans + i*c1 + k) * *(tmp1 + k*c2 + j);
                }
            }
        delete[] ans;
        ans = tmp2;
        delete[] tmp1;
        c1 = c2;
    }
    print(ans, r1, c1);
    
    delete[] ans;
    
    return 0;
}