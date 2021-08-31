#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

struct Trie{
    Trie *c[26];
    int cnt;
    
    Trie(){
        this->cnt = 0;
        for (int i = 0; i < 26; i++) this->c[i] = NULL;
    }
};
vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;
    Trie *prefix[10002], *suffix[10002];
    Trie *pre, *suf;
    for (auto w : words){
        int l = w.size();
        if (prefix[l] == NULL || suffix[l] == NULL){
            prefix[l] = new Trie();
            suffix[l] = new Trie();
        }
        pre = prefix[l], suf = suffix[l];
        pre->cnt++;
        suf->cnt++;
        
        for (int i = 0; i < l; i++){
            if (pre->c[w[i]-'a'] == NULL) pre->c[w[i]-'a'] = new Trie();
            if (suf->c[w[l-i-1]-'a'] == NULL) suf->c[w[l-i-1]-'a'] = new Trie();
            pre = pre->c[w[i]-'a'];
            suf = suf->c[w[l-i-1]-'a'];
            pre->cnt++;
            suf->cnt++;
        }
    }
    for (auto q : queries){
        int l = q.size();
        if (prefix[l] == NULL) answer.push_back(0);
        else if (q[0] == '?' && q[l-1] == '?') answer.push_back(prefix[l]->cnt);
        else if (q[0] != '?'){
            Trie *pre = prefix[l];
            for (int i = 0; i < l && q[i] != '?' && pre != NULL; i++){
                pre = pre->c[q[i]-'a'];
            }
            if (pre != NULL) answer.push_back(pre->cnt);
            else answer.push_back(0);
        }
        else{
            Trie *suf = suffix[l];
            for (int i = q.size()-1; i >= 0 && q[i] != '?' && suf != NULL; i--){
                suf = suf->c[q[i]-'a'];
            }
            if (suf != NULL) answer.push_back(suf->cnt);   
            else answer.push_back(0);
        }
    }
    return answer;
}
int main(){
    return 0;
}