#include <iostream>
#include <string>
//#include <time.h>
#include <stdlib.h>
#include <limits>
#include <sstream>
using namespace std;


int tinhMa(int number)
{
	string str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ~`!@#$%^&*()-_+=|\\\"\n\t{[]}:;'<,.>?/0123456789";
	int length = str.length();
	return ((number%length)+length)%length;
}

// ma hoa caesar
string encryptCaesar(string ciphertext, int k)
{
    string result = "";
    int length = ciphertext.length();
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ~`!@#$%^&*()-_+=|\\\"\n\t{[]}:;'<,.>?/0123456789";
    for (int i = 0; i < length; i++)
    {
        char currentChar = ciphertext[i];
        size_t position = characters.find(currentChar);

        if (position != string::npos)//gia tri khong tim thay
        {
        	 //int newPosition = (position + k ) % str.length();
            int newPosition = tinhMa(position + k);
            result += characters[newPosition];
            cout << "\n+ Ki tu: " << currentChar << " ==>  " << result[result.length() - 1] << endl;
        }
    }
    return result;
}

// giai ma caesar
string decryptCaesar(string ciphertext, int k)
{
    string result = "";
    int length = ciphertext.length();
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ~`!@#$%^&*()-_+=|\\\"\n\t{[]}:;'<,.>?/0123456789";
    for (int i = 0; i < length; i++)
    {
        char currentChar = ciphertext[i];
        size_t position = characters.find(currentChar);

        if (position != string::npos)//gia tri khong tim thay
        {
            //int newPosition = (position - k ) % str.length();
            int newPosition = tinhMa(position - k);
            result += characters[newPosition];
            cout << "\n+ Ki tu: " << currentChar << " ==>  " << result[result.length() - 1]  << endl;
        }
    }
    return result;
}


// chuoi plaintext co chua ki tu khong nam trong danh sach khong
bool characterNotString(string plaintext)
{
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ~`!@#$%^&*()-_+=|\\\"\n\t{[]}:;'<,.>?/0123456789";

    for (char c : plaintext)
    {
        if (characters.find(c) == string::npos)
        {
            return true;
        }
    }
    return false;
}

bool containsVietnameseCharacters(const string& plaintext) {
    for (char c : plaintext) {
        // Kiểm tra mã Unicode của ký tự
        int unicode = static_cast<unsigned char>(c);
        
        // Kiểm tra xem ký tự có nằm trong khoảng mã Unicode của ký tự tiếng Việt hay không
        if ((unicode >= 0x00C0 && unicode <= 0x1EF9) || (unicode == 0x0111)) {
            return true;
        }
    }
    return false;
}
int main()
{
    string plaintext;
    int lc, luachon;
    int k;
    bool hasVietCharacter = false; // bien dieu kien de kiem soat vong lap ban ro

    cout << "------------Ma dich vong (Caesar)----------" << endl;
    do
    {
        cout << "\n - Chuoi ban ro(P) : ";
        getline(cin, plaintext);
        if (characterNotString(plaintext))
        {
            cout << "==> Chuoi chua ki tu Tieng Viet. Nhap lai chuoi!" << endl;
            hasVietCharacter = true;
        }
        else
        {
            hasVietCharacter = false;
        }
    } while (hasVietCharacter);

    do
    {
        while (lc != 1 && lc != 2)
        {
        	cout << "\n-------------------KEY K------------------";
            cout << "\n---       1. Khoa K ngau nhien         ---";
            cout << "\n---       2. Khoa K nhap tu ban phim   ---";
            cout << "\n------------------------------------------";
            cout << "\n\n - Lua chon cua ban: ";
            cin >> lc;

            if (lc == 1)
            {
                //srand(time(0)); // Khoi tao seed ngau nhien
                k = rand();
                cout << " => Khoa K ngau nhien: " << k << endl;
            }
            else if (lc == 2)
            {
                string inputLine;
                stringstream ss;
                cin.ignore();
                do
                {
                    cout << " => Khoa K nhap tu ban phim: ";
                    getline(cin, inputLine);

                     ss.clear(); // Xoa trang thai loi cua stringstream
                    // Su dung stringstream de chuyen doi chuoi thanh so nguyen
                    ss.str(inputLine);
                    if (!(ss >> k) || !inputLine.length() ||k<0)
                    {
                        cout << "==> Khong duoc de khoa K trong và phai la so" << endl;
                    }

                } while (!inputLine.length() || ss.fail()||k<0);

            }
            else
            {
                cout << "--> Khong co lua chon nay. Vui long chon 1 hoac 2." << endl;
            }
        }

        cout << "\n----------------MENU----------------";
        cout << "\n---        1. Ma hoa Caesar      ---";
        cout << "\n---        2. Giai ma Caesar     ---";
        cout << "\n---        3. Thoat!             ---";
        cout << "\n------------------------------------";
        cout << "\n\n - Lua chon cua ban: ";
        cin >> luachon;
        switch (luachon)
        {
        case 1:
        {
            cout << "\n - Chuoi ban ro (P): " << plaintext;
            cout << "\n - Khoa K= " << k;
            cout << "\n - Ma hoa lan luot cac ki tu:";
            string encrypted = encryptCaesar(plaintext, k);
            cout << "\n --> Ban ma (C): " << encrypted << endl;
            break;
        }
        case 2:
        {
            string encrypted = encryptCaesar(plaintext, k);
            cout << "\n\n - Ban ma(C): " << encrypted;
            cout << "\n - Khoa K= " << k;
            cout << "\n - Giai ma lan luot cac ki tu:";
            string decrypted = decryptCaesar(encrypted, k);
            cout << "\n --> Ban ro(P): " << decrypted << endl;
            break;
        }
        case 3:
            break;
        default:
            cout << "\n\t==>Khong co lua chon nay!!!";
            break;
        }
    } while (luachon != 3);
    return 0;
}