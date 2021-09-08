#include <string>
#include <vector>
#include <unordered_map>
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

vector<string> solution(vector<string> record) {
    vector<string> answer, id;
    unordered_map<string, string> hash;
    
    for (auto s : record){
        vector<string> split_s = split(s, ' ');
        if (split_s[0] == "Enter"){
            answer.push_back("님이 들어왔습니다.");
            id.push_back(split_s[1]);
            hash[split_s[1]] = split_s[2];
        }
        else if (split_s[0] == "Leave"){
            answer.push_back("님이 나갔습니다.");
            id.push_back(split_s[1]);
        }
        else hash[split_s[1]] = split_s[2];
    }
    for (int i = 0; i < answer.size(); i++){
        answer[i] = hash[id[i]] + answer[i];
    }
    return answer;
}
int main(){ return 0; }