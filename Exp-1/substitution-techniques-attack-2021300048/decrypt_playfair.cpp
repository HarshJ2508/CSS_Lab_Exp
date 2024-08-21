#include <bits/stdc++.h>
using namespace std;

const string keyword = "occurrence";
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
    vector<string> cipherText;
    int cnt; cin >> cnt;
    for(int i = 0; i < cnt; i++) {
        string str;
        cin >> str;
        cipherText.push_back(str);
    }

    cout << "Cipher text enetered: ";
    for(auto &i : cipherText) {
        cout << i << " ";
    }
    cout << endl;

    vector<vector<char>> matrix;
    char ch;
    for(int i = 0; i < SIZE; i++) {
        vector<char> v;
        for(int j = 0; j < SIZE; j++) {
            cin >> ch;
            v.push_back(ch);
        }
        matrix.push_back(v);
    }

    cout << "Matrix entered: \n";
    for(auto &i : matrix) {
        for(auto &j : i) cout << j << " ";
        cout << endl;
    }

    vector<string> plainText;
    for(auto ct : cipherText) {
        string decrypt = "";

        pair<int, int> co1 = findCordinates(matrix, ct[0]);
        pair<int, int> co2 = findCordinates(matrix, ct[1]);

        if(co1.first == co2.first) {
            if(co1.second == 0) co1.second = SIZE;
            if(co2.second == 0) co2.second = SIZE;
            
            decrypt += matrix[co1.first][(co1.second - 1) % SIZE];
            if(matrix[co1.first][(co2.second - 1) % SIZE] != 'x') decrypt += matrix[co1.first][(co2.second - 1) % SIZE];
            if(co2.second < co1.second) reverse(decrypt.begin(), decrypt.end());   
        }
        else if(co1.second == co2.second) {
            if(co1.first == 0) co1.first = SIZE;
            if(co2.first == 0) co2.first = SIZE;

            decrypt += matrix[(co1.first - 1) % SIZE][co1.second];
            if(matrix[(co2.first - 1) % SIZE][co1.second] != 'x') decrypt += matrix[(co2.first - 1) % SIZE][co1.second];
            if(co2.first < co1.first) reverse(decrypt.begin(), decrypt.end()); 
        }
        else {  
            if(co1.first < co2.first and co1.second < co2.second) {
                decrypt += matrix[co1.first][co2.second];
                if(matrix[co2.first][co1.second] != 'x') decrypt += matrix[co2.first][co1.second];
            }
            else if(co1.first > co2.first and co1.second > co2.second) {
                decrypt += matrix[co2.first][co1.second];
                if(matrix[co1.first][co2.second] != 'x') decrypt += matrix[co1.first][co2.second];
            }
            else if(co1.first < co2.first and co1.second > co2.second) {
                decrypt += matrix[co1.first][co2.second];
                if(matrix[co2.first][co1.second] != 'x') decrypt += matrix[co2.first][co1.second];
            }
            else {
                decrypt += matrix[co1.first][co2.second];
                if(matrix[co2.first][co1.second] != 'x') decrypt += matrix[co2.first][co1.second];
            }
        }

        plainText.push_back(decrypt);
    }

    string plainTextNoSpace = "";
    for(auto &i : plainText) {
        plainTextNoSpace += i;
    }

    cout << "Plain text: " << plainTextNoSpace << endl; 

    return 0;
}