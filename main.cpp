#include <iostream>
#include "table.cpp"
using namespace std;

template <class T>
void fill(table<T>& t, T item);

template <class T>
void randomize(table<T>& t);

int square(int k);

int main()
{
    table<int> t1(3,3);
    for(int i = 0; i < t1.get_rows(); i++)
    {
        for(int j = 0; j < t1.get_cols(); j++)
        {
            if(i == 2 and j == 0)
                t1.operator ()(i,j) = 5;
            else
                t1.operator()(i,j) = 66;
        }
    }

    cout << t1 << endl;
    cout << t1(2,0) << endl;

    table<int> t2(3,3);
    for(int i = 0; i < t2.get_rows(); i++)
    {
        for(int j =0; j < t2.get_cols(); j++)
        {
            t2(i,j) = 33;
        }
    }
    cout << t2 << endl;

    cout << t1 << endl;
    cout << t2 << endl;
    cout << t1(2,0) << endl;

}

template <class T>
void fill(table<T>& t, T item)
{
    for(int i = 0; i < t.get_rows(); i++)
    {
        for(int j = 0; j < t.get_cols(); j++)
        {
            t(i,j)=item;
        }
    }
}

int square(int k)
{
    return k*k;
}

template <class T>
void randomize(table<T>& t)
{
    srand(time(0));
    for(int i = 0; i < t.get_rows(); i++)
    {
        for(int j = 0; j < t.get_cols(); j++)
        {
            t(i,j) = (rand() % 90 + 10);
        }
    }
}
