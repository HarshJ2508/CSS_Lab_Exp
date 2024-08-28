#include <bits/stdc++.h>
using namespace std;

void findCipher(int s, int e, string plainText, vector<string> &cipherText) {
    int depthLvl = 0;

    cipherText[depthLvl] += plainText[s];
    if(e < plainText.size()) cipherText[depthLvl] += plainText[e];
    
    s++; e--; depthLvl++;

    while(s < e) {
        if(s < plainText.size()) cipherText[depthLvl] += plainText[s];
        if(e < plainText.size()) cipherText[depthLvl] += plainText[e];
        s++;
        e--;
        depthLvl++;
    }

    if(s < plainText.size()) cipherText[depthLvl] += plainText[s];
}

int main() {
    string plainText;
    cin >> plainText;

    cout << "Enter Plain text: " << plainText << endl;

    int depth;
    cout << "Enter depth: ";
    cin >> depth; cout << depth;

    vector<string> cipherText(depth, "");
    for(int i = 0; i < plainText.size(); i += depth * 2 - 2) {
        findCipher(i, i + depth * 2 - 2, plainText, cipherText);
    }

    string ct = "";
    for(int i = 0; i < cipherText.size(); i++){
        if(i == 0) {
            ct += cipherText[i][0];
            for(int j = 1; j < cipherText[i].size(); j += 2) {
                ct += cipherText[i][j];
            }
        }
        else ct += cipherText[i];
    }

    cout << "\nCipher text: " << ct << endl;
    
    return 0;
}


/*
helloworld
3
*/

/*
Enter Plain text: helloworld
Enter depth: 3
Cipher text: holelwrdlo
*/