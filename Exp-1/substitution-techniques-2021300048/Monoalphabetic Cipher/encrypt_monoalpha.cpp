#include <bits/stdc++.h>
using namespace std;

const int alphabets = 26;

int findMap(int ch) {
    return rand() % alphabets;
}

int main() {
    vector<string> plainText; 
    int cnt; cout << "Enter count of words in plain text: "; cin >> cnt;

    for(int i = 0; i < cnt; i++) {
        string str; cin >> str; plainText.push_back(str);
    }
    cout << "Plain text entered: ";
    for(auto &i : plainText) cout << i << " ";

    cout << endl;

    vector<bool> isMapped(26, false);
    map<char, char> mp;

    for(int i = 0; i < 26; i++) {
        int mappedVal = findMap(i);
        while(isMapped[ mappedVal ]) {
            mappedVal = findMap(i);
        }
        isMapped[ mappedVal ] = true;
        mp[i + 'a'] = mappedVal + 'a';
    } 

    cout << "Encryption key:" << endl;
    for(auto &i : mp) {
        // cout << i.first << " " << i.second << endl; 
        cout << "mp['" << i.first << "'] = '" << i.second  << "';" << endl;
    }

    cout << "Decryption key:" << endl;
    for(auto &i : mp) {
        // cout << i.first << " " << i.second << endl; 
        cout << "mp['" << i.second << "'] = '" << i.first  << "';" << endl;
    }

    string cipherText = "";
    for(auto &p : plainText) {
        for(int l = 0; l < p.size(); l++) {
            cipherText += mp[p[l]];
        }
        cipherText += " ";
    }

    cout << "Cipher Text: " << cipherText << endl;

    map<char, int> freq;
    int totalLetters = cipherText.size();
    for(int i = 0; i < cipherText.size(); i++) {
        if(cipherText[i] == ' ') continue;
        freq[cipherText[i]]++;
    }

    for(int i = 0; i < alphabets; i++) {
        cout << "For character: " << (char)(i + 'a') << ", Frequence (%): " << ((double)(freq[(char)(i + 'a')] * 100.0) / (cipherText.size()));
        cout << endl;
    }
}