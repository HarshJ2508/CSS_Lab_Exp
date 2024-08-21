#include <iostream>
#include <vector>

using namespace std;

const string keyword = "deceptive";
const int mod26 = 26;

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

    cout << "Keyword: " << keyword << endl << endl;; 

    string cipherText = "";
    int j = 0;
    for(int i = 0; i < plainTextNoSpace.size(); i++) {
        cipherText += char((plainTextNoSpace[i] - 'a' + keyword[j] - 'a') % mod26 + 'a');
        j = (j + 1) % keyword.size(); 
    }

    cout << "Cipher text: " << cipherText << endl;

    return 0;
}
