#include <iostream>  // Include the iostream library for input and output operations
#include <cstring>   // Include the cstring library for string manipulation functions
using namespace std; // Use the standard namespace

#define SIZE 30     // Define a constant SIZE for the maximum length of input strings

// Function to convert uppercase characters in a string to lowercase
void toLowerCase(char str[], int len) {
    for (int i = 0; i < len; i++) { // Iterate through each character in the string
        if (str[i] >= 'A' && str[i] <= 'Z') // Check if the character is uppercase
            str[i] += 32; // Convert to lowercase by adding 32 (ASCII value difference)
    }
}

// Function to remove spaces from the string and return the new length
int removeSpaces(char* str, int len) {
    int count = 0; // Counter for non-space characters
    for (int i = 0; i < len; i++) { // Iterate through each character
        if (str[i] != ' ') // If the character is not a space
            str[count++] = str[i]; // Copy it to the front of the string
    }
    str[count] = '\0'; // Null-terminate the string
    return count; // Return the new length of the string
}

// Function to generate the key table for the Playfair Cipher
void generateKeyTable(char key[], int keyLen, char keyT[5][5]) {
    int dicty[26] = {0}; // Initialize an array to track characters in the key

    for (int i = 0; i < keyLen; i++) { // Iterate through each character in the key
        if (key[i] != 'j') // Treat 'j' as 'i'
            dicty[key[i] - 'a'] = 2; // Mark the character as used in the key
    }
    dicty['j' - 'a'] = 1; // Mark 'j' as used once

    int i = 0, j = 0; // Initialize indices for the key table
    for (int k = 0; k < keyLen; k++) { // Iterate through the key again
        if (dicty[key[k] - 'a'] == 2) { // If the character is used in the key
            dicty[key[k] - 'a']--; // Decrease its count
            keyT[i][j++] = key[k]; // Add it to the key table
            if (j == 5) { i++; j = 0; } // Move to the next row if the current row is full
        }
    }

    for (int k = 0; k < 26; k++) { // Iterate through all alphabet characters
        if (dicty[k] == 0) { // If the character is not in the key
            keyT[i][j++] = (char)(k + 'a'); // Add it to the key table
            if (j == 5) { i++; j = 0; } // Move to the next row if the current row is full
        }
    }
}

// Function to display the key matrix (5x5)
void displayKeyTable(char keyT[5][5]) {
    cout << "Key Table:" << endl; // Print header for the key table
    for (int i = 0; i < 5; i++) { // Iterate through rows of the key table
        for (int j = 0; j < 5; j++) { // Iterate through columns of the key table
            cout << keyT[i][j] << ' '; // Print each character in the key table
        }
        cout << endl; // Move to the next line after each row
    }
}

// Function to find the positions of two characters in the key table
void search(char keyT[5][5], char a, char b, int arr[]) {
    if (a == 'j') a = 'i';  // Treat 'j' as 'i'
    if (b == 'j') b = 'i';  // Treat 'j' as 'i'

    for (int i = 0; i < 5; i++) { // Iterate through rows of the key table
        for (int j = 0; j < 5; j++) { // Iterate through columns of the key table
            if (keyT[i][j] == a) { // If the character matches 'a'
                arr[0] = i; arr[1] = j; // Store its position in the array
            }
            if (keyT[i][j] == b) { // If the character matches 'b'
                arr[2] = i; arr[3] = j; // Store its position in the array
            }
        }
    }
}

// Function to calculate modulo 5
int mod5(int a) { return (a + 5) % 5; } // Returns the modulus of a with respect to 5

// Modified prepare function to handle bogus characters and track their positions
int prepare(char str[], int len, bool bogusMarkers[]) {
    for (int i = 0; i < len; i += 2) { // Iterate through the string in pairs
        if (str[i] == str[i + 1]) { // If both characters are the same
            for (int j = len; j > i + 1; j--) // Shift characters to the right
                str[j] = str[j - 1]; // Shift characters to the right
            str[i + 1] = 'x'; // Insert 'x' as a bogus character
            bogusMarkers[i + 1] = true;  // Mark 'x' as bogus
            len++; // Increase length of the string
        }
    }
    if (len % 2 != 0) { // If the length is odd
        str[len] = 'z'; // Append 'z' as a bogus character
        bogusMarkers[len] = true;  // Mark 'z' as bogus
        len++; // Increase length of the string
        str[len] = '\0'; // Null-terminate the string
    }
    return len; // Return the new length
}

// Function to encrypt the string using the Playfair Cipher
void encrypt(char str[], char keyT[5][5], int len) {
    int a[4]; // Array to hold positions of characters
    for (int i = 0; i < len; i += 2) { // Iterate through the string in pairs
        search(keyT, str[i], str[i + 1], a); // Find positions of the characters
        if (a[0] == a[2]) { // If both characters are in the same row
            str[i] = keyT[a[0]][mod5(a[1] + 1)]; // Replace with right character in the same row
            str[i + 1] = keyT[a[0]][mod5(a[3] + 1)]; // Replace with right character in the same row
        } else if (a[1] == a[3]) { // If both characters are in the same column
            str[i] = keyT[mod5(a[0] + 1)][a[1]]; // Replace with character below in the same column
            str[i + 1] = keyT[mod5(a[2] + 1)][a[1]]; // Replace with character below in the same column
        } else { // If characters are in different rows and columns
            str[i] = keyT[a[0]][a[3]]; // Replace with character at the intersection
            str[i + 1] = keyT[a[2]][a[1]]; // Replace with character at the intersection
        }
    }
}

// Function to decrypt the string using the Playfair Cipher
void decrypt(char str[], char keyT[5][5], int len) {
    int a[4]; // Array to hold positions of characters
    for (int i = 0; i < len; i += 2) { // Iterate through the string in pairs
        search(keyT, str[i], str[i + 1], a); // Find positions of the characters
        if (a[0] == a[2]) { // If both characters are in the same row
            str[i] = keyT[a[0]][mod5(a[1] - 1)]; // Replace with left character in the same row
            str[i + 1] = keyT[a[0]][mod5(a[3] - 1)]; // Replace with left character in the same row
        } else if (a[1] == a[3]) { // If both characters are in the same column
            str[i] = keyT[mod5(a[0] - 1)][a[1]]; // Replace with character above in the same column
            str[i + 1] = keyT[mod5(a[2] - 1)][a[1]]; // Replace with character above in the same column
        } else { // If characters are in different rows and columns
            str[i] = keyT[a[0]][a[3]]; // Replace with character at the intersection
            str[i + 1] = keyT[a[2]][a[1]]; // Replace with character at the intersection
        }
    }
}

// Modified function to remove only marked bogus characters
void removeBogusCharacters(char str[], int& len, bool bogusMarkers[]) {
    int index = 0; // Index for the new string without bogus characters
    for (int i = 0; i < len; i++) { // Iterate through the string
        if (!bogusMarkers[i]) { // If the character is not bogus
            str[index++] = str[i]; // Keep it in the new string
        }
    }
    str[index] = '\0'; // Null-terminate the new string
    len = index; // Update length after bogus removal
}

// Function to encrypt the string by Playfair Cipher while tracking bogus characters
void encryptByPlayfairCipher(char str[], char keyT[5][5], bool bogusMarkers[]) {
    int len = strlen(str); // Get the length of the input string
    len = prepare(str, len, bogusMarkers);  // Prepare the string and track bogus characters
    encrypt(str, keyT, len);  // Encrypt the string
}

// Function to decrypt the string by Playfair Cipher while tracking bogus characters
void decryptByPlayfairCipher(char str[], char keyT[5][5], bool bogusMarkers[]) {
    int len = strlen(str); // Get the length of the input string
    decrypt(str, keyT, len); // Decrypt the string
    removeBogusCharacters(str, len, bogusMarkers);  // Remove bogus characters based on markers
}

// Main function
int main() {
    char str[SIZE], key[SIZE], keyT[5][5]; // Declare character arrays for plaintext, key, and key table
    bool bogusMarkers[SIZE] = {false};  // Initialize all bogus markers to false

    cout << "Enter the key: "; // Prompt for the encryption key
    cin >> key; // Read the key input

    cout << "Enter the plaintext: "; // Prompt for the plaintext
    cin >> str; // Read the plaintext input

    int keyLen = strlen(key); // Get the length of the key
    keyLen = removeSpaces(key, keyLen); // Remove spaces from the key
    toLowerCase(key, keyLen); // Convert the key to lowercase

    generateKeyTable(key, keyLen, keyT); // Generate the key table
    displayKeyTable(keyT);  // Display the key matrix

    int textLen = strlen(str); // Get the length of the plaintext
    textLen = removeSpaces(str, textLen); // Remove spaces from the plaintext
    toLowerCase(str, textLen); // Convert the plaintext to lowercase

    encryptByPlayfairCipher(str, keyT, bogusMarkers); // Encrypt the plaintext
    cout << "Ciphertext: " << str << endl; // Display the ciphertext

    decryptByPlayfairCipher(str, keyT, bogusMarkers); // Decrypt the ciphertext
    cout << "Decrypted Text: " << str << endl; // Display the decrypted text

    return 0; // Return 0 to indicate successful execution
}

