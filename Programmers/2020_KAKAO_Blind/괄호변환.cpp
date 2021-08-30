#include <string>
#include <vector>
using namespace std;

bool is_correct(string s){
    int cnt = 0;
    for (auto c : s){
        if (c == '(') cnt++;
        else{
            if (cnt == 0) return false;
            cnt--;
        }
    }
    return true;
}

string solution(string p) {
    string answer = "";
    if (p == "") return "";
    
    int cnt = 1;
    char c = p[0];
    for (int i = 1; i < p.size(); i++){
        if (c != p[i]){
            cnt--;
            if (cnt == 0){
                string u = p.substr(0, i+1);
                string v = p.substr(i+1, p.size()-i-1);
                if (is_correct(u)){
                    answer += u;
                    answer += solution(v);
                }
                else{
                    answer += '(';
                    answer += solution(v);
                    answer += ')';
                    for (int j = 1; j < u.size()-1; j++){
                        if (u[j] == '(') answer += ')';
                        else answer += '(';
                    }
                }
                break;
            }
        }
        else cnt++;
    }
    return answer;
}
int main(){
    return 0;
}