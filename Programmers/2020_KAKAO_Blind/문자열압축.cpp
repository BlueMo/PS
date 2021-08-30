#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int solution(string s) {
    int answer = s.size();
    
    for (int i = 1; i <= s.size()/2; i++){
        int l = 0, len = 0;
        while (l + i <= s.size()){
            string str = s.substr(l, i);
            int j = l + i, cnt = 1;
            for (; j+i <= s.size(); j+=i){
                if (str == s.substr(j, i)) cnt++;
                else break;
            }
            len += min(i*cnt, i + (int)log10(cnt) + 1);
            l = j;
        }
        if (s.size() % i != 0) len += s.size() % i;
        answer = min(answer, len);
    }
    return answer;
}
int main(){
    return 0;
}