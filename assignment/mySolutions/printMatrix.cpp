#include <iostream>
#include <cstring>

using namespace std;

const int N = 110;

int matrix[N][N];
bool visited[N][N];

int dx[4] = {0 , 1, 0, -1}, dy[4] = {1, 0, -1, 0};

int main(){
    int n, m;
    cin >> m >> n;
    memset(visited, true, sizeof visited);
    for(int i = 1; i <= m; i ++)
        for(int j = 1; j <= n; j ++){
            cin >> matrix[i][j];
            visited[i][j] = false;
        }
    int count = m * n;
    int x = 1, y = 1;
    int dir = 0;
    while(count--){
        cout << matrix[x][y] << " ";
        visited[x][y] = true;
        x += dx[dir];
        y += dy[dir];
        if(visited[x][y]){
            x -= dx[dir];
            y -= dy[dir];
            dir = (dir + 1) % 4;
            x += dx[dir];
            y += dy[dir];
        }
    }
    
    return 0;
}