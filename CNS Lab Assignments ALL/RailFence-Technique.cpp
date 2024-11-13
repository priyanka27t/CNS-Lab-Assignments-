#include <iostream>
#include <cstring>
using namespace std;

// Function to encrypt the plaintext using Rail Fence Cipher
string encryptRailFence(string text, int key) {
    int len = text.length();
    char rail[key][len];

    // Initialize the rail matrix with '\n'
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < len; j++) {
            rail[i][j] = '\n';
        }
    }

    // Fill the rail matrix in a zigzag pattern
    bool dir_down = false;
    int row = 0, col = 0;

    for (int i = 0; i < len; i++) {
        // Change direction when reaching the top or bottom
        if (row == 0 || row == key - 1) {
            dir_down = !dir_down;
        }

        // Place the character in the current rail
        rail[row][col++] = text[i];

        // Move to the next row based on direction
        dir_down ? row++ : row--;
    }

    // Display the zigzag arrangement
    cout << "\nZigzag arrangement:\n";
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] == '\n') {
                cout << " ";
            } else {
                cout << rail[i][j];
            }
        }
        cout << endl;
    }

    // Construct the ciphertext by reading the rails row-wise
    string result;
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] != '\n') {
                result.push_back(rail[i][j]);
            }
        }
    }

    return result;
}

int main() {
    string text;
    int key;

    // Get plaintext and key from the user
    cout << "Enter the plaintext: ";
    getline(cin, text);
    
    cout << "Enter the key (number of rails): ";
    cin >> key;

    // Encrypt the plaintext
    string ciphertext = encryptRailFence(text, key);
    
    // Display the ciphertext
    cout << "\nCiphertext: " << ciphertext << endl;

    return 0;
}

