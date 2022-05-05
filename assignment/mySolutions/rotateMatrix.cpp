#include <iostream>

using namespace std;

const int N = 1010;

int matrix[N][N];
typedef pair<int, int> pii;
struct st{
    pii origin;
    pii dir;
    int ud;
};
struct st get(int rotatedArc, int n){
    rotatedArc = rotatedArc % 360;
    if(rotatedArc == 0){
        return {{1, 1}, {0, 1}, 1};
    }else if(rotatedArc == 90){
        return {{n, 1}, {-1, 0}, 1};
    }else if(rotatedArc == 180){
        return {{n, n}, {0, -1}, -1};
    }else{
        return {{1, n}, {1, 0}, -1};
    }
}

int main(){
    int rotatedArc, n;
    cin >> n >> rotatedArc;
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            cin >> matrix[i][j];
    struct st s = get(rotatedArc, n);
    int x = s.origin.first, y = s.origin.second;
    int dx = s.dir.first, dy = s.dir.second;
    int ud = s.ud;
    int count = n * n;
    for(int i = 1; i <= count; i ++){
        cout << matrix[x][y] << " ";
        if(i % n == 0){
            putchar('\n');
        }
        x += dx, y += dy;
        if(x == 0 || x == n+1){
            x = s.origin.first;
            y += ud;
        }
        if(y == 0 || y == n+1){
            y = s.origin.second;
            x += ud;
        }
    }
    
    return 0;
}