#include <iostream>
#include <string>

bool containsVietnameseDiacritics(const std::string& str) {
    // Duyệt qua từng kí tự trong chuỗi UTF-8
    for (size_t i = 0; i < str.size(); ++i) {
        // Nếu là kí tự tiếng Việt có dấu
        if ((str[i] & 0xC0) == 0x80) {
            return true;
        }
    }
    return false; // Nếu không có kí tự tiếng Việt có dấu, trả về false
}

int main() {
    std::string key;

    std::cout << "Nhập key: ";
    std::getline(std::cin, key);

    if (containsVietnameseDiacritics(key)) {
        std::cout << "Key chua ki tu tieng vien." << std::endl;
    } else {
        std::cout << "Key khong chua ki tu tieng viet." << std::endl;
    }

    return 0;
}
