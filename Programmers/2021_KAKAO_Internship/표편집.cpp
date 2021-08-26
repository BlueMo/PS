#include <string>
#include <vector>
#include <stack>
#include <list>
using namespace std;

struct Node{
    int value;
    Node *prev = nullptr, *next = nullptr;
    Node(int value){ this->value = value; }
};
string solution(int n, int k, vector<string> cmd) {
    string answer = "";
    vector<Node*> l(n);
    Node *head;
    stack<int> st;
    for (int i = 0; i < n; i++) l[i] = new Node(i);
    for (int i = 1; i < n; i++){
        l[i-1]->next = l[i];
        l[i]->prev = l[i-1];
    }
    head = l[0];
    for (auto s : cmd){
        if (s[0] == 'U'){
            int x = stoi(s.substr(2));
            while(x--) k = l[k]->prev->value;
        }
        else if (s[0] == 'D'){
            int x = stoi(s.substr(2));
            while(x--) k = l[k]->next->value;
        }
        else if (s[0] == 'C'){
            st.push(k);
            if (l[k]->prev == nullptr){
                l[k]->next->prev = nullptr;
                k = l[k]->next->value;
                head = l[k];
            }
            else if (l[k]->next == nullptr){
                l[k]->prev->next = nullptr;
                k = l[k]->prev->value;
            }
            else{
                l[k]->prev->next = l[k]->next;
                l[k]->next->prev = l[k]->prev;
                k = l[k]->next->value;
            }
        }
        else{
            int p = st.top(); st.pop();
            if (l[p]->prev) l[p]->prev->next = l[p];
            else head = l[p];
            if (l[p]->next) l[p]->next->prev = l[p];
        }
    }
    for (auto i : l){
        if (i == head){
            answer += "O";
            head = head->next;
        }
        else answer += "X";
    }
    return answer;
}

int main(){
    int n, k;
    vector<string> cmd;

    n = 8;
    k = 2;
    cmd.push_back("D 2");
    cmd.push_back("C");
    cmd.push_back("U 3");
    cmd.push_back("C");
    cmd.push_back("D 4");
    cmd.push_back("C");
    cmd.push_back("U 2");
    cmd.push_back("Z");
    cmd.push_back("Z");

    solution(n, k, cmd);
    return 0;
}