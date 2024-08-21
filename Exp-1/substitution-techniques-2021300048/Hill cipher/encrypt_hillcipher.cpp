#include <bits/stdc++.h>
using namespace std;


const string key = "gybnqkurp";
const int block = 3;
const int mod26 = 26;

string findCipher(vector<vector<int>> &keyMatrix, string &plainText) {
    vector<vector<int>> plainTextVector(1, vector<int> (block));
    for(int i = 0; i < plainText.size(); i++) {
        plainTextVector[0][i] = plainText[i] - 'a';
    }

    string cipherTextVector = "";
    for(int col = 0; col < block; col++) {
        int sum = 0;
        for(int row = 0; row < block; row++) {
            sum = (sum + plainTextVector[0][row] * keyMatrix[row][col]) % mod26;
        }
        cipherTextVector += char(sum + 'a');
    }

    return cipherTextVector;
}

int main() {
    int cnt;
    cout << "Enter word count in plain text: ";
    cin >> cnt;
    cout << cnt << endl << endl;

    vector<string> plainText;
    string plainTextNoSpace;
    for(int i = 0; i < cnt; i++) {
        string s; cin >> s;
        plainText.push_back(s);
        plainTextNoSpace += s;
    }

    cout << "Plain text entered: ";
    for(auto &i : plainText) cout << i << " ";

    cout << endl << endl;

    cout << "Key: " << key << ", Matrix size: " << block << " X " << block << endl;
    
    cout << endl;

    vector<vector<int>> keyMatrix(block, vector<int>(block));
    int row = 0, col = 0;

    for(auto &k: key) {
        keyMatrix[row][col] = k - 'a';
        col = (col + 1) % block;
        if(col == 0) row++;
    }

    cout << "Key matrix created: \n";
    for(auto &i : keyMatrix) {
        for(auto &j : i) {
            cout << j << " ";
        }
        cout << endl;
    }

    cout << endl;

    int l;
    for(l = 0; l + block - 1 < plainTextNoSpace.size(); l += block) {
        string txt = "";
        for(int p = l; p < l + block; p++) {
            txt += plainTextNoSpace[p];
        }
        string ct = findCipher(keyMatrix, txt);
        cout << "Plain text: " << txt << " Cipher text: " << ct << endl;
    }

    if(l < plainTextNoSpace.size()) {
        string txt = "";
        for(int p = l; p < plainTextNoSpace.size(); p++) {
            txt += plainTextNoSpace[p];
        }
        int len = txt.size();
        for(; len < block; len++) {
            txt += 'x';
        }
        string ct = findCipher(keyMatrix, txt);
        cout << "Plain text: " << txt << " Cipher text: " << ct << endl;
    }

    return 0;
}