#include <string>
#include <vector>

using namespace std;

vector<vector<int>> rotate_key(vector<vector<int>> key){
    int m = key.size();
    vector<vector<int>> ret(m, vector<int>(m, 0));
    
    for (int i = 0; i < m; i++){
        for (int j = 0; j < m; j++){
            ret[j][m - i - 1] = key[i][j];
        }
    }
    return ret;
}

bool is_correct(int dy, int dx, vector<vector<int>> key, vector<vector<int>> lock){
    int n = lock.size(), m = key.size();
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            int y = i + dy, x = j + dx;
            if (y < 0 || x < 0 || y >= m || x >= m){
                if (lock[i][j] == 0) return false;
                continue;
            }
            if ((key[y][x]^lock[i][j]) == 0) return false;
        }
    }
    return true;
}
bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    bool answer = false;
    int m = key.size(), n = lock.size();
    
    for (int i = 0; i < 4; i++){
        for (int dy = -n+1; dy < m; dy++){
            for (int dx = -n+1; dx < m; dx++){
                if (is_correct(dy, dx, key, lock) == true) return true;
            }
        }
        
        key = rotate_key(key);
    }
    return answer;
}
int main(){
    return 0;
}