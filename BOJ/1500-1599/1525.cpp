#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>
using namespace std;

string s = "123456789";
unordered_map<string, int> chk;
queue<pair<string, int>> q;
int idx;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    for (int i = 0; i < 9; ++i){
        cin >> s[i];
        if (s[i] == '0') idx = i;
    }
    q.push({s, idx});
    chk[s] = 1;

    while (!q.empty()){
        pair<string, int> h = q.front();
        q.pop();
        if (h.first == "123456780"){
            cout << chk[h.first] - 1;
            return 0;
        }

        int x = h.second % 3, y = h.second / 3;
        for (int i = 0; i < 4; ++i){
            int nx = x + "2011"[i] - '1';
            int ny = y + "1102"[i] - '1';
            if (nx < 0 || ny < 0 || nx >= 3 || ny >= 3) continue;
            string next = h.first;
            swap(next[ny * 3 + nx], next[h.second]);
            if (!chk[next]){
                chk[next] = chk[h.first] + 1;
                q.push({next, ny * 3 + nx});
            }
        }
    }

    cout << -1;
    return 0;
}