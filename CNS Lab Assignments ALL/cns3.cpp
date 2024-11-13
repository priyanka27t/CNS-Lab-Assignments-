#include <iostream>
#include <cctype>  // for toupper

using namespace std;

class PlayfairCipher {
private:
    int length;  // length of digraph array
    char table[5][5];  // 5x5 matrix for Playfair cipher

    // Function to parse input string
    void parseString(char str[], char parsedStr[], int &len) {
        int j = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            if (isalpha(str[i])) {
                parsedStr[j++] = toupper(str[i] == 'J' ? 'I' : str[i]);
            }
        }
        parsedStr[j] = '\0';
        len = j;
    }

    // Function to create the cipher table based on key
    void cipherTable(char key[], int keyLength) {
        bool used[26] = {false};
        used['J' - 'A'] = true;  // Treat 'J' as 'I'

        int k = 0;
        for (int i = 0; i < keyLength; i++) {
            if (!used[key[i] - 'A']) {
                table[k / 5][k % 5] = key[i];
                used[key[i] - 'A'] = true;
                k++;
            }
        }

        for (char ch = 'A'; ch <= 'Z'; ch++) {
            if (!used[ch - 'A']) {
                table[k / 5][k % 5] = ch;
                k++;
            }
        }
    }

    // Function to locate the position of a character in the table
    void getPoint(char ch, int &row, int &col) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (table[i][j] == ch) {
                    row = i;
                    col = j;
                    return;
                }
            }
        }
    }

    // Function to encode a digraph
    void encodeDigraph(char digraph[], char encodedDigraph[]) {
        int r1, c1, r2, c2;
        getPoint(digraph[0], r1, c1);
        getPoint(digraph[1], r2, c2);

        if (r1 == r2) {
            encodedDigraph[0] = table[r1][(c1 + 1) % 5];
            encodedDigraph[1] = table[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            encodedDigraph[0] = table[(r1 + 1) % 5][c1];
            encodedDigraph[1] = table[(r2 + 1) % 5][c2];
        } else {
            encodedDigraph[0] = table[r1][c2];
            encodedDigraph[1] = table[r2][c1];
        }
    }

    // Function to decode a digraph
    void decodeDigraph(char digraph[], char decodedDigraph[]) {
        int r1, c1, r2, c2;
        getPoint(digraph[0], r1, c1);
        getPoint(digraph[1], r2, c2);

        if (r1 == r2) {
            decodedDigraph[0] = table[r1][(c1 + 4) % 5];
            decodedDigraph[1] = table[r2][(c2 + 4) % 5];
        } else if (c1 == c2) {
            decodedDigraph[0] = table[(r1 + 4) % 5][c1];
            decodedDigraph[1] = table[(r2 + 4) % 5][c2];
        } else {
            decodedDigraph[0] = table[r1][c2];
            decodedDigraph[1] = table[r2][c1];
        }
    }

public:
    // Constructor to initialize and run the Playfair Cipher
    PlayfairCipher() {
        char key[100], plaintext[100], parsedKey[100], parsedText[100];
        int keyLength, textLength;

        cout << "Enter the key for playfair cipher: ";
        cin.getline(key, 100);
        parseString(key, parsedKey, keyLength);
        cipherTable(parsedKey, keyLength);

        cout << "Enter the plaintext to be enciphered: ";
        cin.getline(plaintext, 100);
        parseString(plaintext, parsedText, textLength);

        length = (textLength + 1) / 2;
        for (int i = 0; i < length; i++) {
            if (parsedText[2 * i] == parsedText[2 * i + 1]) {
                for (int j = textLength; j > 2 * i + 1; j--) {
                    parsedText[j] = parsedText[j - 1];
                }
                parsedText[2 * i + 1] = 'X';
                textLength++;
            }
        }
        if (textLength % 2 != 0) {
            parsedText[textLength] = 'X';
            textLength++;
        }

        char encodedText[100] = {0}, decodedText[100] = {0};

        for (int i = 0; i < length; i++) {
            encodeDigraph(parsedText + 2 * i, encodedText + 2 * i);
        }

        for (int i = 0; i < length; i++) {
            decodeDigraph(encodedText + 2 * i, decodedText + 2 * i);
        }

        cout << "\nPlayfair Cipher Key Matrix: \n";
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cout << table[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\nEncrypted Message: " << encodedText << endl;
        cout << "Decrypted Message: " << decodedText << endl;
    }
};

int main() {
    PlayfairCipher pf;
    return 0;
}

