#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;
vector<vector<string>> r;
vector<int> vec;
vector<string> ans;
int n, m;

void comb(vector<string> str, int k, string key){
    vector<string> newStr(n);
    
    for (int i = k+1; i < vec.size(); i++){
        unordered_set<string> hash;
        bool flag = 0;
        for (int j = 0; j < n; j++){
            newStr[j] = str[j] + " " + r[j][vec[i]];
            if (hash.find(newStr[j]) == hash.end()) hash.insert(newStr[j]);
            else flag = 1;
        }
        if (flag) comb(newStr, i, key + to_string(vec[i]));
        else ans.push_back(key + to_string(vec[i]));
    }
}

int solution(vector<vector<string>> relation) {
    int answer = 0;
    n = relation.size(), m = relation[0].size();
    r = relation;
    for (int i = 0; i < m; i++){
        unordered_set<string> hash;
        bool flag = 0;
        for (int j = 0; j < n; j++){
            if (hash.find(relation[j][i]) == hash.end()) hash.insert(relation[j][i]);
            else{
                flag = 1;
                vec.push_back(i);
                break;
            }
        }
        if (!flag) answer++;
    }
    for (int i = 0; i < vec.size(); i++){
        vector<string> s;
        for (int j = 0; j < n; j++) s.push_back(r[j][vec[i]]);
        comb(s, i, to_string(vec[i]));
    }
    
    for (int i = 0; i < ans.size(); i++){
        bool flag = 0;
        for (int j = 0; j < ans.size(); j++){
            if (i == j || ans[i].size() <= ans[j].size()) continue;
            bool flag2 = 0;
            for (auto s : ans[j]){
                if (ans[i].find(s) == string::npos){
                    flag2 = 1;
                    break;
                }
            }
            if (!flag2){
                flag = 1;
                break;
            }
        }
        if (!flag) answer++;
    }
    return answer;
}

int main(){
    return 0;
}