#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

long long calc_op(long long a, long long b, char op){
    if (op == '*') return a*b;
    if (op == '+') return a+b;
    return a-b;
}

long long solution(string expression) {
    long long answer = 0;
    vector<long long> num;
    vector<char> op;
    vector<char> order;
    order.push_back('*');
    order.push_back('+');
    order.push_back('-');
    sort(order.begin(), order.end());
    int prev = 0;
    for (int i = 0; i < expression.size(); i++){
        if (expression[i] < '0' || expression[i] > '9'){
            num.push_back(stoi(expression.substr(prev, i - prev)));
            op.push_back(expression[i]);
            prev = i + 1;
        }
    }
    num.push_back(stoi(expression.substr(prev, expression.size() - prev)));
    
    do{
        list<long long> l;
        vector<bool> chk(op.size(), 0);
        list<long long>::iterator idx;
        for (auto i : num) l.push_back(i);
        for (auto x : order){
            idx = l.begin();
            idx++;
            for (int i = 0; i < op.size(); i++){
                if (x == op[i]){
                    chk[i] = 1;
                    long long a = *idx;
                    idx = l.erase(idx);
                    idx--;
                    *idx = calc_op(*idx, a, op[i]);
                    idx++;
                }
                else if (!chk[i]) idx++;
            }
        }
        answer = max(answer, abs(*l.begin()));
    }while(next_permutation(order.begin(), order.end()));
    return answer;
}

int main(){
    string s = "100-200*300-500+20";
    cout << solution(s);
    return 0;
}