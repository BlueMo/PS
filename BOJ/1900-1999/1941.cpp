#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <tuple>
using namespace std;
typedef tuple<int, int, int, int> tiiii;

vector<string> class_map(5, "");
vector<int> chk(25, 0);
int answer;
void choose_student(int idx, int cnt){
    if (cnt == 7){
        int cnt_S = 0;
        bool flag = 0;
        queue<pair<int, int>> q;
        for (int i = 0; i < 25; i++){
            if (chk[i]){
                if (flag == 0){
                    q.push({i/5, i%5});
                    chk[i] = 2;
                    flag = 1;
                }
                if (class_map[i/5][i%5] == 'S') cnt_S++;
            }
        }
        if (cnt_S >= 4){
            while (!q.empty()){
                auto [y, x] = q.front(); q.pop();
                cnt--;
                for (int i = 0; i < 4; i++){
                    int ny = y + "2011"[i] - '1';
                    int nx = x + "1120"[i] - '1';
                    if (ny < 0 || nx < 0 || ny == 5 || nx == 5) continue;
                    int next = ny*5 + nx;
                    if (chk[next] == 1){
                        chk[next] = 2;
                        q.push({ny, nx});
                    }
                }
            }
            if (cnt == 0) answer++;
            for (int i = 0; i < 25; i++) if (chk[i] == 2) chk[i] = 1;
        }
        return;
    }

    for (int i = idx; i < 25; i++){
        chk[i] = 1;
        choose_student(i+1, cnt + 1);
        chk[i] = 0;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    for (int i = 0; i < 5; i++){
        string s;
        cin >> s;
        class_map[i] = s;
    }
    choose_student(0, 0);
    cout << answer;
    return 0;
}