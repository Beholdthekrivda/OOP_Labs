#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class SBase
{
public:
    virtual int Get() = 0;
    virtual ~SBase() = default;
};

class SFile: public SBase
{
private:
    ifstream file;
public:
    SFile(const string& name)
    {
        file.open(name);
    }

    ~SFile()
    {
        if (file.is_open()) file.close();
    }

    int Get() override
    {
        int value;
        if (file >> value) return value;
        return -1;
    }
};

class SKbrd: public SBase
{
public:
    SKbrd() {}
    ~SKbrd() {}
    int Get() override
    {
        int value;
        if (cin >> value)
            return value;
        else
            return -1;
    }
};

class SQueue: public SBase
{
private:
    int* arr;
    int size, count = 0;
public:
    SQueue(int n)
    {
        size = n;
        arr = new int[size];

        for (int i = 0; i < size; i++)
        {
            arr[i] = 1 + rand() % 21;
        }
    }

    ~SQueue()
    {
        delete[] arr;
    }

    int Get() override
    {
        if (count < size) 
        {
            return arr[count++];
        }
        else return -1;
    }
};