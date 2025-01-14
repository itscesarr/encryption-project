#include "encryption.h"
#include <fstream>
#include <cctype>
#include <string>

using namespace std;

bool performCaeserCipher(string &content, bool encrypt) {
    int shift = encrypt ? 3 : -3;

    for (char &ch : content) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            ch = static_cast<char>((ch - base + shift + 26) % 26 + base);
        }
    }
    return true;
}

bool encryptFile(const string &filename, bool encrypt) {
    ifstream inFile(filename);
    if (!inFile) {
        return false; // File not found or couldn't be opened
    }

    // Reads the content of the file
    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    if (performCaeserCipher(content, encrypt)) {
        // Create output file and write modified content
        ofstream outFile(encrypt ? "encrypted_" + filename : "decrypted_" + filename);
        if (!outFile) {
            return false; // Failed to open output file
        }

        outFile << content;
        outFile.close();
        return true;
    }

    return false; // Cipher operation failed
}
