#include <iostream>
#include <algorithm>
using namespace std;

int N, adj[30][2];
char a, b, c;

void preOrder(int p){
    cout << char('A' + p);
    if (adj[p][0] != 0){
        preOrder(adj[p][0]);
    }
    if (adj[p][1] != 0){
        preOrder(adj[p][1]);
    }
}
void inOrder(int p){
    if (adj[p][0] != 0){
        inOrder(adj[p][0]);
    }
    cout << char('A' + p);
    if (adj[p][1] != 0){
        inOrder(adj[p][1]);
    }
}
void postOrder(int p){
    if (adj[p][0] != 0){
        postOrder(adj[p][0]);
    }
    if (adj[p][1] != 0){
        postOrder(adj[p][1]);
    }
    cout << char('A' + p);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> a >> b >> c;
        if (b != '.'){
            adj[a - 'A'][0] = b - 'A';
        }
        if (c != '.'){
            adj[a - 'A'][1] = c - 'A';
        }
    }

    preOrder(0);
    cout << "\n";
    inOrder(0);
    cout << "\n";
    postOrder(0);

    return 0;
}