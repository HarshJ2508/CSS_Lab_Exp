#include <bits/stdc++.h>
using namespace std;

const string keyword = "moonmission";
const int SIZE = 5;

pair<int, int> findCordinates(vector<vector<char>> &matrix, char ch) {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            if(matrix[i][j] == ch) return {i, j};
        }
    }

    return {-1, -1};
}

int main() {
    vector<string> plainText; 
    int cnt; cin >> cnt;
    string plainTextNoSpace = "";

    for(int i = 0; i < cnt; i++) {
        string str; cin >> str; plainText.push_back(str); plainTextNoSpace += str; 
    }

    cout << "Plain text entered: ";
    for(auto &i : plainText) cout << i << " ";

    cout << endl << endl;

    cout << "Keyword: " << keyword << "\n\n"; 

    vector<vector<char>> matrix(5, vector<char>(5, '#'));
    unordered_set<char> ust;
    int row = 0, col = 0;

    for(auto &i : keyword) {
        if(ust.find(i) == ust.end()) {
            matrix[row][col] = i;
            if((col + 1) % SIZE == 0) row += 1;
            col = (col + 1) % SIZE;
            ust.insert(i);
        }
    }

    for(char ch = 'a'; ch <= 'z'; ch++) {
        if(ust.find(ch) == ust.end()) {
            if((ch == 'i' and ust.find('j') != ust.end()) or (ch == 'j' and ust.find('i') != ust.end())) continue;
            matrix[row][col] = ch;
            if((col + 1) % SIZE == 0) row += 1;
            col = (col + 1) % SIZE;
            ust.insert(ch);
        }
    }

    cout << "Matrix generated:\n";
    for(auto &i : matrix) {
        for(auto &j : i) cout << j << " ";
        cout << endl;
    }

    // cout << plainTextNoSpace << endl;

    vector<string> plainTextGrp;
    int i;
    for(i = 0; i + 1 < plainTextNoSpace.size();) {
        string str = "";
        if(plainTextNoSpace[i] != plainTextNoSpace[i + 1]) {
            // cout << plainTextNoSpace[i] << " " << plainTextNoSpace[i + 1] << endl;
            str += plainTextNoSpace[i]; str += plainTextNoSpace[i + 1];
            i += 2;
        }
        else {
            // cout << plainTextNoSpace[i] << " " << "x" << endl;
            str += plainTextNoSpace[i]; str += "x";
            i += 1;
        }
        // cout << str << endl;
        plainTextGrp.push_back(str); 
    }

    if(i < plainTextNoSpace.size()) {
        string str = "";
        str += plainTextNoSpace[plainTextNoSpace.size() - 1];
        str += "x";
        plainTextGrp.push_back(str);
    }

    cout << "\nPlain text pairs generated: ";
    for(auto &i : plainTextGrp) cout << i << " ";
    cout << endl;

    // Encryption
    vector<string> cipherText;
    for(auto &i : plainTextGrp) {
        string txt = i, encrypt = "";

        pair<int, int> co1 = findCordinates(matrix, txt[0]);
        pair<int, int> co2 = findCordinates(matrix, txt[1]);

        if(co1.first == co2.first) { // same row
            encrypt += matrix[co1.first][(co1.second + 1) % SIZE];
            encrypt += matrix[co1.first][(co2.second + 1) % SIZE];
            if(co2.second < co1.second) reverse(encrypt.begin(), encrypt.end());        
        }
        else if(co1.second == co2.second) { // same col
            encrypt += matrix[(co1.first + 1) % SIZE][co1.second];
            encrypt += matrix[(co2.first + 1) % SIZE][co1.second];
            if(co2.first < co1.first) reverse(encrypt.begin(), encrypt.end());        
        }
        else {
            if(co1.first < co2.first and co1.second < co2.second) {
                // cout << i << " " << co1.first << " " << co1.second << "\t" << co2.first << " " << co2.second << endl;
                encrypt += matrix[co1.first][co2.second];
                encrypt += matrix[co2.first][co1.second]; 
            }   
            else if(co1.first > co2.first and co2.second > co1.second) {
                // cout << i << " " << co1.first << " " << co1.second << "\t" << co2.first << " " << co2.second << endl;;
                encrypt += matrix[co1.first][co2.second]; 
                encrypt += matrix[co2.first][co1.second]; 
            }
            else if(co1.first < co2.first and co1.second > co2.second) {
                encrypt += matrix[co1.first][co2.second];
                encrypt += matrix[co2.first][co1.second]; 
            }
            else {
                encrypt += matrix[co1.first][co2.second];
                encrypt += matrix[co2.first][co1.second];
            }
        }

        cipherText.push_back(encrypt);
    }

    cout << "Cipher text generated: ";
    for(auto &i : cipherText) {
        cout << i << " ";
    }


    return 0;
}