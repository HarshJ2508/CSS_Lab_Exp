#include <iostream>
#include <vector>

using namespace std;

const int MOD = 26;
const string key = "gybnqkurp";
const int block = 3;

int determinant(const vector<vector<int>>& matrix) {
    return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
           matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
           matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}

int mod_inverse(int a, int m) {
    for(int x = 1; x < m; x++) {
        if((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}

vector<vector<int>> adjugate(const vector<vector<int>>& matrix) {
    vector<vector<int>> adj(3, vector<int>(3));
    adj[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) % MOD;
    adj[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) % MOD;
    adj[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) % MOD;
    adj[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) % MOD;
    adj[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) % MOD;
    adj[1][2] = (matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2]) % MOD;
    adj[2][0] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) % MOD;
    adj[2][1] = (matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1]) % MOD;
    adj[2][2] = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % MOD;


    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(adj[i][j] < 0) {
                adj[i][j] += MOD;
            }
        }
    }

    return adj;
}

vector<vector<int>> matrix_mod_inverse(const vector<vector<int>>& matrix) {
    int det = determinant(matrix) % MOD;
    if(det < 0) {
        det += MOD;
    }

    int det_inv = mod_inverse(det, MOD);
    if (det_inv == -1) {
        throw runtime_error("Matrix is not invertible");
    }

    vector<vector<int>> adj = adjugate(matrix);
    vector<vector<int>> inverse(3, vector<int>(3));

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            inverse[i][j] = (adj[i][j] * det_inv) % MOD;
            if(inverse[i][j] < 0) {
                inverse[i][j] += MOD;
            }
        }
    }

    return inverse;
}

string findPlain(vector<vector<int>> &matrix, string &cipherText) {
    vector<vector<int>> cipherTextVector(1, vector<int> (block));
    for(int i = 0; i < cipherText.size(); i++) {
        cipherTextVector[0][i] = cipherText[i] - 'a';
    }

    string plainTextVector = "";
    for(int col = 0; col < block; col++) {
        int sum = 0;
        for(int row = 0; row < block; row++) {
            sum = (sum + cipherTextVector[0][row] * matrix[row][col]) % MOD;
        }
        plainTextVector += char(sum + 'a');
    }

    return plainTextVector;
}

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
    
    cout << "Key: " << key << ", matrix size: " << block << " X " << block << endl;

    vector<vector<int>> keyMatrix(block, vector<int>(block));
    int row = 0, col = 0;

    for(auto &k: key) {
        keyMatrix[row][col] = k - 'a';
        col = (col + 1) % block;
        if(col == 0) row++;
    }

    cout << "\nKey matrix created: \n";
    for(auto &i : keyMatrix) {
        for(auto &j : i) {
            cout << j << " ";
        }
        cout << endl;
    }

    
    vector<vector<int>> keyMatrixInverse = matrix_mod_inverse(keyMatrix);
    cout << "\nInverse of K modulo 26:" << endl;
    for(auto &row : keyMatrixInverse) {
        for(int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    cout << endl;

    int l;
    for(l = 0; l + block - 1 < cipherTextNoSpace.size(); l += block) {
        string txt = "";
        for(int p = l; p < l + block; p++) {
            txt += cipherTextNoSpace[p];
        }
        // string ct = findCipher(keyMatrix, txt);
        cout << "Cipher text: " << txt << " " << "Plain text: " << findPlain(keyMatrixInverse, txt) << endl;;
    }

    return 0;
}
