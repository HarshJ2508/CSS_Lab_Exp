#include <bits/stdc++.h>
using namespace std;

const int rows = 4;
const int cols = 4;

int main() {
    vector<string> plainText; 
    int cnt; cout << "Enter count of words in plain text: "; cin >> cnt; cout << cnt << endl;
    string plainTextNoSpace = "";

    for(int i = 0; i < cnt; i++) {
        string str; cin >> str; plainText.push_back(str);
        plainTextNoSpace += str;
    }

    cout << "Plain text entered: ";
    for(auto &i : plainText) cout << i << " ";

    cout << endl;
    
    vector<int> key;
    cout << "Enter length of key: "; cin >> cnt; cout << cnt << endl;

    for(int i = 0; i < cnt; i++) {
        int d; cin >> d; key.push_back(d);
    }
    cout << "Key entered: ";
    for(auto &i : key) cout << i << " ";

    cout << endl << endl;

    vector<vector<char>> matrix(rows, vector<char> (cols, '#'));
    int r = 0, c = 0;
    for(int i = 0; i < plainTextNoSpace.size(); i++) {
        matrix[r][c] = plainTextNoSpace[i];
        // cout << r << " " << c << endl;
        c = (c + 1) % cols;
        if(c == 0) r++; 
        if(r == rows) break;
    }

    int rem = rows * cols - plainTextNoSpace.size();
    if(rem > 0 and rem <= 26) {
        int ch = 122;
        r = rows - 1; c = cols - 1;
        for(int i = rem; i > 0; i--) {
            matrix[r][c] = (char)ch;
            ch--;
            c--; 
            if(c < 0) {
                c = cols - 1;
                r--;
            }
        }
    }
    else if(rem < 0 or rem > 26) {
        cout << "Plain text too large!\nEither decrease plainText size or increase no. of rows and columns\n";
        return 0;
    }

    cout << "Matrix generated: \n";

    for(auto &i : matrix) {
        for(auto &j : i) cout << j << " ";
        cout << endl;
    }

    cout << endl;

    string cipherText = "";
    map<int, string> mp;
    c = 0;
    for(auto &i : key) {
        string res = "";
        for(r = 0; r < rows; r++) {
            res += matrix[r][c];
        }
        mp[i] = res;
        c++;
    }

    cout << "Cipher text generated: ";
    for(auto &i : mp) {
        cout << i.second;
    }

    return 0;
}

/*
5
Kill Z at five pm
4
4 1 3 2
*/

/*
Enter count of words in plain text: 5
Plain text entered: Kill Z at five pm 
Enter length of key: 4
Key entered: 4 1 3 2 

Matrix generated: 
K i l l 
Z a t f 
i v e p 
m x y z 

Cipher text generated: iavxlfpzlteyKZim
*/



