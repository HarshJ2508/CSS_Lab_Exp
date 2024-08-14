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
    mp['n'] = 'a';
    mp['w'] = 'b';
    mp['l'] = 'c';
    mp['r'] = 'd';
    mp['b'] = 'e';
    mp['m'] = 'f';
    mp['q'] = 'g';
    mp['h'] = 'h';
    mp['c'] = 'i';
    mp['d'] = 'j';
    mp['a'] = 'k';
    mp['z'] = 'l';
    mp['o'] = 'm';
    mp['k'] = 'n';
    mp['y'] = 'o';
    mp['i'] = 'p';
    mp['s'] = 'q';
    mp['x'] = 'r';
    mp['j'] = 's';
    mp['f'] = 't';
    mp['e'] = 'u';
    mp['g'] = 'v';
    mp['p'] = 'w';
    mp['u'] = 'x';
    mp['v'] = 'y';
    mp['t'] = 'z';


    string plainText = "";
    for(auto &c : cipherText) {
        for(int l = 0; l < c.size(); l++) {
            plainText += mp[c[l]];
        }
        plainText += " ";
    }
    
    cout << "Plain Text: " << plainText << endl;


}