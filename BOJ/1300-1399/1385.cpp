#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct HoneyComb{
    int num, dir[6];
}m[1001001];
int a, b, st, en, v[1001001];
queue<int> q;
vector<int> ans;
bool flag;

void link(int x, int y, int d){
    if (!y) return;
    m[x].dir[d] = y;
    m[y].dir[(d+3)%6] = x;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    cin >> a >> b;
    if (a == b){
        cout << a;
        return 0;
    }
    m[1].num = 1;
    for (int i = 1, cnt = 2; ; ++i){
        for (int j = 0; j < 6; ++j){
            if (!m[i].dir[j]){
                link(i, cnt, j);
                cnt++;
                if (cnt == 1001000) break;
            }
            link(m[i].dir[j], m[i].dir[(j+5)%6], (j+4)%6);
        }
        if (cnt == 1001000) break;
        link(m[i].dir[0], m[i].dir[5], 4);
    }
    if (a == 1) st = 1;
    else if (b == 1) en = 1;
    for (int i = 1, idx = 2, p = 1; ; ++i){
        for (int j = 0; j < 6; ++j){
            int e = (j != 1) ? i : i-1;
            for (int k = 0; k < e; ++k){
                p = m[p].dir[j];
                if (a == idx) st = p;
                else if (b == idx) en = p;
                m[p].num = idx++;
                if (idx > max(a, b)){
                    flag = 1;
                    break;
                }
            }
            if (flag) break;
        }
        if (flag) break;
    }

    q.push(st);
    v[st] = -1;
    while(!q.empty()){
        int h = q.front();
        q.pop();
        if (h == en) break;
        for (int i = 0; i < 6; ++i){
            int p = m[h].dir[i];
            if (v[p] || !m[p].num) continue;
            v[p] = h;
            q.push(p);
        }
    }
    for (int p = en, cnt = 0; p != -1; p = v[p], cnt++) ans.push_back(m[p].num);
    for (int i = ans.size()-1; i >= 0; --i) cout << ans[i] << " ";
    return 0;
}