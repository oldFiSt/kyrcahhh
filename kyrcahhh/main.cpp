#include <iostream>
#include <string>
#include <windows.h> //SetConsoleOutputCP

#include <D:/for_icu/include/unicode/ustream.h>
#include <D:/for_icu/include/unicode/unistr.h>
#include <D:/for_icu/include/unicode/ucnv.h>

#include <vector>
#include <codecvt>
#include <cstdlib> 


// ������� ��� �������������� ������ �� UTF-8 � Windows-1251 � �������������� ICU
std::string convertUTF8ToWindows1251(const std::string& utf8_str) {
    UErrorCode errorCode = U_ZERO_ERROR;

    UConverter* utf8ToWindows1251 = ucnv_open("windows-1251", &errorCode);
    if (U_FAILURE(errorCode)) {
        std::cerr << "������ ��� �������� ����������: " << u_errorName(errorCode) << std::endl;
        return "";
    }

    int32_t windows1251Length = utf8_str.size() * ucnv_getMaxCharSize(utf8ToWindows1251);
    std::string windows1251_str(windows1251Length, '\0');

    const char* source = utf8_str.c_str();
    char* target = &windows1251_str[0];
    int32_t targetCapacity = windows1251Length;

    int32_t convertedLength = ucnv_convert("windows-1251", "UTF-8", target, targetCapacity, source, utf8_str.size(), &errorCode);

    if (U_FAILURE(errorCode)) {
        std::cerr << "������ ��� �����������: " << u_errorName(errorCode) << std::endl;
        ucnv_close(utf8ToWindows1251);
        return "";
    }

    windows1251_str.resize(convertedLength); // ��������� ������ �� ����������� �����
    ucnv_close(utf8ToWindows1251);
    return windows1251_str;
}

void writeToConsole(const std::string& str) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    WriteConsoleA(hConsole, str.c_str(), str.length(), &written, nullptr);
}

int main() {
    setlocale(LC_ALL, "Rus");

    std::string utf8_string = "������, ���!";

    SetConsoleOutputCP(CP_UTF8);

    std::cout << "UTF-8 ������: " << utf8_string << std::endl;
    std::cout << "Win-1251 ������: ";

    std::string windows1251_string = convertUTF8ToWindows1251(utf8_string);

    SetConsoleOutputCP(1251);

    writeToConsole(windows1251_string);
    std::cout << std::endl;
    system("pause");

    return 0;
}













