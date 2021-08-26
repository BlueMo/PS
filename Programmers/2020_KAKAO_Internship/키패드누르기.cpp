#include <string>
#include <vector>
using namespace std;

string solution(vector<int> numbers, string hand) {
    string answer = "";
    int l = 9, r = 11;
    for (auto n : numbers){
        n--;
        if (n == -1) n = 10;
        if (n%3 == 0){
            l = n;
            answer += "L";
        }
        else if (n%3 == 2){
            r = n;
            answer += "R";
        }
        else{
            int dist_l = abs(l/3 - n/3) + abs(l%3 - n%3);
            int dist_r = abs(r/3 - n/3) + abs(r%3 - n%3);
            bool flag = 0;
            if (dist_l > dist_r) flag = 1;
            else if (dist_l == dist_r && hand[0] == 'r') flag = 1;
            
            if (flag){
                answer += "R";
                if (!n) r = 10;
                else r = n;
            }
            else{
                answer += "L";
                if (!n) l = 10;
                else l = n;
            }
        }
    }
    return answer;
}
int main(){
    return 0;
}