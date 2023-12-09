#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <unordered_map>
#include <random>
#include <set>
using namespace std;

//  hàm encrypt thực hiện mã hoá bằng cách duyệt qua từng ký tự trong chuỗi plaintext và thay thế chúng bằng các ký tự
// tương ứng trong ánh xạ cipher nếu chúng tồn tại trong ánh xạ.
//  Nếu không tồn tại trong ánh xạ, ký tự sẽ được giữ nguyên. Kết quả cuối cùng là chuỗi đã mã hoá.

// Hàm mã hoá monoalphabetic substitution
string encrypt(string plaintext, const unordered_map<char, char> &cipher)
{
    string ciphertext = "";
    for (char c : plaintext)
    {
        if (cipher.find(c) != cipher.end())
        {
            ciphertext += cipher.at(c);
        }
        else
        {
            ciphertext += c;
        }
    }
    return ciphertext;
}

// Hàm giải mã monoalphabetic substitution
string decrypt(string ciphertext, const unordered_map<char, char> &cipher)
{
    // Tạo một bản đồ ngược để dễ dàng giải mã
    unordered_map<char, char> reverseCipher;
    // Lặp qua mọi cặp phép thay thế trong ánh xạ và đảo ngược chúng
    for (const auto &pair : cipher)
    {
        reverseCipher[pair.second] = pair.first;
    }
    string plaintext = "";
    // Lặp qua từng ký tự trong chuỗi ciphertext
    for (char c : ciphertext)
    {
        // Kiểm tra xem ký tự c có tồn tại trong bản đồ ngược hay không
        if (reverseCipher.find(c) != reverseCipher.end())
        {
            // Nếu tồn tại, thêm ký tự giải mã vào chuỗi plaintext
            plaintext += reverseCipher.at(c);
        }
        else
        {
            // Nếu không tồn tại, giữ nguyên ký tự đó (không thực hiện giải mã)
            plaintext += c;
        }
    }
    return plaintext;
}

// Hàm tạo một khóa ngẫu nhiên
string generateRandomKey(string alphabet)
{
    string key = alphabet;
    random_device rd;
    mt19937 g(rd());
    shuffle(key.begin(), key.end(), g);
    return key;
}

bool isKeyValid(const string &key, const string &alphabet)
{
    if (key.length() != alphabet.length())
    {
        cout << "Key length must match the alphabet length (97 characters)." << endl;
        return false;
    }

    // set<char> uniqueChars;
    // for (char c : key)
    // {
    //     // Kiểm tra xem kí tự có phải là '\' hoặc ' ' không
    //     if (c == '\\' || c == ' ')
    //     {
    //         continue;
    //     }

    //     if (uniqueChars.count(c) > 0)
    //     {
    //         cout << "Key contains duplicate characters: " << c << std::endl;
    //         return false;
    //     }
    //     uniqueChars.insert(c);
    // }

    set<char> uniqueChars;
    set<char> duplicateChars;

    for (size_t i = 0; i < key.length(); ++i)
    {
        char c = key[i];

        // Kiểm tra xem kí tự có phải là '\' hoặc ' ' không
        if (c == '\\' || c == ' ')
        {
            continue;
        }

        if (uniqueChars.count(c) > 0)
        {
            cout << "Key contains duplicate character: " << c << " at position " << i << endl;
            duplicateChars.insert(c);
        }
        else
        {
            uniqueChars.insert(c);
        }
    }

    return true;
}

void printCipher(const unordered_map<char, char> &cipher)
{
    for (const auto &pair : cipher)
    {
        cout << "Alphabet: " << pair.first << " -> Cipher: " << pair.second << endl;
    }
}

bool containsUnicode(const string &str)
{
    for (char c : str)
    {
        if (static_cast<unsigned char>(c) > 127)
        {
            cout << "Key chua ki tu Unicode" << endl;
            return true; // Ký tự Unicode được tìm thấy
        }
    }
    return false; // Không có ký tự Unicode
}

bool containsVietnameseCharacters(const string &plaintext)
{
    for (char c : plaintext)
    {
        // Kiểm tra mã Unicode của ký tự
        int unicode = static_cast<unsigned char>(c);

        // Kiểm tra xem ký tự có nằm trong khoảng mã Unicode của ký tự tiếng Việt hay không
        if ((unicode >= 0x00C0 && unicode <= 0x1EF9) || (unicode == 0x0111))
        {
            return true;
        }
    }
    return false;
}

void menu()
{
    cout << "Monoalphabetic Substitution Cipher" << endl;
    cout << "----------------------------------" << endl;
    cout << "1. Ma hoa" << endl;
    cout << "2. Giai ma" << endl;
    cout << "3. In chi tiet anh xa" << endl;
    cout << "4. Thoat" << endl;
    cout << "----------------------------------" << endl;
    cout << "Nhap lua chon (1/2/3/4): ";
}

int main()
{
    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ~`!@#$%^&*()-_+=|\"\n\t{[]}':;<,>.?/";
    int choice;
    int luachon;
    string key;
    bool randomKeyGenerated = false;

    unordered_map<char, char> cipher;

    do
    {
        cout << "Choose an option:" << endl;
        cout << "1. Nhap Key" << endl;
        cout << "2. random key" << endl;
        cout << "0. Thoat" << endl;
        cout << "Enter your choice: ";
        cin >> luachon;
        switch (luachon)
        {
        case 1:
            cin.ignore();
            cout << "Enter key: ";
            getline(cin, key);
           

            if (isKeyValid(key, alphabet) && key.size() == alphabet.size())
            {
                break; 
            }
            else
            {
                cout << "Please re-enter the key." << std::endl;
            }
            break;
        case 2:
        {
            key = generateRandomKey(alphabet);
            randomKeyGenerated = true;
            cout << "Random key generated: " << key << endl;
            break;
        }
        case 0:
            break;
        }
    } while (luachon != 0);

    string text;

    while (true)
    {
        menu();
        cin >> choice;

        switch (choice)
        {
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
            // In chi tiết ánh xạ
            printCipher(cipher);
            break;
        case 4:
            cout << "Thoat chuong trinh" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please enter 1, 2, 3, or 4." << endl;
        }
    }

    return 0;
}
// mY"e'1i0=yL!9R4k7}#B&tpwWj;$|`Z/Q*O^sJCS3F) K]ohIGd.+<5X,HaNn:lf -6T@[Vu~E>\(z8%g{Pqv_b2DAxUM?rc

// Sửa chỗ thoát chương trình
// In ra ánh xạ từng kí tự
// Nhập trùng kí tự thì in ra kí tự trùng và vi tri
// Có kí tự tiếng việt
// Không nhập gì ấn enter
//