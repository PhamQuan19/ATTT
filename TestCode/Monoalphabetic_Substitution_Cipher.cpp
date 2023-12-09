#include <iostream>
#include <string>
#include <map>

using namespace std; 

// Hàm đổi chỗ hai phần tử trong một chuỗi
void swap(char &a, char &b) {
    char temp = a;
    a = b;
    b = temp;
}

// Hàm mã hóa bằng monoalphabetic substitution
string monoalphabeticEncrypt(const string &plaintext, const string &key) {
    map<char, char> substitutionMap; // Tạo bản đồ thay thế

    // Tạo bản đồ thay thế dựa trên khóa
    for (int i = 0; i < 26; i++) {
        substitutionMap['a' + i] = key[i];
    }

    string ciphertext;

    // Mã hóa đoạn văn bản
    for (char c : plaintext) {
        if (isalpha(c)) {
            if (isupper(c)) {
                ciphertext += toupper(substitutionMap[tolower(c)]);
            } else {
                ciphertext += substitutionMap[c];
            }
        } else {
            ciphertext += c; // Giữ nguyên các ký tự không phải chữ cái
        }
    }

    return ciphertext;
}

// Hàm giải mã bằng monoalphabetic substitution
string monoalphabeticDecrypt(const string &ciphertext, const string &key) {
    map<char, char> substitutionMap; // Tạo bản đồ giải mã

    // Tạo bản đồ giải mã dựa trên khóa
    for (int i = 0; i < 26; i++) {
        substitutionMap[key[i]] = 'a' + i;
    }

    string plaintext;

    // Giải mã đoạn văn bản
    for (char c : ciphertext) {
        if (isalpha(c)) {
            if (isupper(c)) {
                plaintext += toupper(substitutionMap[tolower(c)]);
            } else {
                plaintext += substitutionMap[c];
            }
        } else {
            plaintext += c; // Giữ nguyên các ký tự không phải chữ cái
        }
    }

    return plaintext;
}

int main() {
    string key = "bcdefghijklmnopqrstuvwxyza"; // Khóa ví dụ

    string plaintext = "Hello, World123!";
    string encryptedText = monoalphabeticEncrypt(plaintext, key);
    string decryptedText = monoalphabeticDecrypt(encryptedText, key);

    cout << "Plaintext: " << plaintext << endl;
    cout << "Encrypted: " << encryptedText << endl;
    cout << "Decrypted: " << decryptedText << endl;

    return 0;
}
