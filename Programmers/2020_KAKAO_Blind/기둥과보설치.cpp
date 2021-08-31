// 최적화된 코드는 아님: 시간복잡도를 생각 안해도 되는 문제여서 비효율적이지만 빠르게 코딩할 수 있는 방식으로 함

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool is_possible(int n, int y, int x, int a, vector<vector<bool>> row, vector<vector<bool>> col){
    if (a == 0){    // 기둥
        if (y == 0) return true;     // 바닥 위
        else{
            if (col[y-1][x]) return true;     // 기둥 위
            else if (row[y][x] || (x > 0 && row[y][x-1])) return true;     // 보 위
        }
    }
    else{           // 보
        if (col[y-1][x] || (x != n && col[y-1][x+1])) return true;  // 기둥 위
        else if ((x > 0 && row[y][x-1]) && (x != n && row[y][x+1])) return true;    // 양쪽 보와 연결
    }
    return false;
}
vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    vector<vector<bool>> row(n+1, vector<bool>(n+1, 0)), col(n+1, vector<bool>(n+1, 0));
    
    for (auto p : build_frame){
        int x = p[0], y = p[1], a = p[2], b = p[3];
        if (b == 1){        // 건설
            if (is_possible(n, y, x, a, row, col) == true){
                if (a == 0) col[y][x] = 1;
                else row[y][x] = 1;
            }
        }
        else{
            if (a == 0) col[y][x] = 0;
            else row[y][x] = 0;
            
            bool flag = 0;
            for (int i = 0; i <= n; i++){
                for (int j = 0; j <= n; j++){
                    if (col[i][j]){
                        if (is_possible(n, i, j, 0, row, col) == false){
                            flag = 1; break;
                        }
                    }
                    if (row[i][j]){
                        if (is_possible(n, i, j, 1, row, col) == false){
                            flag = 1; break;
                        }
                    }
                }
                if (flag == 1) break;
            }
            if (flag == 1){
                if (a == 0) col[y][x] = 1;
                else row[y][x] = 1;
            }
        }
    }
    for (int x = 0; x <= n; x++){
        for (int y = 0; y <= n; y++){
            if (col[y][x] == 1){
                vector<int> v(3);
                v[0] = x, v[1] = y, v[2] = 0;
                answer.push_back(v);
            }
            if (row[y][x] == 1){
                vector<int> v(3);
                v[0] = x, v[1] = y, v[2] = 1;
                answer.push_back(v);
            }
        }
    }
    return answer;
}
int main(){
    return 0;
}