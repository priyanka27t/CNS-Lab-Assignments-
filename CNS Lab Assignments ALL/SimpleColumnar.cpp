#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// Function to print the matrix for demonstration
void printMatrix(const vector<vector<char>>& grid, int rows, int cols) {
    cout << "\nMatrix of the plaintext:\n";
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

    // Display the grid matrix
    printMatrix(grid, rows, numCols);

    // Encrypt by reading columns based on the specified column order
    string ciphertext = "";
    for (int col : colOrder) {
        for (int i = 0; i < rows; i++) {
            ciphertext += grid[i][col - 1];  // Subtract 1 to adjust for zero indexing
        }
    }

    return ciphertext;
}

int main() {
    string plaintext;
    int numCols;

    cout << "Enter the plaintext: ";
    getline(cin, plaintext);

    // Remove spaces from the plaintext
    plaintext.erase(remove(plaintext.begin(), plaintext.end(), ' '), plaintext.end());

    cout << "Enter the number of columns: ";
    cin >> numCols;

    // Input the column order
    vector<int> colOrder(numCols);
    cout << "Enter the column order (1 to " << numCols << "): ";
    for (int i = 0; i < numCols; i++) {
        cin >> colOrder[i];
    }

    // Encrypt the plaintext
    string encryptedText = encrypt(plaintext, colOrder, numCols);
    encryptedText.erase(remove(encryptedText.begin(), encryptedText.end(), ' '), encryptedText.end());
    cout << "\nCipher text: " << encryptedText << endl;

    return 0;
}

