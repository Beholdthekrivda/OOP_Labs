#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <map>
#include <climits>
#include "SBase.hpp"

using namespace std;

class Freq
{
private:
    int sum = 0, count = 0;
    double avg = 0;
    map<int, int> dict;
public:
    virtual void Calc(SBase& source)
    {
        int value;
        sum = 0;
        dict.clear();

        while ((value = source.Get()) != -1)
        {
            sum += value;
            count++;
            dict[value]++;
        }
        double s = sum;
        double c = count;
        avg = s / c;
    }

    virtual void print(ostream& os) const
    {
        if (dict.empty()) 
        {
            os << "Нет данных для анализа" << endl;
            return;
        }
        
        for (const auto& pair : dict) 
        {
            os << "Число " << pair.first << " встречается " 
               << pair.second << " раз" << endl;
        }
        
        os << "Сумма всех чисел: " << sum << endl;
        os << "Среднее значение: " << avg << endl;
    }

    friend ostream& operator<<(ostream& os, const Freq& freq) 
    {
        freq.print(os);
        return os;
    }
};

class Diap: public Freq
{
private:
    int min, max, count;
public:
    void Calc(SBase& source) override
    {
        min = INT_MAX; max = INT_MIN; count = 0;
        int value;
        while ((value = source.Get()) != -1)
        {
            if (min > value) min = value;
            if (max < value) max = value;
            count++;
        }
    }

    void print(ostream& os) const override
    {
        if (count == 0) 
        {
            os << "Нет данных для анализа" << endl;
            return;
        }
        
        os << "Минимальное значение: " << min << endl;
        os << "Максимальное значение: " << max << endl;
        os << "Количество чисел: " << count << endl;
    }
};

int main()
{
    srand(time(NULL));

    SFile test1a("file_with_numbers.txt");
    SFile test1b("file_with_numbers.txt");
    SKbrd test2;
    SQueue test3(10);
    Freq test4;
    Diap test5;

    cout << "Невиртуальный вызов" << endl;

    test4.Calc(test1a);
    cout << test4 << endl;

    test5.Calc(test1b);
    cout << test5 << endl;

    cout << "Виртуальный вызов" << endl;

    Freq *ptr;
    Diap y;
    ptr = &y;

    ptr->Calc(test3);
    cout << *ptr << endl;

    SQueue wasd(5);
    Diap b;
    Freq &a = b;

    a.Calc(wasd);
    cout << a << endl;

    return 0;
}