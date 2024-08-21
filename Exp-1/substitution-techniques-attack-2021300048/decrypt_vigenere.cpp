#include <iostream>
#include <vector>

using namespace std;

const string keyword = "deceptive";
const int mod26 = 26;

int main() {
    int cnt;
    cout << "Enter word count in cipher text: ";
    cin >> cnt;
    cout << cnt << endl << endl;

    vector<string> cipherText;
    string cipherTextNoSpace;
    for(int i = 0; i < cnt; i++) {
        string s; cin >> s;
        cipherText.push_back(s);
        cipherTextNoSpace += s;
    }

    cout << "Cipher text entered: ";
    for(auto &i : cipherText) cout << i << " ";

    cout << endl << endl;

    cout << "Keyword: " << keyword << endl << endl;; 

    string plainText = "";
    int j = 0;
    for(int i = 0; i < cipherTextNoSpace.size(); i++) {
        int d = (cipherTextNoSpace[i] - 'a' - (keyword[j] - 'a'));
        if(d < 0) d += mod26;

        plainText += char(d % mod26 + 'a');
        j = (j + 1) % keyword.size(); 
    }

    cout << "Plain text: " << plainText << endl;

    return 0;
}
