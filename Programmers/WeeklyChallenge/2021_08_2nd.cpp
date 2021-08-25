#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string solution(vector<vector<int>> scores) {
    string answer = "";
    size_t N = scores.size();
    
    for (int i = 0; i < N; i++){
        double sum = 0.0;
        int max_score = 0, min_score = 200;
        bool flag = 0;
        for (int j = 0; j < N; j++){
            if (j != i && scores[j][i] == scores[i][i]) flag = 1;
            sum += scores[j][i];
            max_score = max(max_score, scores[j][i]);
            min_score = min(min_score, scores[j][i]);
        }
        if (!flag && (scores[i][i] == max_score || scores[i][i] == min_score)){
            sum -= scores[i][i];
            sum /= N-1;
        }
        else sum /= N;
        
        if (sum >= 90.0) answer += "A";
        else if (sum >= 80.0) answer += "B";
        else if (sum >= 70.0) answer += "C";
        else if (sum >= 50.0) answer += "D";
        else answer += "F";
    }
    return answer;
}

int main(){
    return 0;
}