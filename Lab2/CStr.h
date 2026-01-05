#include <iostream>
#include "header.h"

using namespace std;

char* CStr::generate(int length) 
{
	char* s = new char[length + 1];
	for (int i = 0; i < length; ++i)
	{
		s[i] = 'a' + (0 + rand() % 25);
	}
	s[length] = '\0';
	return s;
}

int CStr::length_of_string()
{
    return strlen(string);
}

CStr::CStr() : string(nullptr) {}

CStr::CStr(const char* str) {
    string = new char[strlen(str) + 1];
    strcpy(string, str);
}

CStr::CStr(int len) {
    if (len > 0 && len <= 20) string = generate(len);
    else std::cout << "Проверьте условие";
}

CStr::CStr(const CStr &s) {
    if (s.string == nullptr) {
        string = new char[1];
        string[0] = '\0';
    } else {
        string = new char[strlen(s.string) + 1];
        strcpy(string, s.string);
    }
}

CStr::~CStr() {
    delete[] string;
}

CStr& CStr::operator=(const CStr& s) {
    if (this == &s) return *this;
    
    // Сначала создаем новую строку, потом удаляем старую
    char* new_string = nullptr;
    if (s.string != nullptr) {
        new_string = new char[strlen(s.string) + 1];
        strcpy(new_string, s.string);
    } else {
        new_string = new char[1];
        new_string[0] = '\0';
    }
    
    delete[] string;  // Теперь безопасно удаляем старую
    string = new_string;
    return *this;
}

CStr& CStr::operator=(const char* s) {
    delete[] string;
    string = new char[strlen(s) + 1];
    strcpy(string, s);
    return *this;   
}

CStr CStr::operator+(const CStr &s) {
    char* temp = new char[strlen(string) + strlen(s.string) + 1];
    strcpy(temp, string); 
    strcat(temp, s.string);

    CStr result(temp);
    delete[] temp;

    return result;
}

CStr& CStr::operator+=(const CStr& s) {
    char* temp = new char[strlen(string) + 1];
    strcpy(temp, string);
    delete[] string;
    string = new char[strlen(temp) + strlen(s.string) + 1];
    strcpy(string, temp);
    strcat(string, s.string);
    delete[] temp;
    return *this;
}

bool CStr::operator<(const CStr& s) {
    return strcmp(string, s.string) < 0;
}

bool CStr::operator>(const CStr& s) {
    return strcmp(string, s.string) > 0;
}

char& CStr::operator[](int pos) {
    return string[pos];
}

std::ostream& operator<<(std::ostream& r, const CStr& s) {
    r << s.string;
    return r;
}

std::istream& operator>>(std::istream& r, CStr& s) {
    char buf[256];
    r >> buf;

    delete[] s.string;
    s.string = new char[strlen(buf) + 1];
    strcpy(s.string, buf);

    return r;
}