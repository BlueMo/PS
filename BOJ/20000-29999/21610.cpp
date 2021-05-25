#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

struct P{
    int y, x;
};
int N, M, d, s, MAP[51][51], ans;
int dx[]={-1,-1,0,1,1,1,0,-1}, dy[]={0,-1,-1,-1,0,1,1,1};
int dx2[]={-1,-1,1,1}, dy2[]={-1,1,-1,1};
bool chk[51][51];
vector<P> cloud;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            cin >> MAP[i][j];
        }
    }
    cloud.push_back({N-1, 0});
    cloud.push_back({N-1, 1});
    cloud.push_back({N-2, 0});
    cloud.push_back({N-2, 1});

    while (M--){
        cin >> d >> s;
        d--;
        memset(chk, 0, sizeof(chk));
        // move cloud
        for (auto &i : cloud){
            i.x = (i.x + s*dx[d] + 51*N) % N;
            i.y = (i.y + s*dy[d] + 51*N) % N;
            chk[i.y][i.x] = 1;
            MAP[i.y][i.x]++;
        }
        // copy water
        for (auto &i : cloud){
            for (int j = 0; j < 4; ++j){
                int x = i.x + dx2[j], y = i.y + dy2[j];
                if (x < 0 || y < 0 || x == N || y == N) continue;
                if (MAP[y][x]) MAP[i.y][i.x]++;
            }
        }
        cloud.clear();
        // make new cloud
        for (int i = 0; i < N; ++i){
            for (int j = 0; j < N; ++j){
                if (chk[i][j] || MAP[i][j] < 2) continue;
                cloud.push_back({i, j});
                MAP[i][j] -= 2;
            }
        }
    }

    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            ans += MAP[i][j];
        }
    }
    cout << ans;

    return 0;
}