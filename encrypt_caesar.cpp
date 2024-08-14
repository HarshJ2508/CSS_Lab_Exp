#include <bits/stdc++.h>
using namespace std;

const int secretKey = 5; 
const int size = 26;

int main() {
    
    vector<string> plainText; 
    int cnt; cin >> cnt;

    for(int i = 0; i < cnt; i++) {
        string str; cin >> str; plainText.push_back(str);
    }
    cout << "Plain Text: ";
    for(auto &i : plainText) cout << i << " ";

    cout << endl;

    string cipherText = "";
    
    for(auto &p : plainText) {
        for(int j = 0; j < p.size(); j++) {
            cipherText += (char)(((int)p[j] - 'a' + secretKey) % 26 + 'a');
        }
        cipherText += " ";
    }

    cout << "Cipher Text: " << cipherText << endl;

    return 0;
}