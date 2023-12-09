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
    // Chuỗi plaintext dùng để lưu kết quả giải mã
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
    // Trả về chuỗi plaintext đã giải mã
    return plaintext;
}

// Hàm để tạo bảng chữ cái thay thế ngẫu nhiên
string generateRandomAlphabet()
{
    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ~`!@#$%^&*()-_+=|\"\n\t{[]}':;<,>.?/";
    random_shuffle(alphabet.begin(), alphabet.end());
    return alphabet;
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

bool isUniqueAndLengthValid(const string &key, const string &alphabet)
{
    unordered_map<char, bool> charExists;

    for (char c : key)
    {
        if (charExists[c])
        {
            cout << "Key contains duplicate characters: " << c << endl;
            return false;
        }
        charExists[c] = true;
    }

    return true;
}

bool isKeyValid(const std::string &key, const std::string &alphabet)
{
    if (key.length() != alphabet.length())
    {
        std::cout << "Key length must match the alphabet length (97 characters)." << std::endl;
        return false;
    }

    set<char> uniqueChars;
    for (char c : key)
    {
        // Kiểm tra xem kí tự có phải là '\' hoặc ' ' không
        if (c == '\\' || c == ' ')
        {
            continue;
        }

        if (uniqueChars.count(c) > 0)
        {
            std::cout << "Key contains duplicate characters: " << c << std::endl;
            return false;
        }
        uniqueChars.insert(c);
    }

    return true;
}

void menu()
{
    cout << "Monoalphabetic Substitution Cipher" << endl;
    cout << "----------------------------------" << endl;
    cout << "1. Ma hoa" << endl;
    cout << "2. Giai ma" << endl;
    cout << "3. Thoat" << endl;
    cout << "----------------------------------" << endl;
    cout << "Nhap lua chon (1/2/3): ";
}
int main()
{
    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ~`!@#$%^&*()-_+=|\"\n\t{[]}':;<,>.?/";
     int choice;
    int luachon;
    string key;
    bool randomKeyGenerated = false;
    do{
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
            while (true)
            {

                // cout << "Nhap key: ";
                // getline(cin, key);

                if (isKeyValid(key, alphabet) && key.size() == alphabet.size())
                {
                    break; // Thoát khỏi vòng lặp nếu key hợp lệ
                }
                else
                {
                    cout << "Please re-enter the key." << std::endl;
                }
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

    // do
    // {
    //     cout << "Choose an option:" << endl;
    //     cout << "1. Nhap Key" << endl;
    //     cout << "2. random key" << endl;
    //     cout << "0. Thoat" << endl;
    //     cout << "Enter your choice: ";
    //     cin >> luachon;

    //     if (luachon == 1)
    //     {
    //         cin.ignore();
    //         cout << "Enter key: ";
    //         getline(cin, key);
    //         while (true)
    //         {

    //             // cout << "Nhap key: ";
    //             // getline(cin, key);

    //             if (isKeyValid(key, alphabet) && key.size() == alphabet.size())
    //             {
    //                 break; // Thoát khỏi vòng lặp nếu key hợp lệ
    //             }
    //             else
    //             {
    //                 cout << "Please re-enter the key." << std::endl;
    //             }
    //         }
    //     }
    //     if (luachon == 2)
    //     {

    //         {
    //             key = generateRandomKey(alphabet);
    //             randomKeyGenerated = true;
    //             cout << "Random key generated: " << key << endl;
    //             break;
    //         }
    //     }
    //     if (luachon == 0)
    //     {
    //         break;
    //     }

    // } while (luachon != 1 && luachon != 2);

    unordered_map<char, char> cipher;

    // cout << "key: " << key << endl;
    // cout << "\nDo dai key: " << key.length() << endl;
    // cout << "Do dai alphabet" << alphabet.length() << endl;

    if (key.size() == alphabet.size())
    {
        // Tạo bản đồ thay thế cho mã hoá
        for (size_t i = 0; i < alphabet.size(); i++)
        {
            cipher[alphabet[i]] = key[i];
        }
    }
    else
    {
        cout << "Key length must match the alphabet length." << endl;
        return 1;
    }

    // int choice;
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
            return 0; // Thoát khỏi chương trình
        default:
            cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
        }
    }
    }while (choice!= 0);
    
    
    return 0;
}

// U}Rm~Gj.I)`7r<OJV   8&0K^{o|i:"[xfw4Bye9g!2ub5c=Lv?F>n%al_XM*Z@kq-(Hp$s'PTd1 CA,DQ]W6hY/;#SE3+zNt
// mY"e'1i0=yL!9R4k7}#B&tpwWj;$|`Z/Q*O^sJCS3F) K]ohIGd.+<5X,HaNn:lf -6T@[Vu~E>\(z8%g{Pqv_b2DAxUM?rc
// Ve4sh}l|b+d*pB17zjQ =:v_,6% A&/gYZ[rK9;x#2HC'y<Om$Jf!U-Ew.a>t0Fi"3DR?Tc@Gok{^nN~qW5(]M)u8LI`XSP