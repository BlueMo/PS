#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int L, C;
vector<char> ch;

void solve(int idx, string str, int len){
    if (len == L){
        int cnt = 0;
        for (auto s : str){
            if (s == 'a' || s == 'e' || s == 'i' || s == 'o' || s == 'u') cnt++;
        }
        if (cnt == 0) return;
        if (L - cnt < 2) return;
        cout << str << "\n";
    }
    for (int i = idx + 1; i < ch.size(); i++){
        solve(i, str + ch[i], len + 1);
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> L >> C;
    for (int i = 0; i < C; i++){
        char c; cin >> c;
        ch.push_back(c);
    }
    sort(ch.begin(), ch.end());
    solve(-1, "", 0);
    return 0;
}