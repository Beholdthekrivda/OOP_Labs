#include <cmath>
#include <iostream>
#include <istream>
#include <ostream>
#include <time.h>
#include <cstring>
// g++ test.cpp -o test && ./test 
// 1. (решено) разобраться с ошибкой "terminate called after throwing an instance of 'std::bad_array_new_length'"
// 2. ошибка с delete, понимание работы
// 3. отличия создания переменной в стеке от создания в куче
// 4. (решено см. 1 проблему) разобраться почему первые элементы массива array пропадают, если array создан как указатель
using namespace std;

class CStr
{
private:
	char* string;
	char* generate(int length);
public:
	int length_of_string()
	{
		return strlen(string);
	}

	CStr() 
	{
		int len = 1 + rand() % 20;
		string = generate(len);
	}

	CStr(const char* str)
	{
		string = new char[strlen(str) + 1];
		strcpy(string, str);
	}

	CStr(int len)
	{
		if (len > 0 && len <= 20) string = generate(len);
		else cout << "Проверьте условие";
	}

	CStr(const CStr &s)
	{
		string = new char[strlen(s.string) + 1];
		strcpy(string, s.string);
	}

	CStr& operator=(CStr& s)
	{
		if (this == &s) return *this;
		delete[] string;
		string = new char[strlen(s.string) + 1];
		strcpy(string, s.string);
		return *this;
	}

	CStr& operator=(const char* s)
	{
		delete[] string;
		string = new char[strlen(s) + 1];
		strcpy(string, s);
		return *this;   
	}

	CStr operator+(CStr &s)
	{
		char* temp = new char[strlen(string) + strlen(s.string) + 1];
		strcpy(temp, string); strcat(temp, s.string);

		CStr result(temp);
		delete[] temp;

		return result;
	}

	CStr& operator+=(CStr& s)
	{
		char* temp = new char[strlen(string) + 1];
		strcpy(temp, string);
		delete[] string;
		string = new char[strlen(temp) + strlen(s.string) + 1];
		strcpy(string, temp);
		strcat(string, s.string);
		delete[] temp;
		return *this;
	}

	bool operator<(const CStr& s)
	{
		return strcmp(string, s.string) < 0;
	}

	bool operator>(CStr& s)
	{
		return strcmp(string, s.string) > 0;
	}

	char& operator[](int pos)
	{
		return string[pos];
	}

	friend ostream & operator<<(ostream& r, CStr& s)
	{
		r << s.string;
		return r;
	}

	friend istream & operator>>(istream& r, CStr& s)
	{
		char buf[256];
		r >> buf;

		delete[] s.string;

		s.string = new char[strlen(buf) + 1];
		strcpy(s.string, buf);

		return r;
	}

	~CStr()
	{
		cout << "Работет деструктор для " << string << endl;
		delete[] string;
	}
};

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

class CStrArray
{
private:
	CStr** array;
	int capacity;
	int size;
public:
	CStrArray(int cap)
		: array(new CStr*[cap])
		, size(0)
		, capacity(cap)
	{
		for (int i = 0; i < capacity; i++)
		{
			array[i] = nullptr;
		}

		cout << size << endl;
	}

	CStrArray& operator+=(CStr* symb)
	{
		array[size] = symb;
		size++;
		return *this;
	}

	CStr* operator[](int pos)
	{
		return array[pos];
	}

	friend ostream & operator<<(ostream& r, CStrArray& s)
	{
		for (int i = 0; i < s.size; ++i)
		{
			r << *s.array[i] << " ";
		}
		return r;
	}

	void inderect_sort()
	{
		for (int i = 0; i < size - 1; ++i)
		{
			for (int j = i + 1; j < size; ++j)
			{
				if(*array[i] > *array[j])
				{
					CStr* temp = array[i];
					array[i] = array[j];
					array[j] = temp;
				}
			}
		}
	}

	void len_sort()
	{
		for (int i = 0; i < size - 1; ++i)
		{
			for (int j = i + 1; j < size; ++j)
			{
				if(array[i]->length_of_string() > array[j]->length_of_string())
				{
					CStr* temp = array[i];
					array[i] = array[j];
					array[j] = temp;
				}
			}
		}
	}

	bool check_sort()
	{
		for (int i = 0; i < size - 1; ++i)
		{
			if (!(*array[i+1] > *array[i])) return false;
		}
		return true;
	}

	~CStrArray()
	{
		for (int i = 0; i < size; i++) delete array[i];
    	delete[] array; 
	}
};

int main() 
{
	srand(time(NULL));

	int n;
	cout << "Введите кол-во эл-ов: "; cin >> n;

	cout << "Создание массива CStrArray в куче" << endl;

	CStrArray* array = new CStrArray(n);

	for (int i = 0; i < n; ++i)
	{
		CStr* temp = new CStr(7);
		*array += temp;	
	}
	cout << sizeof(CStrArray) << endl;
	cout << *array << endl;

	delete array;

	cout << endl;
	cout << "Создание массива CStrArray в стеке" << endl;

	CStrArray array1(n);

	for (int i = 0; i < n; ++i)
	{
		CStr* temp = new CStr(7);
		array1 += temp;	
	}

	cout << array1 << endl;
	
	return 0;
}