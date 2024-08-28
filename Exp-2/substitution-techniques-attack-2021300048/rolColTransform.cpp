#include <bits/stdc++.h>
using namespace std;

const int rows = 4;
const int cols = 4;
const int keyLen = 4;

void findPermutations(string &str, int l, int r, vector<vector<char>> &matrix) { 
    if(l == r) {
        vector<int> decodeKey;
        for(auto &i : str) {
            decodeKey.push_back(i - 'a');
        }
        
        cout << "Trying For key - ";
        for(auto &i : decodeKey) cout << i + 1 << " ";

        cout << ", Plain Text: ";

        string plainText = "";
        for(int i = 0; i < keyLen; i++) {
            for(int j = 0; j < keyLen; j++) {
                plainText += matrix[decodeKey[j]][i];
            }
        }

        cout << plainText << endl;

        return;
    } 
    
    for(int i = l; i <= r; i++) { 
        swap(str[l], str[i]); 

        findPermutations(str, l + 1, r, matrix); 

        swap(str[l], str[i]); 
    } 
    
} 
  

int main() {
    string str = "";
    for(int i = 0; i < keyLen; i++) {
        str += char(i + 'a');
    }

    cout << "Enter Cipher Text: ";
    string ct;
    cin >> ct; cout << ct << endl; 

    int r = 0, c = 0, idx = 0;    
    vector<vector<char>> matrix(keyLen, vector<char>(keyLen));
    for(int i = 0; i < keyLen; i++) {
        for(int j = 0; j < keyLen; j++) {
            matrix[i][j] = ct[idx++];
            if(idx == ct.size()) break;
        }
        if(idx == ct.size()) break;
    } 

    // for(auto &i : matrix) {
    //     for(auto &j : i) {
    //         cout << j << " " ;
    //     }
    //     cout << endl;
    // }


    findPermutations(str, 0, keyLen - 1, matrix);


    return 0;
}


// iavxlfpzlteyKZim

/*
Enter Cipher Text: iavxlfpzlteyKZim
Trying For key - 1 2 3 4 , Plain Text: illKaftZvpeixzym
Trying For key - 1 2 4 3 , Plain Text: ilKlafZtvpiexzmy
Trying For key - 1 3 2 4 , Plain Text: illKatfZvepixyzm
Trying For key - 1 3 4 2 , Plain Text: ilKlatZfveipxymz
Trying For key - 1 4 3 2 , Plain Text: iKllaZtfviepxmyz
Trying For key - 1 4 2 3 , Plain Text: iKllaZftvipexmzy
Trying For key - 2 1 3 4 , Plain Text: lilKfatZpveizxym
Trying For key - 2 1 4 3 , Plain Text: liKlfaZtpviezxmy
Trying For key - 2 3 1 4 , Plain Text: lliKftaZpevizyxm
Trying For key - 2 3 4 1 , Plain Text: llKiftZapeivzymx
Trying For key - 2 4 3 1 , Plain Text: lKlifZtapievzmyx
Trying For key - 2 4 1 3 , Plain Text: lKilfZatpivezmxy
Trying For key - 3 2 1 4 , Plain Text: lliKtfaZepviyzxm
Trying For key - 3 2 4 1 , Plain Text: llKitfZaepivyzmx
Trying For key - 3 1 2 4 , Plain Text: lilKtafZevpiyxzm
Trying For key - 3 1 4 2 , Plain Text: liKltaZfevipyxmz
Trying For key - 3 4 1 2 , Plain Text: lKiltZafeivpymxz
Trying For key - 3 4 2 1 , Plain Text: lKlitZfaeipvymzx
Trying For key - 4 2 3 1 , Plain Text: KlliZftaipevmzyx
Trying For key - 4 2 1 3 , Plain Text: KlilZfatipvemzxy
Trying For key - 4 3 2 1 , Plain Text: KlliZtfaiepvmyzx
Trying For key - 4 3 1 2 , Plain Text: KlilZtafievpmyxz
Trying For key - 4 1 3 2 , Plain Text: KillZatfivepmxyz
Trying For key - 4 1 2 3 , Plain Text: KillZaftivpemxzy
*/