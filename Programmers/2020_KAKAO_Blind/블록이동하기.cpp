#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <iostream>
using namespace std;
typedef tuple<int, int, int, int> tiii;

int solution(vector<vector<int>> board) {
    int answer = 0, n = board.size();
    vector<vector<vector<bool>>> chk(n, vector<vector<bool>>(n, vector<bool>(2, false)));
    queue<tiii> q;
    q.push({0, 1, 0, 0});
    while (!q.empty()){
        auto [y, x, cost, rtype] = q.front(); q.pop();
        if (y == n-1 && x == n-1){
            answer = cost;
            break;
        }
        if (rtype){     // col
            if (x > 0 && !board[y][x-1] && !board[y-1][x-1]){
                if (!chk[y][x-1][1]){
                    q.push({y, x-1, cost+1, 1});
                    chk[y][x-1][1] = 1;
                }
                if (!chk[y][x][0]){
                    q.push({y, x, cost+1, 0});
                    chk[y][x][0] = 1;
                }
                if (!chk[y-1][x][0]){
                    q.push({y-1, x, cost+1, 0});
                    chk[y-1][x][0] = 1;
                }
            }
            if (x < n-1 && !board[y][x+1] && !board[y-1][x+1]){
                if (!chk[y][x+1][1]){
                    q.push({y, x+1, cost+1, 1});
                    chk[y][x+1][1] = 1;
                }
                if (!chk[y][x+1][0]){
                    q.push({y, x+1, cost+1, 0});
                    chk[y][x+1][0];
                }
                if (!chk[y-1][x+1][0]){
                    q.push({y-1, x+1, cost+1, 0});
                    chk[y-1][x+1][0] = 1;
                }
            }
            if (y > 1 && !board[y-2][x] && !chk[y-1][x][1]){
                q.push({y-1, x, cost+1, 1});
                chk[y-1][x][1] = 1;
            }
            if (y < n-1 && !board[y+1][x] && !chk[y+1][x][1]){
                q.push({y+1, x, cost+1, 1});
                chk[y+1][x][1] = 1;
            } 
        }
        else{           // row
            if (x > 1 && !board[y][x-2] && !chk[y][x-1][0]){
                q.push({y, x-1, cost+1, 0});
                chk[y][x-1][0] = 1;
            }
            if (x < n-1 && !board[y][x+1] && !chk[y][x+1][0]){
                q.push({y, x+1, cost+1, 0});
                chk[y][x+1][0] = 1;
            }
            if (y > 0 && !board[y-1][x] && !board[y-1][x-1]){
                if (!chk[y-1][x][0]){
                    q.push({y-1, x, cost+1, 0});
                    chk[y-1][x][0] = 1;
                }
                if (!chk[y][x][1]){
                    q.push({y, x, cost+1, 1});
                    chk[y][x][1] = 1;
                }
                if (!chk[y][x-1][1]){
                    q.push({y, x-1, cost+1, 1});
                    chk[y][x-1][1] = 1;
                }
            }
            if (y < n-1 && !board[y+1][x] && !board[y+1][x-1]){
                if (!chk[y+1][x][0]){
                    q.push({y+1, x, cost+1, 0});
                    chk[y+1][x][0] = 1;
                }
                if (!chk[y+1][x][1]){
                    q.push({y+1, x, cost+1, 1});
                    chk[y+1][x][1] = 1;
                }
                if (!chk[y+1][x-1][1]){
                    q.push({y+1, x-1, cost+1, 1});
                    chk[y+1][x-1][1] = 1;
                }
            }
        }
    }
    return answer;
}
int main(){ return 0; }