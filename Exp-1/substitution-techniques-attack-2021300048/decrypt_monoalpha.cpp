#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<string> cipherText; 
    int cnt; cin >> cnt;

    for(int i = 0; i < cnt; i++) {
        string str; cin >> str; cipherText.push_back(str);
    }
    cout << "Cipher Text: ";
    for(auto &i : cipherText) cout << i << " ";

    cout << endl;

    map<char, char> mp;
    mp['p'] = 'a';
    mp['h'] = 'b';
    mp['q'] = 'c';
    mp['g'] = 'd';
    mp['u'] = 'e';
    mp['m'] = 'f';
    mp['e'] = 'g';
    mp['a'] = 'h';
    mp['y'] = 'i';
    mp['l'] = 'j';
    mp['n'] = 'k';
    mp['f'] = 'l';
    mp['d'] = 'm';
    mp['x'] = 'n';
    mp['i'] = 'o';
    mp['r'] = 'p';
    mp['c'] = 'q';
    mp['v'] = 'r';
    mp['s'] = 's';
    mp['b'] = 't';
    mp['w'] = 'u';
    mp['k'] = 'v';
    mp['o'] = 'w';
    mp['z'] = 'x';
    mp['t'] = 'y';
    mp['j'] = 'z';


    string plainText = "";
    for(auto &c : cipherText) {
        for(int l = 0; l < c.size(); l++) {
            plainText += mp[c[l]];
        }
        plainText += " ";
    }
    
    cout << "Plain Text: " << plainText << endl;


}