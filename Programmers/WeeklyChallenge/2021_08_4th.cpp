#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> split(string str, char delimiter){
    size_t prev = 0, pos;
    vector<string> ret;
    while ((pos = str.find(delimiter, prev)) != string::npos){
        ret.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }
    ret.push_back(str.substr(prev, str.size() - prev + 1));
    return ret;
}

string solution(vector<string> table, vector<string> languages, vector<int> preference) {
    vector<string> answer;
    int max_score = 0;
    
    for (auto s : table){
        int score = 0;
        vector<string> split_s = split(s, ' ');
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < languages.size(); j++){
                if (split_s[i+1] == languages[j]){
                    score += preference[j] * (5 - i);
                    break;
                }
            }
        }
        if (score > max_score){
            max_score = score;
            answer.clear();
            answer.push_back(split_s[0]);
        }
        else if (score == max_score) answer.push_back(split_s[0]);
    }
    sort(answer.begin(), answer.end());
    return answer[0];
}

int main(){
    return 0;
}