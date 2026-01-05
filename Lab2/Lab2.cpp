#include <iostream>
#include <istream>
#include <ostream>
#include <cstring>
#include "CStr.h"

using namespace std;

template <typename T> 
class TVector
{
    private:
        T* data;
        int size, capacity;
    public:
        TVector(int s = 1): data(new T[s]), size(s), capacity(s)
        {
            for (int i = 0; i < capacity; i++)
            {
                data[i] = T();
            }
        }

        TVector(const TVector<T> &v)
        {
            capacity = v.capacity;
            size = v.size;
            data = new T[capacity];
            for (int i = 0; i < size; i++)
            {
                data[i] = v.data[i];
            }
        }

        ~TVector()
        {
            delete[] data;
        }

        T& operator[](int pos)
        {   
            if (pos <= size && pos >= 0) return data[pos];
            else exit(1);
        }

        TVector& operator+=(const TVector<T> &v)
        {
            if (v.size == size)
            {
                for (int i = 0; i < size; i++)
                {
                    data[i] += v.data[i];
                }
            }
            return *this;
        }

        TVector& operator=(const TVector<T> &v)
        {
            if (this != &v)
            {
                delete[] data;
                capacity = v.capacity;
                size = v.size;
                data = new T[capacity];
                for (int i = 0; i < size; i++)
                {
                    data[i] = v.data[i];
                }
            }
            return *this;
        }

        friend ostream& operator<<(ostream &r, TVector& v)
        {
            for (int i = 0; i < v.size; i++)
            {
                r << v.data[i] << " ";
            }
            return r; 
        }

        friend istream& operator>>(istream &r, TVector& v)
        {
            for (int i = 0; i < v.capacity; i++)
            {
                r >> v.data[i];
            }
            v.size = v.capacity;
            return r;
        }

        void setLength(int newlen);
};

template <typename T>
void TVector<T>::setLength(int newlen)
{
    T* temp = new T[newlen];
    int countcopy = (newlen <= size) ? newlen : size;

    for (int i = 0; i < countcopy; i++)
    {
        temp[i] = data[i];
    }

    for (int i = countcopy; i < newlen; i++)
    {
        temp[i] = T();
    }
    
    delete[] data;
    data = temp;
    capacity = newlen;
    size = newlen;
}

template <typename T>
class TMatrix
{
    private:
        TVector<T>* matrix;
        int count_row, count_col;
    public:
        TMatrix(int r = 1, int c = 1): count_row(r), count_col(c)
        {
            matrix = new TVector<T>[count_row];
            for (int i = 0; i < count_row; i++)
            {
                matrix[i] = TVector<T>(count_col);
            } 
        }

        TMatrix(const TMatrix& other): count_row(other.count_row), count_col(other.count_col)
        {
            matrix = new TVector<T>[count_row];
            for (int i = 0; i < count_row; i++)
            {
                matrix[i] = other.matrix[i];
            } 
        }

        ~TMatrix()
        {
            delete[] matrix;
        }

        TMatrix& operator=(const TMatrix& other)
        {
            if (this != &other)
            {   
                if (this->count_col == other.count_col && this->count_row == other.count_row)
                {
                    delete[] matrix;
                    count_row = other.count_row;
                    count_col = other.count_col;
                    matrix = new TVector<T>[count_row];
                    for (int i = 0; i < count_row; i++)
                    {
                        matrix[i] = other.matrix[i];
                    }
                }
            }
            return *this;
        }

        TMatrix& operator+=(const TMatrix& other)
        {
            if (this->count_col == other.count_col && this->count_row == other.count_row)
            {
                for (int i = 0; i < count_row; i++)
                {
                    matrix[i] += other.matrix[i];
                }
            }
            return *this;
        }

        TVector<T>& operator[](int pos)
        {
            if (pos < count_row && pos >= 0) return matrix[pos];
            else exit(1);
        }

        friend ostream & operator<<(ostream& os, const TMatrix& m)
        {
            for (int i = 0; i < m.count_row; i++)
            {
                os << m.matrix[i] << endl;
            }
            return os;
        }

        friend istream & operator>>(istream& is, TMatrix& m)
        {
            for (int i = 0; i < m.count_row; i++)
            {
                is >> m[i];
            }
            return is;
        }
};

void testvector()
{
    TVector<double> v_d(3), v_d1(3);
    TVector<string> v_s(3), v_s1(3);

    cout << "Введите элементы типа double (v_d): " << endl; cin >> v_d;
    cout << v_d << endl;
    cout << "Введите элементы типа double (v_d1): " << endl; cin >> v_d1;
    cout << v_d1 << endl;

    v_d += v_d1;
    cout << "Результат +=: " << v_d << endl;

    v_d = v_d1;
    cout << "Результат =: " << v_d << endl;

    cout << "Вывод 1-го элемента: " << v_d[0] << endl;

    cout << "Введите элементы типа string (v_s): " << endl; cin >> v_s;
    cout << v_s << endl;
    cout << "Введите элементы типа string (v_s1): " << endl; cin >> v_s1;
    cout << v_s1 << endl;

    v_s += v_s1;
    cout << "Результат +=: " << v_s << endl;

    v_s = v_s1;
    cout << "Результат =: " << v_s << endl;

    cout << "Вывод 1-го элемента: " << v_s[0] << endl;

    TVector<double> v_test_d(v_d);
    TVector<string> v_test_s(v_s);

    cout << "Результат конструктора копий: " << endl;
    cout << v_test_d << endl;
    cout << v_test_s << endl;

    v_test_d.setLength(10);
    cout << "Результат изменения длины (v_test_d): " << endl;
    cout << v_test_d << endl;

    v_test_s.setLength(10);
    cout << "Результат изменения длины (v_test_s): " << endl;
    cout << v_test_s << endl;
}

void testvector_ptr()
{
    TVector<double>* v_d = new TVector<double>(3), *v_d1 = new TVector<double>(3);
    TVector<string>* v_s = new TVector<string>(3), *v_s1 = new TVector<string>(3);

    cout << "Введите элементы типа double (v_d): " << endl; cin >> *v_d;
    cout << *v_d << endl;
    cout << "Введите элементы типа double (v_d1): " << endl; cin >> *v_d1;
    cout << *v_d1 << endl;

    *v_d += *v_d1;
    cout << "Результат +=: " << *v_d << endl;

    *v_d = *v_d1;
    cout << "Результат =: " << *v_d << endl;

    cout << "Вывод 1-го элемента: " << (*v_d)[0] << endl;

    cout << "Введите элементы типа string (v_s): " << endl; cin >> *v_s;
    cout << *v_s << endl;
    cout << "Введите элементы типа string (v_s1): " << endl; cin >> *v_s1;
    cout << *v_s1 << endl;

    *v_s += *v_s1;
    cout << "Результат +=: " << *v_s << endl;

    *v_s = *v_s1;
    cout << "Результат =: " << *v_s << endl;

    cout << "Вывод 1-го элемента: " << v_s[0] << endl;

    TVector<double> v_test_d(*v_d);
    TVector<string> v_test_s(*v_s);

    cout << "Результат конструктора копий: " << endl;
    cout << v_test_d << endl;
    cout << v_test_s << endl;

    v_d->setLength(10);
    cout << "Результат изменения длины (v_test_d): " << endl;
    cout << *v_d << endl;

    v_s->setLength(10);
    cout << "Результат изменения длины (v_test_s): " << endl;
    cout << *v_s << endl;

    delete v_d; delete v_d1;
    delete v_s; delete v_s1;
}

void testmatrix()
{
    TMatrix<int> m_i(2, 2), m_i1(2, 2);
    TMatrix<CStr> m_c(2, 2), m_c1(2, 2);

    cout << "Введите элементы типа int (m_i): " << endl; cin >> m_i;
    cout << m_i << endl;
    cout << "Введите элементы типа int (m_i1): " << endl; cin >> m_i1;
    cout << m_i1 << endl;

    m_i += m_i1;
    cout << "Результат +=: " << endl;
    cout << m_i << endl;

    m_i = m_i1;
    cout << "Результат =: " << endl;
    cout << m_i << endl;

    cout << "Вывод 1-й строки: " << m_i[0] << endl;

    m_i[0][0] = 100;
    cout << "Замена значения 1-го элемента: " << endl;
    cout << m_i << endl;

    TVector<int> v(2);
    cout << "Введите тестовый вектор: "; cin >> v;

    m_i[0] = v; 
    cout << "Замена значения 1-й строки: " << endl; 
    cout << m_i << endl; 

    TMatrix<int> m_test(m_i);
    cout << "Результат копирования: " << endl;
    cout << m_test << endl;

    cout << "Введите элементы типа CStr (m_с): " << endl; cin >> m_c;
    cout << m_c << endl;
    cout << "Введите элементы типа CStr (m_c1): " << endl; cin >> m_c1;
    cout << m_c1 << endl;

    m_c += m_c1;
    cout << "Результат +=: " << endl;
    cout << m_c << endl;

    m_c = m_c1;
    cout << "Результат =: " << endl;
    cout << m_c << endl;

    cout << "Вывод 1-й строки: " << endl;
    cout << m_c[0] << endl;

    CStr a = "два";
    m_c[0][0] = a;
    cout << "Замена значения 1-го элемента: " << endl;
    cout << m_c << endl;

    TVector<CStr> v_c(2);
    cout << "Введите тестовый вектор: "; cin >> v_c;

    m_c[0] = v_c; 
    cout << "Замена значения 1-й строки: " << endl;   
    cout << m_c << endl;

    TMatrix<CStr> m_test_c(m_c);
    cout << "Результат копирования: " << endl;
    cout << m_test_c << endl;
}

void testmatrix_ptr()
{
    TMatrix<int> *m_i = new TMatrix<int>(2, 2), *m_i1 = new TMatrix<int>(2, 2);
    TMatrix<CStr> *m_c = new TMatrix<CStr>(2, 2), *m_c1 = new TMatrix<CStr>(2, 2);

    cout << "Введите элементы типа int (m_i): " << endl; cin >> *m_i;
    cout << *m_i << endl;
    cout << "Введите элементы типа int (m_i1): " << endl; cin >> *m_i1;
    cout << *m_i1 << endl;

    *m_i += *m_i1;
    cout << "Результат +=: " << endl;
    cout << *m_i << endl;

    *m_i = *m_i1;
    cout << "Результат =: " << endl;
    cout << *m_i << endl;

    cout << "Вывод 1-й строки: " << (*m_i)[0] << endl;

    (*m_i)[0][0] = 100;
    cout << "Замена значения 1-го элемента: " << endl;
    cout << *m_i << endl;

    TVector<int> v(2);
    cout << "Введите тестовый вектор: "; cin >> v;

    (*m_i)[0] = v; 
    cout << "Замена значения 1-й строки: " << endl; 
    cout << *m_i << endl; 

    TMatrix<int> m_test(*m_i);
    cout << "Результат копирования: " << endl;
    cout << m_test << endl;

    cout << "Введите элементы типа CStr (m_с): " << endl; cin >> *m_c;
    cout << *m_c << endl;
    cout << "Введите элементы типа CStr (m_c1): " << endl; cin >> *m_c1;
    cout << *m_c1 << endl;

    *m_c += *m_c1;
    cout << "Результат +=: " << endl;
    cout << *m_c << endl;

    *m_c = *m_c1;
    cout << "Результат =: " << endl;
    cout << *m_c << endl;

    cout << "Вывод 1-й строки: " << endl;
    cout << (*m_c)[0] << endl;

    CStr a("два");
    (*m_c)[0][0] = a;
    cout << "Замена значения 1-го элемента: " << endl;
    cout << *m_c << endl;

    TVector<CStr> v_c(2);
    cout << "Введите тестовый вектор: "; cin >> v_c;

    (*m_c)[0] = v_c; 
    cout << "Замена значения 1-й строки: " << endl;   
    cout << *m_c << endl;

    TMatrix<CStr> m_test_c(*m_c);
    cout << "Результат копирования: " << endl;
    cout << m_test_c << endl;

    delete m_i; delete m_i1; 
    delete m_c; delete m_c1;
}

int main()
{
    
    return 0;
}