#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <unordered_map>
#include <random>
#include <sstream>
#include <set>
#include <map>
#include <unordered_set>
using namespace std;

//  h�m encrypt th?c hi?n m� ho� b?ng c�ch duy?t qua t?ng k� t? trong chu?i plaintext v� thay th? ch�ng b?ng c�c k� t?
// tuong ?ng trong �nh x? cipher n?u ch�ng t?n t?i trong �nh x?.
//  N?u kh�ng t?n t?i trong �nh x?, k� t? s? du?c gi? nguy�n. K?t qu? cu?i c�ng l� chu?i d� m� ho�.

// H�m m� ho� monoalphabetic substitution
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

// H�m gi?i m� monoalphabetic substitution
string decrypt(string ciphertext, const unordered_map<char, char> &cipher)
{
    // T?o m?t b?n d? ngu?c d? d? d�ng gi?i m�
    unordered_map<char, char> reverseCipher;
    // L?p qua m?i c?p ph�p thay th? trong �nh x? v� d?o ngu?c ch�ng
    for (const auto &pair : cipher)
    {
        reverseCipher[pair.second] = pair.first;
    }
    string plaintext = "";
    // L?p qua t?ng k� t? trong chu?i ciphertext
    for (char c : ciphertext)
    {
        // Ki?m tra xem k� t? c c� t?n t?i trong b?n d? ngu?c hay kh�ng
        if (reverseCipher.find(c) != reverseCipher.end())
        {
            // N?u t?n t?i, th�m k� t? gi?i m� v�o chu?i plaintext
            plaintext += reverseCipher.at(c);
        }
        else
        {
            // N?u kh�ng t?n t?i, gi? nguy�n k� t? d� (kh�ng th?c hi?n gi?i m�)
            plaintext += c;
        }
    }
    return plaintext;
}

// H�m t?o m?t kh�a ng?u nhi�n
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
        cout << "Do dai khoa K khong hop le, phai la 97 ki tu." << endl;
        return false;
    }

    set<char> uniqueChars;
    set<char> duplicateChars;

    for (size_t i = 0; i < key.length(); ++i)
    {
        char c = key[i];

        // Ki?m tra xem k� t? c� ph?i l� '\' ho?c ' ' kh�ng
        if (c == '\\' || c == ' ')
        {
            continue;
        }

        if (uniqueChars.count(c) > 0)
        {
            // cout << "Ki tu trung: " << c << " tai vi tri: " << i << endl;
            duplicateChars.insert(c);
            return false;
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
        cout << "+ Ki tu : " << pair.first << " -> " << pair.second << endl;
    }
}

// Hàm ánh xạ bảng chữ thay thế cho các ký tự cụ thể
unordered_map<char, char> generateSubstitutionCipher(const string &originalChars, const string &substituteChars)
{
    unordered_map<char, char> cipherMap;

    // Đảm bảo độ dài của hai chuỗi bằng nhau
    if (originalChars.length() != substituteChars.length())
    {
        cerr << "Do dai chuoi khong khop." << endl;
        return cipherMap;
    }

    // Tạo ánh xạ
    for (size_t i = 0; i < originalChars.length(); ++i)
    {
        cipherMap[originalChars[i]] = substituteChars[i];
    }

    return cipherMap;
}

// Hàm ánh xạ bản rõ với ánh xạ đã tạo
void mapPlainText(const unordered_map<char, char> &cipher, const string &plaintext)
{
    cout << "Anh xa ki tu tu ban ro vao ban ma:" << endl;
    for (char c : plaintext)
    {
        auto it = cipher.find(c);
        if (it != cipher.end())
        {
            cout << "Ban ro: " << c << " -> Ban ma: " << it->second << endl;
        }
        else
        {
            cout << "Khong tim thay anh xa cho ki tu ban ro: " << c << endl;
        }
    }
}

// Hàm ánh xạ từ bản mã về bản rõ
void mapCipherTextToPlainText(const unordered_map<char, char> &cipher, const string &ciphertext)
{
    cout << "Anh xa ky tu tu ban ma vao ban ro:" << endl;
    for (char c : ciphertext)
    {
        // Tìm ký tự bản rõ tương ứng trong ánh xạ
        auto it = find_if(cipher.begin(), cipher.end(), [c](const auto &pair)
                          { return pair.second == c; });
        if (it != cipher.end())
        {
            cout << "Ban ma: " << c << " -> Ban ro: " << it->first << endl;
        }
        else
        {
            cout << "Khong tim thay ki tu cho anh xa ban ma: " << c << endl;
        }
    }
}

bool containsVietnameseDiacritics(const std::string &str)
{
    // Duyệt qua từng kí tự trong chuỗi UTF-8
    for (size_t i = 0; i < str.size(); ++i)
    {
        // Nếu là kí tự tiếng Việt có dấu
        if ((str[i] & 0xC0) == 0x80)
        {
            return true;
        }
    }
    return false; // Nếu không có kí tự tiếng Việt có dấu, trả về false
}

bool containsUnicode(const string &str)
{
    for (char c : str)
    {
        if (static_cast<unsigned char>(c) > 127)
        {
            cout << "Key chua ki tu Unicode" << endl;
            return true; // K� t? Unicode du?c t�m th?y
        }
    }
    return false; // Kh�ng c� k� t? Unicode
}

bool isContainNonASCII(string txt)
{
    for (int i = 0; i < txt.length(); i++)
    {
        if (!(int(txt[i]) >= 33 && int(txt[i]) <= 126 && int(txt[i]) != 63))
        {
            return true;
        }
    }
    return false;
}

void menu()
{
    cout << endl;
    cout << "----------Monoalphabetic Substitution Cipher----------" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "----------		1. Ma hoa	 	----------" << endl;
    cout << "----------		2. Giai ma		-----------" << endl;
    cout << "----------		3. Chi tiet anh xa	----------" << endl;
    cout << "----------		4. Thoat	 	----------" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "\n- Nhap lua chon : ";
}

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

using namespace std;

// Hàm kiểm tra key có thiếu ký tự so với alphabet
string checkMissingCharacters(const string &key, const string &alphabet)
{
    unordered_set<char> keySet(key.begin(), key.end());
    string missingCharacters;

    for (char c : alphabet)
    {
        // Bỏ qua kí tự '\t' và dấu cách
        if (c == '\t' || c == ' ')
        {
            continue;
        }

        if (keySet.find(c) == keySet.end())
        {
            missingCharacters += c;
        }
    }

    return missingCharacters;
}

// Hàm kiểm tra key có chứa ký tự không hợp lệ
bool hasInvalidCharacters(const string &key, const string &validChars)
{
    for (char c : key)
    {
        // Bỏ qua kí tự '\t' và dấu cách
        if (c == '\t' || c == ' ')
        {
            continue;
        }

        if (validChars.find(c) == string::npos)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ~`!@#$%^&*()-_+=|\"\n\t{[]}':;<,>.?/";
    int choice;
    int luachon;
    string key;
    bool randomKeyGenerated = false;
    bool hasVietCharacter = false;
    unordered_map<char, char> cipher;
    stringstream ss;
    cout << "\n\nMonoalphabetic Substitution Cipher\n\n";

    while (luachon != 1 && luachon != 2)
    {
        cout << "---------- Key K -----------" << endl;
        cout << "-----	1. Nhap Key	-----" << endl;
        cout << "-----	2. Random key-----" << endl;
        cout << "----------------------------" << endl;
        cout << "\n- Nhap lua chon cua ban: ";
        cin >> luachon;
        cin.ignore();
        if (luachon == 1)
        {
            do
            {
                cout << "\n- Khoa K nhap tu ban phim:";
                getline(cin, key);

                // Kiểm tra key có thiếu ký tự không
                string missingChars = checkMissingCharacters(key, alphabet);

                if (!missingChars.empty())
                {
                    cout << "Key nhap vao thieu cac ky tu sau trong alphabet: " << missingChars << endl;
                    cout << "Vui long nhap lai key!" << endl;
                    hasVietCharacter = true;
                }
                else if (hasInvalidCharacters(key, alphabet))
                {
                    cout << "Key nhap vao chua ky tu khong hop le. Vui long chi nhap cac ky tu trong alphabet!" << endl;
                    hasVietCharacter = true;
                }
                else if (containsVietnameseDiacritics(key))
                {
                    cout << "\n==> Chuoi chua ki tu Tieng Viet" << endl;
                    hasVietCharacter = true;
                }
                else if (key.empty())
                {
                    cout << "\n==> Vui long nhap khoa!";
                    ss.clear();
                    hasVietCharacter = true;
                }
                else if (!isKeyValid(key, alphabet))
                {
                    set<char> uniqueChars;
                    set<char> duplicateChars;

                    for (size_t i = 0; i < key.length(); ++i)
                    {
                        char c = key[i];

                        if (c == '\\' || c == ' ')
                        {
                            continue;
                        }

                        if (uniqueChars.count(c) > 0)
                        {
                            cout << "Ki tu trung: " << c << " tai vi tri: " << i << endl;
                            duplicateChars.insert(c);
                        }
                        else
                        {
                            uniqueChars.insert(c);
                        }
                    }
                    hasVietCharacter = true;
                }
                else
                {
                    hasVietCharacter = false;
                }
            } while (hasVietCharacter);
            // Tạo bản đồ thay thế cho mã hóa
            for (size_t i = 0; i < alphabet.size(); i++)
            {
                cipher[alphabet[i]] = key[i];
            }
            break;
        }
        else if (luachon == 2)
        {
            key = generateRandomKey(alphabet);
            randomKeyGenerated = true;
            cout << "Khoa K ngau nhien: " << key << endl;

            // Tạo bản đồ thay thế cho mã hóa
            for (size_t i = 0; i < alphabet.size(); i++)
            {
                cipher[alphabet[i]] = key[i];
            }
            break;
        }
        else
        {
            cout << "Khong co lua chon nay. Vui long chon 1 hoac 2." << endl;
        }
    }

    string text;
    string str1 = "";
    unordered_map<char, char> substitutionCipher;
    while (true)
    {
        menu();
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            do
            {
                cout << "- Chuoi ban ro (P): ";
                getline(cin, text);
                if (containsUnicode(text))
                {
                    cout << "==> Chuoi chua ki tu Tieng Viet. Nhap lai chuoi!" << endl;
                    hasVietCharacter = true;
                }
                else
                {
                    hasVietCharacter = false;
                }
            } while (hasVietCharacter);
            cout << "Ban ma (C):" << encrypt(text, cipher) << endl;
            substitutionCipher = generateSubstitutionCipher(alphabet, key);
            // Ánh xạ bản rõ với ánh xạ đã tạo
            mapPlainText(substitutionCipher, text);
            break;
        case 2:
            str1 = encrypt(text, cipher);
            cout << "Ban ro(P):" << decrypt(str1, cipher) << endl;
            substitutionCipher = generateSubstitutionCipher(alphabet, key);
            // Ánh xạ bản rõ với ánh xạ đã tạo
            mapCipherTextToPlainText(substitutionCipher, str1);
            break;
        case 3:
            printCipher(cipher);
            break;
        case 4:
            cout << "Thoat" << endl;
            return 0;
        default:
            cout << "=>Khong co lua chon nay!!!" << endl;
        }
    }

    return 0;
}


// mY"e'1i0=yL!9R4k7}#B&tpwWj;$|`Z/Q*O^sJCS3F) K]ohIGd.+<5X,HaNn:lf -6T@[Vu~E>\(z8%g{Pqv_b2DAxUM?rc
//_sHb$xu"mj)!2ZeKin1Dh q+0T|5;pfLtGYFR/\=-:6`~%w{M4'U3[.QS 7]*Eo(c}rlz><9gJk@XaIOv#B&dVNWCy8,?^AP
// S?a ch? tho�t chuong tr�nh
// In ra �nh x? t?ng k� t?
// Nh?p tr�ng k� t? th� in ra k� t? tr�ng
// Nh?p th?a k� t?
// C� k� t? ti?ng vi?t
// Kh�ng nh?p g� ?n enter
//
