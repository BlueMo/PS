#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

/*  ASCII Code
    0: 48
    A: 65
    a: 97   */

vector<string> split(string str, string delimiter){
    size_t prev = 0, pos, delimiter_size = delimiter.size();
    vector<string> ret;
    while ((pos = str.find(delimiter, prev)) != string::npos){
        ret.push_back(str.substr(prev, pos - prev));
        prev = pos + delimiter_size;
    }
    ret.push_back(str.substr(prev, str.size() - prev + 1));
    return ret;
}

string eraseAll(string str, string target){
    size_t pos, target_size = target.size();
    while ((pos = str.find(target)) != string::npos) str.erase(pos, target_size);
    return str;
}

string replaceAll(string str, string a, string b){      // a -> b
    size_t pos, a_size = a.size();
    while ((pos = str.find(a)) != string::npos) str.replace(pos, a_size, b);
    return str;
}
int main(){
    string str ="pizza and chicken and coke";
    
    // split
    vector<string> split_s = split(str, " and ");
    cout << "====== split =========\n";
    for (auto s : split_s) cout << s << endl;

    // erase 
    string str1 = str, str2 = str, str3 = str, str4 = str, str5;
    string::iterator it = str2.begin(), it2 = str4.begin();
    it+=2;
    str5 = str1.erase(3);       // delete 3 ~ end
    str2.erase(it);             // delete only 3
    str3.erase(3, 2);           // delete 3, 4 (2)
    str4.erase(it2, it2+3);     // delete [it2, it2+3)
    cout << "====== erase ========\n";
    cout << str1 << endl << str2 << endl << str3 << endl << str4 << endl << str5 << endl;

    // erase specific pattern (all)
    string erase_str = str;
    cout << eraseAll(erase_str, " and") << endl;

    // replace specific pattern (all)
    string replace_str = str;
    cout << replaceAll(str, " and", " /") << endl;

    // find (string, size_t) : size_t ~ find string value
    size_t pos = str.find("and");       
    size_t pos2 = str.find("kk");
    size_t pos3 = str.find("and", 10);  
    cout << pos << endl;
    if (pos2 == string::npos) cout << -1 << endl;
    cout << pos3 << endl;
    return 0;
}