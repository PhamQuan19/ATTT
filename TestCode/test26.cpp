#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class MonoalphabeticCipher {
public:
    static char p[26];
    static char ch[26];

    static string doEncryption(const string& s) {
        string result = s;
        for (size_t i = 0; i < s.length(); i++) {
            for (int j = 0; j < 26; j++) {
                if (p[j] == s[i]) {
                    result[i] = ch[j];
                    break;
                }
            }
        }
        return result;
    }

    static string doDecryption(const string& s) {
        string result = s;
        for (size_t i = 0; i < s.length(); i++) {
            for (int j = 0; j < 26; j++) {
                if (ch[j] == s[i]) {
                    result[i] = p[j];
                    break;
                }
            }
        }
        return result;
    }
};

char MonoalphabeticCipher::p[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
char MonoalphabeticCipher::ch[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M'};

int main() {
    cout << "Enter the message: ";
    string message;
    cin >> message;
    
    // Convert the input message to lowercase
    transform(message.begin(), message.end(), message.begin(), ::tolower);
    
    string encryptedMessage = MonoalphabeticCipher::doEncryption(message);
    cout << "Encrypted message: " << encryptedMessage << endl;
    
    string decryptedMessage = MonoalphabeticCipher::doDecryption(encryptedMessage);
    cout << "Decrypted message: " << decryptedMessage << endl;
    
    return 0;
}
