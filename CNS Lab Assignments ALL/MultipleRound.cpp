#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// Function to print the matrix for demonstration
void printMatrix(const vector<vector<char>>& grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to encrypt the plaintext using columnar transposition
string encrypt(string plaintext, const vector<int>& colOrder, int numCols) {
    int textLen = plaintext.length();
    
    // Calculate number of rows needed
    int rows = (textLen + numCols - 1) / numCols;

    // Fill the matrix with characters row by row
    vector<vector<char>> grid(rows, vector<char>(numCols, ' '));

    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (k < textLen) {
                grid[i][j] = plaintext[k++];
            }
        }
    }

    // Display the matrix after filling it with the current round's plaintext
    cout << "\nMatrix after filling with plaintext in this round:\n";
    printMatrix(grid, rows, numCols);

    // Encrypt by reading columns based on the specified column order
    string ciphertext = "";
    for (int col : colOrder) {
        for (int i = 0; i < rows; i++) {
            if (grid[i][col - 1] != ' ') {  // Avoid spaces
                ciphertext += grid[i][col - 1];
            }
        }
    }

    return ciphertext;
}

int main() {
    string plaintext;
    int numCols, numRounds;

    cout << "Enter the plaintext: ";
    getline(cin, plaintext);

    // Remove spaces from the plaintext
    plaintext.erase(remove(plaintext.begin(), plaintext.end(), ' '), plaintext.end());

    cout << "Enter the number of columns: ";
    cin >> numCols;

    cout << "Enter the number of rounds: ";
    cin >> numRounds;

    string encryptedText = plaintext;

    for (int round = 1; round <= numRounds; round++) {
        cout << "\n--- Round " << round << " ---";

        // Input the column order for each round
        vector<int> colOrder(numCols);
        cout << "Enter the column order for round " << round << " (1 to " << numCols << "): ";
        for (int i = 0; i < numCols; i++) {
            cin >> colOrder[i];
        }

        // Encrypt and display the matrix for this round
        encryptedText = encrypt(encryptedText, colOrder, numCols);

        // Display the ciphertext after the round
        cout << "Cipher text after round " << round << ": " << encryptedText << endl;
    }

    return 0;
}

