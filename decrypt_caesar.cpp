#include <bits/stdc++.h>
using namespace std;


int main() {
    // mjqqt btwqi
    vector<string> cipherText; 
    int cnt; cin >> cnt;

    for(int i = 0; i < cnt; i++) {
        string str; cin >> str; cipherText.push_back(str);
    }
    cout << "Cipher Text: ";
    for(auto &i : cipherText) cout << i << " ";

    cout << endl;

    // brute force 
    for(int secretKey = 1; secretKey <= 26; secretKey++) {
        string plainText = "";
        for(auto &c : cipherText) {
            for(int l = 0; l < c.size(); l++) {
                int d = (int)c[l] - 'a' - (secretKey);
                if(d < 0) d += 26;
                plainText += (char)((d) % 26 + 'a');
            }
            plainText += " ";
        }
        
        cout << "For key: " << secretKey << "\tPlain Text: " << plainText << endl;
    } 
    return 0;
}