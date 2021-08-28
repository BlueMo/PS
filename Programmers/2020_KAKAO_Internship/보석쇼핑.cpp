#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> solution(vector<string> gems) {
    vector<int> answer(2);
    int n = 0, min_range = 123456;
    unordered_map<string, int> chk;
    
    for (auto s : gems){
        if (!chk.count(s)){
            chk[s] = 0;
            n++;
        }
    }
    int l = 0, r = 0, cnt = 0;
    while (r < gems.size()){
        if (chk[gems[r]] == 0){
            cnt++;
            if (cnt == n && min_range > (r-l+1)){
                min_range = r-l+1;
                answer[0] = l+1;
                answer[1] = r+1;
            }
        }
        chk[gems[r]]++;
        
        while (l <= r && chk[gems[l]] > 1){
            chk[gems[l++]]--;
            if (cnt == n && min_range > (r-l+1)){
                min_range = r-l+1;
                answer[0] = l+1;
                answer[1] = r+1;
            }
        }
        r++;
    }
    return answer;
}
int main(){
    return 0;
}