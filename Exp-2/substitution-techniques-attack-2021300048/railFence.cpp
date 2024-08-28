#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<vector<char>> createRailMatrix(int depth, int length) {
    vector<vector<char>> rail(depth, vector<char>(length, ' '));
    bool direction_down = false;
    int row = 0, col = 0;

    for (int i = 0; i < length; i++) {
        if (row == 0 || row == depth - 1) {
            direction_down = !direction_down;
        }
        rail[row][col++] = '*';
        row += direction_down ? 1 : -1;
    }
    return rail;
}

void fillRailMatrix(vector<vector<char>> &rail, const string &ciphertext) {
    int index = 0;
    for(int row = 0; row < rail.size(); row++) {
        for(int col = 0; col < rail[row].size(); col++) {
            if(rail[row][col] == '*') {
                rail[row][col] = ciphertext[index++];
            }
        }
    }
    
}

string readRailMatrix(const vector<vector<char>> &rail, int length) {
    string result;
    int row = 0, col = 0;
    bool direction_down = false;

    for(int i = 0; i < length; i++) {
        if(row == 0 || row == rail.size() - 1) {
            direction_down = !direction_down;
        }
        if(rail[row][col] != ' ') {
            result += rail[row][col];
            col++;
        }
        row += direction_down ? 1 : -1;
    }
    return result;
}

// Function to decrypt using Rail Fence cipher
string railFenceDecrypt(const string &ciphertext, int depth) {
    vector<vector<char>> rail = createRailMatrix(depth, ciphertext.length());
   
    cout << "Trying depth " << depth << endl;
    
    cout << "Created rail matrix of size: " << rail.size() << ", " << rail[0].size() << endl << endl;;
    
    for(int i = 0; i < rail.size(); i++) {
        for(int j = 0; j < rail[0].size(); j++) {
            cout << rail[i][j] << " ";
        }
        cout << endl;
    }
    
    fillRailMatrix(rail, ciphertext);
    
    cout << "\nFilled rail matrix: \n\n";
    for(auto &i : rail) {
        for(auto &j : i) {
            cout << j << " ";
        }
        cout << endl;
    } 

    return readRailMatrix(rail, ciphertext.length());
}

void bruteForceRailFence(const string &ciphertext) {
    for (int depth = 2; depth <= ciphertext.length(); depth++) {
        string decrypted_text = railFenceDecrypt(ciphertext, depth);
        cout << "\nDecrypted Text: " << decrypted_text << endl << endl;
        cout << "--------------------------------\n";
    }
}

int main() {
    string ciphertext = "";
    cout << "Enter cipher text: ";
    cin >> ciphertext; 
    cout << ciphertext;
    bruteForceRailFence(ciphertext);
    return 0;
}

// TC: holelwrdlo

/*
Enter cipher text: holewrdloTrying depth 2
Created rail matrix of size: 2, 9

*   *   *   *   * 
  *   *   *   *   

Filled rail matrix: 

h   o   l   e   w 
  r   d   l   o   

Decrypted Text: hrodlleow

--------------------------------
Trying depth 3
Created rail matrix of size: 3, 9

*       *       * 
  *   *   *   *   
    *       *     

Filled rail matrix: 

h       o       l 
  e   w   r   d   
    l       o     

Decrypted Text: helworodl

--------------------------------
Trying depth 4
Created rail matrix of size: 4, 9

*           *     
  *       *   *   
    *   *       * 
      *           

Filled rail matrix: 

h           o     
  l       e   w   
    r   d       l 
      o           

Decrypted Text: hlrodeowl

--------------------------------
Trying depth 5
Created rail matrix of size: 5, 9

*               * 
  *           *   
    *       *     
      *   *       
        *         

Filled rail matrix: 

h               o 
  l           e   
    w       r     
      d   l       
        o         

Decrypted Text: hlwdolreo

--------------------------------
Trying depth 6
Created rail matrix of size: 6, 9

*                 
  *               
    *           * 
      *       *   
        *   *     
          *       

Filled rail matrix: 

h                 
  o               
    l           e 
      w       r   
        d   l     
          o       

Decrypted Text: holwdolre

--------------------------------
Trying depth 7
Created rail matrix of size: 7, 9

*                 
  *               
    *             
      *           
        *       * 
          *   *   
            *     

Filled rail matrix: 

h                 
  o               
    l             
      e           
        w       r 
          d   l   
            o     

Decrypted Text: holewdolr

--------------------------------
Trying depth 8
Created rail matrix of size: 8, 9

*                 
  *               
    *             
      *           
        *         
          *       
            *   * 
              *   

Filled rail matrix: 

h                 
  o               
    l             
      e           
        w         
          r       
            d   l 
              o   

Decrypted Text: holewrdol

--------------------------------
Trying depth 9
Created rail matrix of size: 9, 9

*                 
  *               
    *             
      *           
        *         
          *       
            *     
              *   
                * 

Filled rail matrix: 

h                 
  o               
    l             
      e           
        w         
          r       
            d     
              l   
                o 

Decrypted Text: holewrdlo

--------------------------------
*/