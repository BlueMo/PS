#include <iostream>
#include <algorithm>
#include <list>
#include <cstring>
#include <fstream>
using namespace std;

struct P{
    int y, x;
};
int N, M, d, s, MAP[50][50], x, y, dx, dy, ans;
P idx[50*50];
list <int> lst;
list <int>::iterator it;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            cin >> MAP[i][j];
        }
    }

    // setting snake pattern
    x = N/2, y = N/2;
    for (int i = 0, j = 1, d = 0; i < N*N; ){
        for (int k = j; k > 0; --k){
            idx[i++] = {y, x};
            x += "0121"[d] - '1';
            y += "1210"[d] - '1';
        }
        if (d & 1) j++;
        d = (d+1)%4;
    }

    while (M--){
        cin >> d >> s;
        d--;

        // blizzard
        x = N/2, y = N/2;
        dx = "1102"[d] - '1';
        dy = "0211"[d] - '1';
        for (int i = 0; i < s; ++i){
            x += dx, y += dy;
            MAP[y][x] = 0;
        }

        // explosion
        for (int i = 1; i < N*N; ++i){
            if (!MAP[idx[i].y][idx[i].x]) continue;
            lst.push_back(MAP[idx[i].y][idx[i].x]);
        }
        while (1){
            bool flag = 0;
            int cnt = 1;
            it = next(lst.begin());
            while (it != lst.end()){
                if (*prev(it) != *it){
                    if (cnt >= 4){
                        flag = 1;
                        it--;
                        ans += cnt * (*prev(it));
                        while (cnt--){
                            lst.erase(it--);
                        }
                        it++;
                    }
                    cnt = 0;
                }
                cnt++;
                it++;
            }
            if (cnt >= 4){
                flag = 1;
                it--;
                ans += cnt * (*prev(it));
                while (cnt--){
                    lst.erase(it--);
                }
            }
            if (!flag) break;
        }

        // group
        memset(MAP, 0, sizeof(MAP));
        it = lst.begin();
        for (int i = 1, cnt = 1; it != lst.end() && i < N*N; it++){
            if (next(it) == lst.end() || *next(it) != *it){
                MAP[idx[i].y][idx[i].x] = cnt;
                if (i+1 == N*N) break;
                MAP[idx[i+1].y][idx[i+1].x] = *it;
                i+=2;
                cnt = 0;
            }
            cnt++;
        }
        lst.clear();

        /*for (int i = 0; i < N; ++i){
            for (int j = 0; j < N; ++j){
                cout << MAP[i][j] << " ";
            }cout << endl;
        }cout << endl;*/
    }
    
    cout << ans;
    return 0;
}