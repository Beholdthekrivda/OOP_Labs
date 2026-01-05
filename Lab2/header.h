#ifndef Lab1_h
#define Lab1_h

#include <cmath>
#include <iostream>
#include <istream>
#include <ostream>
#include <time.h>
#include <cstring>

using namespace std;

class CStr
{
private:
	char* string;
	char* generate(int length);
public:
	int length_of_string();

	CStr(); 
	CStr(const char* str);
	CStr(int len);
	CStr(const CStr &s);

	CStr& operator=(const CStr& s);
	CStr& operator=(const char* s);
	CStr operator+(const CStr &s);
	CStr& operator+=(const CStr& s);
	bool operator<(const CStr& s);
	bool operator>(const CStr& s);
	char& operator[](int pos);

	friend ostream & operator<<(ostream& r, const CStr& s);
	friend istream & operator>>(istream& r, CStr& s);

	~CStr();
};

#endif