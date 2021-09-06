#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
typedef tuple<double, int, int, int> tdiii;
vector<int> solution(vector<int> weights, vector<string> head2head) {
    int n = weights.size();
    vector<int> answer(n);
    vector<tdiii> vec(n);
    
    for (int i = 0; i < n; i++){
        int num_heavy = 0, num_game = 0, num_win = 0;
        double avg;
        for (int j = 0; j < n; j++){
            if (head2head[i][j] != 'N') num_game++;
            if (head2head[i][j] == 'W'){
                num_win++;
                if (weights[i] < weights[j]) num_heavy++;
            }
        }
        if (!num_game) avg = 0.0;
        else avg = double(num_win) / num_game;
        vec[i] = {-avg, -num_heavy, -weights[i], i+1};
    }
    sort(vec.begin(), vec.end());
    for (int i = 0; i < n; i++) answer[i] = get<3>(vec[i]);
    return answer;
}
int main(){ return 0; }