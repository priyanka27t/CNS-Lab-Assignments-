#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Function to generate the key matrix from the key string
void getKeyMatrix(const string& key, vector<vector<int>>& keyMatrix) {
    int k = 0;
    int size = keyMatrix.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            keyMatrix[i][j] = (key[k++] - 'A') % 26; // Adjust to 0-25 range
        }
    }
}

// Function to encrypt the message
void encrypt(vector<vector<int>>& cipherMatrix, const vector<vector<int>>& keyMatrix, const vector<vector<int>>& messageVector) {
    int size = keyMatrix.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < messageVector[0].size(); j++) {
            cipherMatrix[i][j] = 0;
            for (int x = 0; x < size; x++) {
                cipherMatrix[i][j] += keyMatrix[i][x] * messageVector[x][j];
            }
            cipherMatrix[i][j] %= 26; // Adjust to 0-25 range
        }
    }
}

// Function to implement Hill Cipher
void HillCipher(const string& message, const string& key) {
    int size = sqrt(key.length()); // Determine the size of the key matrix
    vector<vector<int>> keyMatrix(size, vector<int>(size));
    getKeyMatrix(key, keyMatrix);

    // Pad the message with 'X' if necessary
    string paddedMessage = message;
    while (paddedMessage.length() % size != 0) {
        paddedMessage += 'X'; // Padding character
    }

    // Create message vector (size x columns)
    vector<vector<int>> messageVector(size, vector<int>(paddedMessage.length() / size));
    for (int j = 0; j < paddedMessage.length() / size; j++) {
        for (int i = 0; i < size; i++) {
            messageVector[i][j] = (paddedMessage[i + j * size] - 'A') % 26; // Adjust to 0-25 range
        }
    }

    vector<vector<int>> cipherMatrix(size, vector<int>(paddedMessage.length() / size));
    // Encrypt the message
    encrypt(cipherMatrix, keyMatrix, messageVector);

    // Generate the encrypted text from the encrypted vector
    string CipherText;
    for (int j = 0; j < paddedMessage.length() / size; j++)
        for (int i = 0; i < size; i++)
            CipherText += (cipherMatrix[i][j] + 'A'); // Adjust to ASCII

    cout << "Ciphertext: " << CipherText << endl;
}

// Driver function
int main() {
    // Get the plaintext from the user
    string message;
    cout << "Enter the plaintext (only uppercase letters): ";
    cin >> message;

    // Get the key from the user
    string key;
    cout << "Enter the key (4, 9, or 16 uppercase letters for 2x2, 3x3 or larger matrices): ";
    cin >> key;

    HillCipher(message, key);
    return 0;
}

