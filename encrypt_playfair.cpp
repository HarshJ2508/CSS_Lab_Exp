#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<string> plainText; 
    int cnt; cin >> cnt;

    for(int i = 0; i < cnt; i++) {
        string str; cin >> str; plainText.push_back(str);
    }
    cout << "Plain Text: ";
    for(auto &i : plainText) cout << i << " ";

    cout << endl;

    
}