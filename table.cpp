/**
 * Implementation of the template class Table. Must include this Table.cpp in the file
 * with int main().
 *
 * @Author Brett Bernardi
 * @date September 15, 2020
 *
 * Table.cpp
 */

#include "table.h"


template <class T>
table<T>::table(int r, int c)
{
    rows = r;
    cols = c;
    // allocate memory for the the array of T* pointers
    data = new T*[rows];

    //data is a pointer to an array of pointers of type T*

    for(int i = 0; i < cols; i++)
    {
        // allocate memory for each array
        data[i] = new T[cols];
    }
}

/*
 *
 * Constructor that allocates memory for 2D array, based on the specified number of
 * rows and columns. Here, the number of rows = number of columns.
 */
template <class T>
table<T>::table(int r_and_c)
{
    rows = r_and_c;
    cols = r_and_c;

    data = new T*[rows];
    for(int i = 0; i < cols; i++)
    {
        data[i] = new T[cols];
    }
}


template <class T>
table<T>::table(const table& t)
{
    this->rows = t.rows;
    this->cols = t.cols;

    this->data = new T*[rows];
    for(int i = 0; i < cols; i++)
    {
        this->data[i] = new T[cols];
    }

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            this->data[i][j] = t.data[i][j];
        }
    }
}


template <class T>
table<T>& table<T>::append_cols(const table<T>& t) const
{
    assert(this->rows == t.rows);
    table<T> *newTable = new table(this->rows, this->cols + t.cols);
    for(int i = 0; i < newTable->rows; i++)
    {
        for(int j = 0; j < newTable->cols; j++)
        {
            if(j < this->cols)
            {
                newTable->operator()(i,j) = this->data[i][j];
            }
            else{
                newTable->operator()(i,j) = t.data[i][j - this->cols];
            }
        }
    }
    return *newTable;
}


template <class T>
table<T>& table<T>::append_rows(const table<T>& t) const
{
    assert(this->cols == t.cols);
    table<T> *newTable = new table(this->rows + t.rows, this->cols);
    for(int i = 0; i < newTable->get_rows(); i++)
    {
        for(int j = 0; j < newTable->get_cols(); j++)
        {
            if(i < this->rows)
            {
                newTable->data[i][j] = this->data[i][j];
            }
            else{
                std::cout<< " i, j = " << i << " " << j << std::endl;
                std::cout << "t.data[" << i - this->get_rows() << "][" << j << "]" <<
                std::endl;
                newTable->data[i][j] = t.data[i - this->rows][j];
            }


        }
    }
    return *newTable;
}

template <class T>
table<T>& table<T>::operator =(const table& t)
{
    // check if this object(on left side of "=" operator) already exists.
    if(this->data!=NULL)
    {
        this->clear();
    }

    this->rows = t.rows;
    this->cols = t.cols;

    this->data = new T*[rows];
    for(int i = 0; i < cols; i++)
    {
        this->data[i] = new T[cols];
    }

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            this->data[i][j] = t.data[i][j];
        }
    }

    // "this" is a pointer to the object currently in use. Must de-reference
    //  when returning.
    return *this;
}

template <class T>
int table<T>::get_cols()const
{
    return this->cols;
}


template <class T>
int table<T>::get_rows()const
{
    return this->rows;
}


template <class T>
T& table<T>::operator()(int x, int y)
{
    assert(validIndices(x,y));
    // return a reference.
    return data[x][y];

}


template <class T>
table<T>& table<T>::operator()(int r1, int c1, int r2, int c2) const
{
    assert(r2 > r1 && c2 > c1); // must be true in order for function to make
    //sense

    table<T>* new_table = new table(r2-r1 + 1, c2 - c1 + 1);
    int newi = 0;

    for(int i = r1; i <= r2; i++)
    {
        int newj = 0;
        for(int j = c1; j <= c2; j++)
        {
            new_table->operator()(newi,newj) = this->data[i][j];
            newj ++;
        }
        newi++;
    }
    // de-reference and return
    return *new_table;
}


template <class T>
table<T>& table<T>::operator+(T (*pFunction)(T)) const
{
    table<T> *newTable = new table<T>(this->get_rows(), this->get_cols());
    for(int i = 0; i < newTable->get_rows(); i++)
    {
        for(int j = 0; j < newTable->get_cols(); j++)
        {
            newTable->operator()(i,j) = pFunction(this->data[i][j]);
        }
    }
    return *newTable;
}


template <class T>
void table<T>::clear()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] this->data[i]; // de-allocate each pointer in the T*[] array
    }

    delete[] this->data; // de-allocate the entire T** data pointer
}


template <class T>
bool table<T>::validIndices(int x, int y)
{
    if(x < 0 || x > this->rows || y < 0 || y > this->cols)
    {
        return false;
    }
    return true;
}


template <class T>
table<T>::~table()
{
    clear();
}
