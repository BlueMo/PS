#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int N, M, answer = -1;
vector<string> table;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    table.assign(N, "");
    for (int i = 0; i < N; i++){
        string s;
        cin >> s;
        table[i] = s;
    }

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            int num = table[i][j] - '0';
            int sqrt_num = sqrt(num);
            if (num == sqrt_num * sqrt_num) answer = max(answer, num);
            for (int dy = -N+1; dy < N; dy++){
                for (int dx = -M+1; dx < M; dx++){
                    if (dy == 0 && dx == 0) continue;
                    int y = i + dy, x = j + dx;
                    string s = "";
                    s += table[i][j];
                    while (x >= 0 && y >= 0 && x < M && y < N){
                        s += table[y][x];
                        int num = stoi(s);
                        int sqrt_num = sqrt(num);
                        if (num == sqrt_num * sqrt_num) answer = max(answer, num);
                        y += dy, x += dx;
                    }
                }
            }
        }
    }

    cout << answer;
    return 0;
}