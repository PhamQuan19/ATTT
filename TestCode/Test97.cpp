#include <iostream>
#include <string>
#include <map>


using namespace std; // Sử dụng namespace std

// Hàm đổi chỗ hai phần tử trong một chuỗi
void swap(char &a, char &b) {
    char temp = a;
    a = b;
    b = temp;
}

// Hàm mã hóa bằng monoalphabetic substitution
string monoalphabeticEncrypt(const string &plaintext, const string &key) {
    map<char, char> substitutionMap; // Tạo bản đồ thay thế

    // Đảm bảo rằng kích thước của khóa là 97 ký tự
    if (key.length() != 96) {
        return "Invalid key length";
    }

    // Tạo bản đồ thay thế dựa trên khóa
    for (int i = 0; i < 96; i++) {
        substitutionMap[32 + i] = key[i];
    }

    string ciphertext;

    // Mã hóa đoạn văn bản
    for (char c : plaintext) {
        if (substitutionMap.find(c) != substitutionMap.end()) {
            ciphertext += substitutionMap[c];
        } else {
            ciphertext += c; // Giữ nguyên các ký tự không có trong bản đồ thay thế
        }
    }

    return ciphertext;
}

// Hàm giải mã bằng monoalphabetic substitution
string monoalphabeticDecrypt(const string &ciphertext, const string &key) {
    map<char, char> substitutionMap; // Tạo bản đồ giải mã

    // Đảm bảo rằng kích thước của khóa là 97 ký tự
    if (key.length() != 96) {
        return "Invalid key length";
    }

    // Tạo bản đồ giải mã dựa trên khóa
    for (int i = 0; i < 96; i++) {
        substitutionMap[key[i]] = 32 + i;
    }

    string plaintext;

    // Giải mã đoạn văn bản
    for (char c : ciphertext) {
        if (substitutionMap.find(c) != substitutionMap.end()) {
            plaintext += substitutionMap[c];
        } else {
            plaintext += c; // Giữ nguyên các ký tự không có trong bản đồ giải mã
        }
    }

    return plaintext;
}
//nho dieu kien kiem soat
int main() {
    string key="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ~`!@#$%^&*()-_+=|\"\n\t{[]}':;<,>.?/";
    cout << "Do dai: " << key.length() << endl;
    string plaintext = "Hello,Pham ? Quan! 123"; // Ví dụ văn bản gốc
    string encryptedText = monoalphabeticEncrypt(plaintext, key); // Mã hóa
    string decryptedText = monoalphabeticDecrypt(encryptedText, key); // Giải mã

    cout << "Plaintext: " << plaintext << endl;
    cout << "Encrypted: " << encryptedText << endl;
    cout << "Decrypted: " << decryptedText << endl;

    return 0;
}

// plaintext: bản rõ

