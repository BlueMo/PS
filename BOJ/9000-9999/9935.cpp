#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;

#define MAX_SIZE 1000001

string str, str2;
int idx, tail, st[MAX_SIZE];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> str >> str2;

    for (auto c : str){
        if (c != str2[idx]) idx = 0;
        if (c == str2[idx]){
            st[tail++] = idx;
            idx++;
            if (idx == str2.size()){
                tail -= str2.size();
                if(tail > 0 && st[tail - 1] < 48) idx = st[tail - 1] + 1;
                else idx = 0;
            }
        }
        else{
            st[tail++] = (int)c;
        }
    }

    if (tail == 0) cout << "FRULA";
    else{
        for (int i = 0; i < tail; i++){
            if (st[i] < 48) cout << str2[st[i]];
            else cout << (char)st[i];
        }
    }

    return 0;
}