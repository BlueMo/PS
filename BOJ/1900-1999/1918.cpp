#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

string str, ans;
char stack[102], tail;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> str;
    for (auto ch : str){
        if (ch >= 'A' && ch <= 'Z'){
            ans += ch;
        }
        else if (ch == '('){
            stack[tail++] = ch;
        }
        else if (ch == ')'){
            while (tail > 0 && stack[tail - 1] != '('){
                ans += stack[--tail];
            }
            tail--;
        }
        else if (ch == '*' || ch == '/'){
            if (tail > 0 && (stack[tail - 1] == '*' || stack[tail - 1] == '/')){
                ans += stack[--tail];
            }
            stack[tail++] = ch;
        }
        else{
            while (tail > 0 && stack[tail - 1] != '('){
                ans += stack[--tail];
            }
            stack[tail++] = ch;
        }
    }
    while (tail > 0){
        ans += stack[--tail];
    }
    cout << ans;
    return 0;
}