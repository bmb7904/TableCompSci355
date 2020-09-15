/**
 * Header file of template class Table.
 *
 *@Author Brett Bernardi
 *@date September 15, 2020
 * table.h
 */

#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <cassert>
#include <iomanip>

template <class T>
class table {

    public:
        /*
         * Constructor that allocates memory for table made up 2D array, based on the
         * specified number of rows and columns.
         */
        table(int r, int c);
        /*
        *
        * Constructor that allocates memory for 2D array, based on the specified number of
        * rows and columns. Here, the number of rows = number of columns.
        */
        table(int r_and_c);
        /*
        * Copy Constructor. Needed because we are dealing with pointer data, and a
        * default copy constructor will result in shallow copies.
        */
        table(const table& t);
        /*
        * Overloaded assignment operator. Needed because we are dealing with pointer
        * data. Returns a reference to the table object on left of "=" sign.
        */
        table& operator=(const table& t);
        T get(int r, int c)const;
        void set(int r, int c, T value);
        /*
        * Returns number of columns for this table object.
        */
        int get_cols()const;
        /*
        * Returns number of rows for this table object.
        */
        int get_rows()const;
        /*
        * Overloaded function call operator () that returns a reference to the 2D array at the
        * specified indices. Allows client to set specific cells in the following
        * format: t(x,y) = z, where is table object.
        */
        T& operator()(int x, int y);
        /*
        * Overloaded operator and member function that extracts a sub-table from the
        * object calling it.
        * (r1,c1) is the upper left hand corner of new sub-table
        * (r2,c2) is the lower right hand corner of new sub-table.
        * Returns a new Table<T> which is the sub-table.
        */
        table& operator()(int r1, int c1, int r2, int c2) const;
        /*
        * Overloaded "+" operator. A pointer to a function (*pFunction) is passed as an
        * argument when this function is called. This function has the form: T (*pFunction) T
        * --> Where it returns the type T and takes in an argument of type T. As long as the
        * Template class Type and the Template Function type match, this function can be used
        * to perform some type of rule on all elements of the 2D array. Returns a new
        * Table<int> after function is used on this table.
        */
        table<T>& operator+(T (*pFunction)(T)) const;
        /*
        * Will take a table and concatenate it with another table object in the parameter.
        * When concatenating horizontally, both tables must have same number of rows. cassert
        * checks for this condition.
        */
        table& append_cols(const table& t) const;
        /*
        * Will take a table and concatenate it with another table object in the parameter.
        * When concatenating vertically, both tables must have same number of columns. cassert
        * checks for this condition. Returns a new concatenated table.
        */
        table& append_rows(const table& t) const;
        /*
        * Overloaded "<<" operator that takes an ostream& object and a table. modifies and
        * returns the ostream& object.
        */
        friend std::ostream& operator<<(std::ostream& out, const table<T>& t)
        {
            // get current width from ostream object.
            int w = out.width();

            for(int i = 0; i < t.rows; i++)
            {
                for(int j = 0; j < t.cols; j++)
                {
                    out << std::setw(w) << t.data[i][j] << " ";
                }
                out << std::endl;
            }
            return out;

        }
        /*
        * Destructor. Must be defined because we are dealing with pointer data.
        */
        virtual ~table();

    private:
        int rows;
        int cols;
        // a pointer to a T*. i.e. A pointer to a pointer
        T **data;

        /*
        * Releases memory from object. First releases each T[]. Followed by releasing the
        * memory of the T*[] pointed at by data.
        */
        void clear();
        /*
        * Private helper function that checks the specified x and y parameters, to see if they
        * are valid indices for this particular instance of the table class.
        */
        bool validIndices(int x, int y);


};


#endif /* TABLE_H */