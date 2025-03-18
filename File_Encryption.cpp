#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string caesarCipher(const string& text, int shift, bool encrypt = true) {
    string result;
    shift = encrypt ? shift : (26 - shift);
    for (char ch : text) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            result += (ch - base + shift) % 26 + base;
        }
        else {
            result += ch;
        }
    }
    return result;
}

void processFile(const string& inputFilePath, const string& outputFilePath, int shift, bool encrypt) {
    ifstream inputFile(inputFilePath);
    if (!inputFile) {
        cerr << "Error opening file " << inputFilePath << " for reading." << endl;
        return;
    }

    ofstream outputFile(outputFilePath);
    if (!outputFile) {
        cerr << "Error opening file " << outputFilePath << " for writing." << endl;
        return;
    }

    string line;
    cout << "Original file contents:" << endl;
    while (getline(inputFile, line)) {
        cout << line << endl; 
        string processedLine = caesarCipher(line, shift, encrypt);
        outputFile << processedLine << endl;
        cout << (encrypt ? "Encrypted: " : "Decrypted: ") << processedLine << endl;
    }

    cout << "File processed successfully: " << outputFilePath << endl;
}

void decryptFile(const string& filePath, int shift) {
    ifstream inputFile(filePath);
    if (!inputFile) {
        cerr << "Error opening file " << filePath << " for reading." << endl;
        return;
    }

    cout << "Decrypted file contents:" << endl;
    string line;
    while (getline(inputFile, line)) {
        string decryptedLine = caesarCipher(line, shift, false);
        cout << decryptedLine << endl;
    }
}

int main() {
    string originalFile;
    int shift = 5;

    cout << "Enter the path of the original file: ";
    cin >> originalFile;

    string encryptedFile = originalFile + ".enc";
    processFile(originalFile, encryptedFile, shift, true);
    decryptFile(encryptedFile, shift);

    return 0;
}
