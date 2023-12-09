#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <unordered_map>
#include <random>
using namespace std;

//  hàm encrypt thực hiện mã hoá bằng cách duyệt qua từng ký tự trong chuỗi plaintext và thay thế chúng bằng các ký tự
// tương ứng trong ánh xạ cipher nếu chúng tồn tại trong ánh xạ.
//  Nếu không tồn tại trong ánh xạ, ký tự sẽ được giữ nguyên. Kết quả cuối cùng là chuỗi đã mã hoá.

// Hàm mã hoá monoalphabetic substitution
string encrypt(string plaintext, const unordered_map<char, char>& cipher) {
    string ciphertext = "";
    for (char c : plaintext) {
        if (cipher.find(c) != cipher.end()) {
            ciphertext += cipher.at(c);
        } else {
            ciphertext += c;
        }
    }
    return ciphertext;
}

// Hàm giải mã monoalphabetic substitution
string decrypt(string ciphertext, const unordered_map<char, char>& cipher) {
    // Tạo một bản đồ ngược để dễ dàng giải mã
    unordered_map<char, char> reverseCipher;
    // Lặp qua mọi cặp phép thay thế trong ánh xạ và đảo ngược chúng
    for (const auto& pair : cipher) {
        reverseCipher[pair.second] = pair.first;
    }
    // Chuỗi plaintext dùng để lưu kết quả giải mã
    string plaintext = "";
     // Lặp qua từng ký tự trong chuỗi ciphertext
    for (char c : ciphertext) {
        // Kiểm tra xem ký tự c có tồn tại trong bản đồ ngược hay không
        if (reverseCipher.find(c) != reverseCipher.end()) {
            // Nếu tồn tại, thêm ký tự giải mã vào chuỗi plaintext
            plaintext += reverseCipher.at(c);
        } else {
            // Nếu không tồn tại, giữ nguyên ký tự đó (không thực hiện giải mã)
            plaintext += c;
        }
    }
    // Trả về chuỗi plaintext đã giải mã
    return plaintext;
}

// Hàm để tạo bảng chữ cái thay thế ngẫu nhiên
string generateRandomAlphabet() {
    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ~`!@#$%^&*()-_+=|\"\n\t{[]}':;<,>.?/";
    random_shuffle(alphabet.begin(), alphabet.end());
    return alphabet;
}

// Hàm tạo một khóa ngẫu nhiên
string generateRandomKey(string alphabet) {
    string key = alphabet;
    random_device rd;
    mt19937 g(rd());
    shuffle(key.begin(), key.end(), g);
    return key;
}

void menu(){
    cout << "Monoalphabetic Substitution Cipher" << endl;
    cout << "----------------------------------" << endl;
    cout << "1. Ma hoa" << endl;
    cout << "2. Giai ma" << endl;
    cout << "3. Thoat" << endl;
    cout << "----------------------------------" << endl;
    cout << "Nhap lua chon (1/2/3): ";
}
int main() {
    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ~`!@#$%^&*()-_+=|\"\n\t{[]}':;<,>.?/";
   
   string key=generateRandomKey(alphabet);
    unordered_map<char, char> cipher;
    
    cout<<"key: "<<key<< endl;
    cout<<"\nDo dai key: "<<key.length()<< endl;
    cout<<"Do dai alphabet"<<alphabet.length()<< endl;

    if (key.size() == alphabet.size()) {
        // Tạo bản đồ thay thế cho mã hoá
        for (size_t i = 0; i < alphabet.size(); i++) {
            cipher[alphabet[i]] = key[i];
        }
    } else {
        cout << "Key length must match the alphabet length." << endl;
        return 1;
    }

    int choice;
    string text;

    while (true) {
        menu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter text to encrypt: ";
                cin.ignore();
                getline(cin, text);
                cout << "Ciphertext:" << encrypt(text, cipher) << endl;
                break;
            case 2:
                cout << "Enter text to decrypt: ";
                cin.ignore();
                getline(cin, text);
                cout << "Decrypted Text:" << decrypt(text, cipher) << endl;
                break;
            case 3:
                return 0; // Thoát khỏi chương trình
            default:
                cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
        }
    }

    return 0;
}
