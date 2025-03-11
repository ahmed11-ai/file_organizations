#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
using namespace std;


string caesarEncrypt(const string& text, int shift) {
    string result = text;
    for (char& ch : result) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            ch = (ch - base + shift) % 26 + base;
        }
    }
    return result;
}


string caesarDecrypt(const string& text, int shift) {
    return caesarEncrypt(text, 26 - shift);
}


void encryptFile(const string& inputFilePath, const string& outputFilePath, int shift) {
    ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        cerr << "Error opening file " << inputFilePath << " for reading." << endl;
        return;
    }
    ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        cerr << "Error opening file " << outputFilePath << " for writing." << endl;
        return;
    }
    string line;
    cout << "Original Contents:" << endl;
    while (getline(inputFile, line)) {
        cout << line << endl;
        string encryptedLine = caesarEncrypt(line, shift);
        outputFile << encryptedLine << endl;
        cout << "Encrypted: " << encryptedLine << endl;
    }
    cout << "File has been encrypted and saved to " << outputFilePath << endl;
}


void decryptFile(const string& inputFilePath, int shift) {
    ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        cerr << "Error opening file " << inputFilePath << " for reading." << endl;
        return;
    }
    string line;
    cout << "Decrypted file contents:" << endl;
    while (getline(inputFile, line)) {
        string decryptedLine = caesarDecrypt(line, shift);
        cout << decryptedLine << endl;
    }
}

int main() {
    string originalFile;
    int shift = 5;

    cout << "Enter the path of the original file: ";
    cin >> originalFile;

    string encryptedFile = originalFile + ".enc";

    encryptFile(originalFile, encryptedFile, shift);
    decryptFile(encryptedFile, shift);

    _getch();
    return 0;
}
